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
* File:        statesmanager.h
* Author:      Kunsh Jain
* Created On:  2025-12-22
* Brief:       Flight state definitions and manager interface.
* Description: Declares `FlightState` enum and `StatesManager` which encapsulates
*              state transitions and handlers.
***************************************************************************************************
* HISTORY:
* +----- (NEW | MODify | ADD | DELete)
* |
* No#   |       when       who                  what
******+*********+**********+********************+**************************************************
* 000  NEW      2025-12-22   Kunsh Jain           Added header and Doxygen
**************************************************************************************************/
#ifndef STATESMANAGER_H
#define STATESMANAGER_H

#include <string>
    
enum class FlightState {
    BOOT, IDLE, ARMED, LAUNCH, ASCENT, CRUISING, 
    APOGEE, DEPLOYMENT, DESCENT, LANDED, FAILSAFE
};

class StatesManager {
public:
    StatesManager();
    void onUserLogic(FlightState state);
    void HandleBoot(); void HandleIdle(); void HandleArmed();
    void HandleLaunch(); void HandleAscent(); void HandleCruising();
    void HandleApogee(); void HandleDeployment(); void HandleDescent();
    void HandleLanded(); void HandleFailsafe();
    void SetState(FlightState newState);
    FlightState GetState() const;
private:
    FlightState currentState;
};

#endif // STATESMANAGER_H