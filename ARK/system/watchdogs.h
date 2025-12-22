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
* File:        watchdogs.h
* Author:      Kunsh Jain
* Created On:  2025-12-22
* Brief:       Simple watchdog helper interface.
* Description: Tracks last kick time and detects timeout conditions.
***************************************************************************************************
* HISTORY:
* +----- (NEW | MODify | ADD | DELete)
* |
* No#   |       when       who                  what
******+*********+**********+********************+**************************************************
* 000  NEW      2025-12-22   Kunsh Jain           Added header and Doxygen
**************************************************************************************************/

#ifndef WATCHDOGS_H
#define WATCHDOGS_H

#include <stdint.h>

/** \brief Very small watchdog timer helper. */
class Watchdogs {
public:
    Watchdogs();
    void Init(uint32_t timeout_ms);
    void Reset();
    bool IsCheckFailed();

private:
    uint32_t last_kick_time;
    uint32_t timeout_limit;
};

#endif