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
* File:        loops.h
* Author:      Kunsh Jain
* Created On:  2025-12-22
* Brief:       Main loop declarations.
* Description: Contains the `Loops` class used to run periodic tasks.
***************************************************************************************************
* HISTORY:
* +----- (NEW | MODify | ADD | DELete)
* |
* No#   |       when       who                  what
******+*********+**********+********************+**************************************************
* 000  NEW      2025-12-22   Kunsh Jain           Added header and Doxygen
**************************************************************************************************/

#ifndef LOOPS_H
#define LOOPS_H

// NOTE: Header and Doxygen added. No logic changes.

#include "statesmanager.h"
#include "../../tests/test.hpp" 
#include "../system/watchdogs.h"
#include "../system/timer.hpp"
#include "../system/sensors.h"

/**
 * \brief Main periodic loop runner.
 * \details Calls sensor updates, streams telemetry and manages state transitions.
 */
class Loops {
public:
    /** \brief Construct Loops and initialize subsystems. */
    Loops();
    /** \brief Run the main loop (blocking). */
    void Run();

private:
    void StreamTelemetry();
    StatesManager manager;
    Watchdogs wdt; 
    SensorManager sensors;
};

#endif