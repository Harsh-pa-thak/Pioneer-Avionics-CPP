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
* File:        watchdogs.cpp
* Author:      Kunsh Jain
* Created On:  2025-12-22
* Brief:       Watchdog helper implementation.
* Description: Implements timeout logic based on `timer.hpp` helper.
***************************************************************************************************
* HISTORY:
* +----- (NEW | MODify | ADD | DELete)
* |
* No#   |       when       who                  what
******+*********+**********+********************+**************************************************
* 000  NEW      2025-12-22   Kunsh Jain           Added header and Doxygen
**************************************************************************************************/

#include "watchdogs.h"
#include "timer.hpp"

/** \brief Construct watchdog with zeroed timers. */
Watchdogs::Watchdogs() : last_kick_time(0), timeout_limit(0) {}

/** \brief Initialize watchdog timeout in milliseconds. */
void Watchdogs::Init(uint32_t timeout_ms) {
    timeout_limit = timeout_ms;
    last_kick_time = millis();
}

/** \brief Reset watchdog timer (kick). */
void Watchdogs::Reset() {
    last_kick_time = millis();
}

/** \brief Check whether timeout has occurred. */
bool Watchdogs::IsCheckFailed() {
    return (millis() - last_kick_time) > timeout_limit;
}