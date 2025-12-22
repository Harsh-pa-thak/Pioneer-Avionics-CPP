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
* File:        l89ha.cpp
* Author:      Kunsh Jain
* Created On:  2025-12-22
* Brief:       L89HA GNSS receiver implementation.
* Description: UART initialization and raw read helper implementation.
***************************************************************************************************
* HISTORY:
* +----- (NEW | MODify | ADD | DELete)
* |
* No#   |       when       who                  what
******+*********+**********+********************+**************************************************
* 000  NEW      2025-12-22   Kunsh Jain           Added header and Doxygen
**************************************************************************************************/

#include "l89ha.h"

/** \brief Construct GNSS wrapper specifying UART instance and baud. */
L89HA::L89HA(uart_inst_t* uart, uint baud) : _uart(uart), _baud(baud) {}

/** \brief Initialize UART pins and baudrate for GNSS receiver. */
void L89HA::Init(uint tx, uint rx) {
    uart_init(_uart, _baud);
    gpio_set_function(tx, GPIO_FUNC_UART);
    gpio_set_function(rx, GPIO_FUNC_UART);
}

/** \brief Read available raw bytes from GNSS into `buffer`. Returns bytes read. */
int L89HA::ReadRaw(char* buffer, size_t len) {
    int i = 0;
    while (uart_is_readable(_uart) && i < (int)len - 1) {
        buffer[i++] = uart_getc(_uart);
    }
    buffer[i] = '\0';
    return i;
}