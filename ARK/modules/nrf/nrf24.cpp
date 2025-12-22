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
* File:        nrf24.cpp
* Author:      Kunsh Jain
* Created On:  2025-12-22
* Brief:       NRF24 minimal SPI helper implementation.
* Description: Controls CS/CE lines and performs SPI transfers for send operations.
***************************************************************************************************
* HISTORY:
* +----- (NEW | MODify | ADD | DELete)
* |
* No#   |       when       who                  what
******+*********+**********+********************+**************************************************
* 000  NEW      2025-12-22   Kunsh Jain           Added header and Doxygen
**************************************************************************************************/

#include "nrf24.h"

/** \brief Construct radio helper with SPI instance and control pins. */
NRF24::NRF24(spi_inst_t* spi, uint cs, uint ce) : _spi(spi), _cs(cs), _ce(ce) {}

/** \brief Initialize CS/CE GPIO lines. */
void NRF24::Init() {
    gpio_init(_cs);
    gpio_init(_ce);
    gpio_set_dir(_cs, GPIO_OUT);
    gpio_set_dir(_ce, GPIO_OUT);
    gpio_put(_cs, 1);
    gpio_put(_ce, 0);
}

/** \brief Send `len` bytes over SPI with CS toggle and a short CE pulse. */
void NRF24::Send(const uint8_t* data, size_t len) {
    gpio_put(_cs, 0);
    spi_write_blocking(_spi, data, len);
    gpio_put(_cs, 1);
    gpio_put(_ce, 1);
    sleep_us(15);
    gpio_put(_ce, 0);
}