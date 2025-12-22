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
* File:        sdcard.h
* Author:      Kunsh Jain
* Created On:  2025-12-22
* Brief:       SD card SPI helper interface.
* Description: Minimal helpers to initialize SPI, create CSV header and append log data.
***************************************************************************************************
* HISTORY:
* +----- (NEW | MODify | ADD | DELete)
* |
* No#   |       when       who                  what
******+*********+**********+********************+**************************************************
* 000  NEW      2025-12-22   Kunsh Jain           Added header and Doxygen
**************************************************************************************************/

#ifndef SDCARD_H
#define SDCARD_H

#include "pico/stdlib.h"
#include "hardware/spi.h"
#include <string>
#include <vector>

typedef struct FATFS FATFS;
typedef struct FIL FIL;

/** \brief Minimal SD card helper that performs SPI init and write operations. */
class SDCard {
public:
    SDCard(spi_inst_t* spi = spi1, uint sck = 14, uint mosi = 15, uint miso = 12, uint cs = 13);
    
    bool Init();
    bool CreateCSV(const std::string& filename, const std::vector<std::string>& headers);
    bool LogData(const std::string& filename, const std::string& data);

private:
    spi_inst_t* _spi;
    uint _sck, _mosi, _miso, _cs;
    bool _isMounted = false;

    // Internal SPI-level helpers
    uint8_t SendCommand(uint8_t cmd, uint32_t arg, uint8_t crc);
    void Select();
    void Deselect();
};

#endif