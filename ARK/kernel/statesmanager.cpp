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

StatesManager::StatesManager() { currentState = FlightState::BOOT; }
void StatesManager::SetState(FlightState newState) { currentState = newState; }
FlightState StatesManager::GetState() const { return currentState; }

void StatesManager::HandleBoot()       { onUserLogic(currentState); }
void StatesManager::HandleIdle()       { onUserLogic(currentState); }
void StatesManager::HandleArmed()      { onUserLogic(currentState); }
void StatesManager::HandleLaunch()     { onUserLogic(currentState); }
void StatesManager::HandleAscent()     { onUserLogic(currentState); }
void StatesManager::HandleCruising()   { onUserLogic(currentState); }
void StatesManager::HandleApogee()     { onUserLogic(currentState); }
void StatesManager::HandleDeployment() { onUserLogic(currentState); }
void StatesManager::HandleDescent()    { onUserLogic(currentState); }
void StatesManager::HandleLanded()     { onUserLogic(currentState); }
void StatesManager::HandleFailsafe()   { onUserLogic(currentState); }

