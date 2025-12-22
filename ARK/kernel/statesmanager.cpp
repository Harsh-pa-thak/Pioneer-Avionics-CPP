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
* File:        statesmanager.cpp
* Author:      Kunsh Jain
* Created On:  2025-12-22
* Brief:       Simple flight state manager implementation.
* Description: Holds current state and provides empty handlers for each state.
***************************************************************************************************
* HISTORY:
* +----- (NEW | MODify | ADD | DELete)
* |
* No#   |       when       who                  what
******+*********+**********+********************+**************************************************
* 000  NEW      2025-12-22   Kunsh Jain           Added header and Doxygen
**************************************************************************************************/

#include "statesmanager.h"

/** \brief Construct and set initial flight state to BOOT. */
StatesManager::StatesManager() {
    currentState = FlightState::BOOT;
}

/** \brief Default destructor. */
StatesManager::~StatesManager() {
}

/** \brief Set the current flight state. */
void StatesManager::SetState(FlightState newState) {
    currentState = newState;
}

/** \brief Get the current flight state. */
FlightState StatesManager::GetState() const {
    return currentState;
}

// State handlers (currently stubs; implement logic as required)
void StatesManager::HandleBoot() {}
void StatesManager::HandleIdle() {}
void StatesManager::HandleArmed() {}
void StatesManager::HandleLaunch() {}
void StatesManager::HandleAscent() {}
void StatesManager::HandleCruising() {}
void StatesManager::HandleApogee() {}
void StatesManager::HandleDeployment() {}
void StatesManager::HandleDescent() {}
void StatesManager::HandleLanded() {}
void StatesManager::HandleFailsafe() {}