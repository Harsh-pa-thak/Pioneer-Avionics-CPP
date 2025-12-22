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
* File:        nrf24.h
* Author:      Kunsh Jain
* Created On:  2025-12-22
* Brief:       Minimal NRF24 radio helper.
* Description: Provides basic SPI CS/CE control and send helper.
***************************************************************************************************
* HISTORY:
* +----- (NEW | MODify | ADD | DELete)
* |
* No#   |       when       who                  what
******+*********+**********+********************+**************************************************
* 000  NEW      2025-12-22   Kunsh Jain           Added header and Doxygen
**************************************************************************************************/

#ifndef NRF24_H
#define NRF24_H

#include "pico/stdlib.h"
#include "hardware/spi.h"

/** \brief Minimal helper for NRF24 SPI radio. */
class NRF24 {
public:
    NRF24(spi_inst_t* spi = spi1, uint cs = 13, uint ce = 16);
    void Init();
    void Send(const uint8_t* data, size_t len);
private:
    spi_inst_t* _spi;
    uint _cs, _ce;
};

#endif