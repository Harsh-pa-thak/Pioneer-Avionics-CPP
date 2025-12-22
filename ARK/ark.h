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
* File:        ark.h
* Author:      Kunsh Jain
* Created On:  2025-12-22
* Brief:       Ark application class declaration.
* Description: Declares application lifecycle methods and the main Loops instance.
***************************************************************************************************
* HISTORY:
* +----- (NEW | MODify | ADD | DELete)
* |
* No#   |       when       who                  what
******+*********+**********+********************+**************************************************
* 000  NEW      2025-12-22   Kunsh Jain           Added standard header and Doxygen
**************************************************************************************************/

#ifndef ARK_H
#define ARK_H

// NOTE: File header and Doxygen comments added; behavior unchanged.

#include "pico/stdlib.h"
#include "kernel/loops.h"

/**
 * \brief Top-level application object for Pioneer firmware.
 */
class Ark {
public:
    /** \brief Construct application object. */
    Ark();
    /** \brief Destruct application object. */
    ~Ark();

    /** \brief Initialize platform and peripherals. */
    void Init();
    /** \brief Enter main execution loop. */
    void Start();
    /** \brief Stop execution (blocks). */
    void Stop();

private:
    Loops main_loop; // Instance of the class defined in loops.h
};

#endif