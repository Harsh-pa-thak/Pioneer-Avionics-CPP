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
* File:        l89ha.h
* Author:      Kunsh Jain
* Created On:  2025-12-22
* Brief:       L89HA GNSS receiver interface.
* Description: Minimal UART-based GNSS wrapper for raw reads.
***************************************************************************************************
* HISTORY:
* +----- (NEW | MODify | ADD | DELete)
* |
* No#   |       when       who                  what
******+*********+**********+********************+**************************************************
* 000  NEW      2025-12-22   Kunsh Jain           Added header and Doxygen
**************************************************************************************************/

#ifndef L89HA_H
#define L89HA_H

#include "pico/stdlib.h"
#include "hardware/uart.h"

/** \brief Simple UART GNSS helper for L89HA module. */
class L89HA {
public:
    L89HA(uart_inst_t* uart = uart0, uint baud = 9600);
    void Init(uint tx = 0, uint rx = 1);
    int ReadRaw(char* buffer, size_t len);
private:
    uart_inst_t* _uart;
    uint _baud;
};

#endif