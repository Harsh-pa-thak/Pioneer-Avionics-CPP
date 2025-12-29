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
*000  NEW      2025-12-22   Kunsh Jain           Created the initial structure , Added Documentation 
*001  ADD       2025-12-24  Harsh                Added sensor upadte, fail-safe check and printing the packet 
**************************************************************************************************/

#include "loops.h"
#include "../../tests/test.hpp"
#include <cstdio>

Loops::Loops() {
    wdt.Init(5000); // Initialize watchdog
    sensors.InitAll(); // Initialize hardware sensors
}

void Loops::Run() {
    const uint32_t SENSOR_PERIOD_MS    = 10;   // 100Hz polling
    const uint32_t TELEMETRY_PERIOD_MS = 100;  // 10Hz stream
    const uint32_t STATE_PERIOD_MS     = 100;  // 10Hz state logic

    uint32_t lastSensorMs    = 0;
    uint32_t lastTelemetryMs = 0;
    uint32_t lastStateMs     = 0;

    while (true) {
        const uint32_t now = to_ms_since_boot(get_absolute_time());

        // Sensor Update Block
        if ((now - lastSensorMs) >= SENSOR_PERIOD_MS) {
            sensors.Update();
            lastSensorMs = now;
        }

        // Telemetry Stream Block
        if ((now - lastTelemetryMs) >= TELEMETRY_PERIOD_MS) {
            printf("PKT: %s\n", sensors.GetPacket().c_str());
            lastTelemetryMs = now;
        }

        // State Machine Execution Block
        if ((now - lastStateMs) >= STATE_PERIOD_MS) {
            if (wdt.IsCheckFailed()) {
                manager.SetState(FlightState::FAILSAFE);
            }

            if (manager.GetState() != FlightState::FAILSAFE) {
                wdt.Reset(); // As per harsh new logic Pet the watchdog at certain frequency
            }

            // This triggers your definitions in usercode.cpp
            switch (manager.GetState()) {
                case FlightState::BOOT:       manager.HandleBoot();       break;
                case FlightState::IDLE:       manager.HandleIdle();       break;
                case FlightState::ARMED:      manager.HandleArmed();      break;
                case FlightState::LAUNCH:     manager.HandleLaunch();     break;
                case FlightState::ASCENT:     manager.HandleAscent();     break;
                case FlightState::APOGEE:     manager.HandleApogee();     break;
                case FlightState::DESCENT:    manager.HandleDescent();    break;
                case FlightState::LANDED:     manager.HandleLanded();     break;
                case FlightState::FAILSAFE:   manager.HandleFailsafe();   break;
                default: break;
            }

            lastStateMs = now;
        }
    }
}