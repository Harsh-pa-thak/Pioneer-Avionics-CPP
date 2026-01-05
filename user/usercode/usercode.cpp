/*
                                        ::                                                      
                                        ::                                                      
                                        ::                                                      
                                        ::                                                      
                                        ::                                                      
    ..    ..........    :.      ::      ::     .........  ..    ..........    ...      .        
    ::    ::            : .:.   ::     .::.       ::      ::    ::       :    :: :.    :        
    ::    ::   ..:::    :   .:. ::    ::::::      ::      ::    ::       :    ::   ::  :        
    ::    ::......::    :      :::    ::::::      ::      ::    ::.......:    ::     :::        
                                      ::::::                                                    
                                      :.::.:                                                    
                         .::::          ::          ::::.                                       
                       .::::::::.       ::       .:::::::::                                   
                       ::::::::::::....::::.....:::::::::::                                   
                        .:::::::::::::::::::::::::::::::::.        

                  © Copyright of Ignition Avionics
*/

/**************************************************************************************************
* File:        main.cpp
* Author:      Kunsh Jain
* Created On:  2025-12-22
* Brief:       Entry point for Pioneer firmware on Pico.
* Description: Initializes stdio and starts the `Ark` application which runs the main loop.
***************************************************************************************************
* HISTORY:
* +----- (NEW | MODify | ADD | DELete)
* |
* No#   |       when       who                  what
******+*********+**********+********************+**************************************************
* 000  NEW      2025-12-22   Kunsh Jain           Added UserCode part to StatesManager
* 001 MODify    2025-12-23    Harsh               Actual UserCode logic for StatesManager
**************************************************************************************************/
#include "../../ARK/kernel/statesmanager.h"
#include "../../ARK/system/sensors.h"
#include <cmath>

extern SensorManager sensors;

// its better to have a config file for these constants
static constexpr float LAUNCH_ACCEL_G          = 0.0f;
static constexpr int   LAUNCH_CONFIRM_TICKS    = 5;     // 500 ms 
static constexpr float APOGEE_DROP_METERS      = 0.0f;
static constexpr float MAIN_DEPLOY_ALT_METERS  = 0.0f;
static constexpr int   LAND_CONFIRM_TICKS      = 50;    // 5 sec 
static constexpr float LAND_ALT_DELTA_METERS   = 0.0f;

// also can be in config
static float ground_altitude   = 0.0f;
static float last_altitude     = 0.0f;
static float max_altitude      = -1e6f;

// state variables
static int   debounce_counter  = 0;
//these are fro 2 state deployment of the chutes
static bool  apogee_deploy_done      = false;
static bool  main_deploy_done        = false;
static bool  initialized       = false;

void StatesManager::onUserLogic(FlightState state) {
    if (!sensors.IsHealthy()) {
        SetState(FlightState::FAILSAFE);
        return;
    }
// read sensor data ;must be implemted in SensorManager
    float altitude   = sensors.GetAltitude();
    float accel_z    = sensors.GetAccelZ();
    float accel_mag  = sensors.GetAccelMagnitude();
    float agl        = altitude - ground_altitude;

    switch (state) {
        case FlightState::BOOT:
            
            if (!initialized) {
                ground_altitude = altitude;
                debounce_counter = 0;
                initialized = true;
            }

            if (fabs(altitude - last_altitude) < 0.2f) {
                debounce_counter++;
            } else {
                debounce_counter = 0;
                ground_altitude = altitude;
            }

            if (debounce_counter >= 20) {
                SetState(FlightState::IDLE);
            }
            break;


        case FlightState::IDLE:
            // Maintain slow barometric drift correction while stationary(chat gpt values ) 
            // Main agend is that the values will not drift too much from initial ground altitude 
            if (accel_mag > 0.9f && accel_mag < 1.1f) {
                ground_altitude = (ground_altitude * 0.98f) + (altitude * 0.02f);
            }
            //IsArmCommanded must also be implemented in SensorManager to read a pin or command
            if (sensors.IsArmCommanded()) {
                debounce_counter = 0;
                SetState(FlightState::ARMED);
            }
            break;

        case FlightState::ARMED:
            // System is live; wait for physical launch
            if (accel_z > LAUNCH_ACCEL_G && agl > 2.0f) {
                debounce_counter++;
            } else {
                debounce_counter = 0;
            }

            // Confirm sustained launch acceleration
            if (debounce_counter >= LAUNCH_CONFIRM_TICKS) {
                SetState(FlightState::LAUNCH);
            }
            break;
        case FlightState::LAUNCH:
            // Confirm upward motion 
            if (altitude > last_altitude) {
                SetState(FlightState::ASCENT);
            }
            break;

        case FlightState::ASCENT:
            // Track maximum altitude reached
            if (agl > max_altitude) {
                max_altitude = agl;
            }

            // Detect apogee via altitude drop from peak(more safe way then relying on max altitude only)
            if ((max_altitude - agl) >= APOGEE_DROP_METERS) {
                SetState(FlightState::APOGEE);
            }
            break;

        case FlightState::APOGEE:
            // Fire deploy  once at apogee
            if (!apogee_deploy_done) {
                sensors.ActivatePyroChannel(1); 
                apogee_deploy_done = true;
            }
            SetState(FlightState::DESCENT);
            break;

        
        case FlightState::DESCENT:
            // Fire main deploy  at configured altitude
            if (!main_deploy_done && agl < MAIN_DEPLOY_ALT_METERS && agl > 20.0f) {
                sensors.ActivatePyroChannel(2); 
                main_deploy_done = true;
            }

            if (fabs(altitude - last_altitude) < LAND_ALT_DELTA_METERS) {
                debounce_counter++;
            } else {
                debounce_counter = 0;
            }

            if (debounce_counter >= LAND_CONFIRM_TICKS) {
                SetState(FlightState::LANDED);
            }
            break;

        case FlightState::LANDED:
            // Enter post-flight recovery 
            sensors.EnterBeaconMode();
            break;

        case FlightState::FAILSAFE:
            // Immediate recovery: deploy all systems
            sensors.ActivatePyroChannel(1);
            sensors.ActivatePyroChannel(2);
            break;

        default:
            break;
    }

    last_altitude = altitude;
}
