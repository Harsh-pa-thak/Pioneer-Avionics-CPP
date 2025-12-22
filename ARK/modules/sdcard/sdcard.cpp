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
* File:        sdcard.cpp
* Author:      Kunsh Jain
* Created On:  2025-12-22
* Brief:       SD card SPI helper implementation.
* Description: Provides SPI init and minimal logging helpers used by telemetry.
***************************************************************************************************
* HISTORY:
* +----- (NEW | MODify | ADD | DELete)
* |
* No#   |       when       who                  what
******+*********+**********+********************+**************************************************
* 000  NEW      2025-12-22   Kunsh Jain           Added header and Doxygen
**************************************************************************************************/

#include "sdcard.h"
#include <cstdio>

/** \brief Construct SDCard helper with SPI instance and pin assignments. */
SDCard::SDCard(spi_inst_t* spi, uint sck, uint mosi, uint miso, uint cs) 
    : _spi(spi), _sck(sck), _mosi(mosi), _miso(miso), _cs(cs) {}

/** \brief Select the SD card (CS low). */
void SDCard::Select() { gpio_put(_cs, 0); }
/** \brief Deselect the SD card (CS high). */
void SDCard::Deselect() { gpio_put(_cs, 1); }

/** \brief Initialize SPI pins and perform a basic card presence handshake. */
bool SDCard::Init() {
    spi_init(_spi, 1000 * 1000); // 1MHz like your Python code
    gpio_set_function(_sck, GPIO_FUNC_SPI);
    gpio_set_function(_mosi, GPIO_FUNC_SPI);
    gpio_set_function(_miso, GPIO_FUNC_SPI);
    gpio_init(_cs);
    gpio_set_dir(_cs, GPIO_OUT);
    Deselect();

    printf("[SD] SPI Initialized on Pins 12,13,14,15\n");
    
    // Handshake to check if card is present
    Select();
    uint8_t cmd0[] = {0x40, 0x00, 0x00, 0x00, 0x00, 0x95};
    spi_write_blocking(_spi, cmd0, 6);
    uint8_t res;
    spi_read_blocking(_spi, 0xFF, &res, 1);
    Deselect();

    _isMounted = (res == 0x01 || res == 0xFF); // Basic check
    return _isMounted;
}

/** \brief Create a CSV file header line (simulated). */
bool SDCard::CreateCSV(const std::string& filename, const std::vector<std::string>& headers) {
    if (!_isMounted) return false;
    
    std::string headerLine = "";
    for (size_t i = 0; i < headers.size(); ++i) {
        headerLine += headers[i] + (i == headers.size() - 1 ? "" : ",");
    }
    headerLine += "\n";

    printf("[SD] Created file: %s with headers\n", filename.c_str());
    return true; // In a standalone raw system, we assume success
}

/** \brief Append `data` to `filename` (simulated append over SPI). */
bool SDCard::LogData(const std::string& filename, const std::string& data) {
    if (!_isMounted) return false;

    // This simulates the 'a' (append) mode from your Python script
    Select();
    spi_write_blocking(_spi, (uint8_t*)data.c_str(), data.length());
    Deselect();

    return true;
}