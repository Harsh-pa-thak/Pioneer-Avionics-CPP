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
**************************************************************************************************/

#include "../../ARK/kernel/statesmanager.h"

void StatesManager::onUserLogic(FlightState state) {
    switch(state) {
        case FlightState::IDLE:
            // Check sensors to trigger launch
            break;
        case FlightState::ASCENT:
            // Monitor for Apogee
            break;
        case FlightState::APOGEE:
            // Deploy chutes
            SetState(FlightState::DESCENT);
            break;
        case FlightState::LANDED:
            // Finalize logs
            break;
        default:
            break;
    }
}