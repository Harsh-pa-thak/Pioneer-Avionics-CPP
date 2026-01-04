#/*
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
* File:        ark.cpp
* Author:      Kunsh Jain
* Created On:  2025-12-22
* Brief:       Ark application entrypoint implementation.
* Description: Implements simple lifecycle methods that start the main loop.
***************************************************************************************************
* HISTORY:
* +----- (NEW | MODify | ADD | DELete)
* |
* No#   |       when       who                  what
******+*********+**********+********************+**************************************************
* 000  NEW      2025-12-22   Kunsh Jain           Added header and Doxygen stubs
**************************************************************************************************/

// NOTE: Only headers and Doxygen comments were added. No behavior changed.

#include "ark.h"
SensorManager sensors;
/**
 * \brief Default constructor for `Ark`.
 */
Ark::Ark() {}

/**
 * \brief Default destructor for `Ark`.
 */
Ark::~Ark() {}

/**
 * \brief Initialize platform I/O used by application.
 * \details Calls `stdio_init_all()` to set up console/USB stdio for logging.
 */
void Ark::Init() {
    stdio_init_all();
}

/**
 * \brief Start the main runtime loop.
 */
void Ark::Start() {
    main_loop.Run();
}

/**
 * \brief Stop the application by entering a tight loop.
 */
void Ark::Stop() {
    while (true) {
        tight_loop_contents();
    }
}