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

                  © Copyright of Ignition Software Department
*/

/**************************************************************************************************
* File:        loops.cpp
* Author:      Harsh
* Created On:  2025-12-22
* Brief:       Implementation of main periodic Loops class.
* Description: Runs periodic sensor updates, telemetry streaming and state management.
***************************************************************************************************
* HISTORY:
* +----- (NEW | MODify | ADD | DELete)
* |
* No#   |       when       who                  what
******+*********+**********+********************+**************************************************
*001  ADD       2025-12-24  Harsh                Added sensor upadte, fail-safe check and printing the packet 
*000  NEW      2025-12-22   Kunsh Jain           Added file header and Doxygen
**************************************************************************************************/

// NOTE: File only updated for headers and Doxygen. Logic preserved.

#include "loops.h"
#include "../../tests/test.hpp"
#include <cstdio>

/**
 * \brief Construct Loops and initialize watchdog and sensors.
 * \details Starts watchdog with a default timeout and runs initial sensor init.
 */
Loops::Loops() {
    wdt.Init(5000);
    
}

/**
 * \brief Main blocking runtime loop.
 * \details Periodically updates sensors, prints telemetry packets and manages
 *          the flight state machine and watchdog behavior.
 */
void Loops::Run() {
    const uint32_t SENSOR_PERIOD_MS    = 100;   //change after kunsh gives the value 
    const uint32_t TELEMETRY_PERIOD_MS = 100;  
    const uint32_t STATE_PERIOD_MS     = 100;   

    uint32_t lastSensorMs    = 0;
    uint32_t lastTelemetryMs = 0;
    uint32_t lastStateMs     = 0;

    while (true) {
        const uint32_t now = to_ms_since_boot(get_absolute_time());

        if ((now - lastSensorMs) >= SENSOR_PERIOD_MS) {
            sensors.Update();
            lastSensorMs = now;
        }

        if ((now - lastTelemetryMs) >= TELEMETRY_PERIOD_MS) {
            printf("PKT: %s\n", sensors.GetPacket().c_str());
            lastTelemetryMs = now;
        }

        if ((now - lastStateMs) >= STATE_PERIOD_MS) {
            if (wdt.IsCheckFailed()) {
                manager.SetState(FlightState::FAILSAFE);
            }

            if (manager.GetState() != FlightState::FAILSAFE) {
                wdt.Reset();
            }

            switch (manager.GetState()) {
                case FlightState::BOOT://add sensors.InitAll();
                    manager.HandleBoot();
                    break;
                case FlightState::IDLE:
                    manager.HandleIdle();
                    break;
                case FlightState::ARMED:
                    manager.HandleArmed();
                    break;
                case FlightState::LAUNCH:
                    manager.HandleLaunch();
                    break;
                case FlightState::ASCENT:
                    manager.HandleAscent();
                    break;
                case FlightState::CRUISING:
                    manager.HandleCruising();
                    break;
                case FlightState::APOGEE:
                    manager.HandleApogee();
                    break;
                case FlightState::DEPLOYMENT:
                    manager.HandleDeployment();
                    break;
                case FlightState::DESCENT:
                    manager.HandleDescent();
                    break;
                case FlightState::LANDED:
                    manager.HandleLanded();
                    break;
                case FlightState::FAILSAFE:
                    manager.HandleFailsafe();
                    break;
            }

            lastStateMs = now;
        }

        
    }
}