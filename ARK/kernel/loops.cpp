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
* File:        loops.cpp
* Author:      Kunsh Jain
* Created On:  2025-12-22
* Brief:       Implementation of main periodic Loops class.
* Description: Runs periodic sensor updates, telemetry streaming and state management.
***************************************************************************************************
* HISTORY:
* +----- (NEW | MODify | ADD | DELete)
* |
* No#   |       when       who                  what
******+*********+**********+********************+**************************************************
* 000  NEW      2025-12-22   Kunsh Jain           Added file header and Doxygen
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
    sleep_ms(2000);
    sensors.InitAll();
}

/**
 * \brief Main blocking runtime loop.
 * \details Periodically updates sensors, prints telemetry packets and manages
 *          the flight state machine and watchdog behavior.
 */
void Loops::Run() {
    uint32_t telemetry_counter = 0;

    while (true) {
        sensors.Update();

        if (telemetry_counter % 50 == 0) {
            printf("PKT: %s\n", sensors.GetPacket().c_str());
        }
        telemetry_counter++;

        if (wdt.IsCheckFailed()) {
            manager.SetState(FlightState::FAILSAFE);
        }

        if (manager.GetState() != FlightState::FAILSAFE) {
            wdt.Reset();
        }

        switch (manager.GetState()) {
            case FlightState::BOOT:
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

        sleep_ms(10);
    }
}