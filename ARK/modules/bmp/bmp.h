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
* File:        bmp.h
* Author:      Kunsh Jain
* Created On:  2025-12-22
* Brief:       BMP280 sensor driver interface.
* Description: Provides basic BMP280 initialization and read interfaces.
***************************************************************************************************
* HISTORY:
* +----- (NEW | MODify | ADD | DELete)
* |
* No#   |       when       who                  what
******+*********+**********+********************+**************************************************
* 000  NEW      2025-12-22   Kunsh Jain           Added header and Doxygen
**************************************************************************************************/

#ifndef BMP_H
#define BMP_H

#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "../../tests/test.hpp"
#include <cmath>

/**
 * \brief Hardware abstraction for BMP280 barometric sensor.
 */
class BMP280 {
public:
    struct CalibrationData {
        uint16_t dig_T1;
        int16_t  dig_T2, dig_T3;
        uint16_t dig_P1;
        int16_t  dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9;
    };

    /** \brief Construct with given I2C instance and optional address. */
    BMP280(i2c_inst_t* i2c_instance, uint8_t addr = 0x76);
    
    /** \brief Initialize BMP on provided SDA/SCL pins. */
    bool Init(uint sda, uint scl, uint32_t baudrate = 400000);
    
    /** \brief Read compensated temperature in deg C. */
    float ReadTemperature();
    /** \brief Read compensated pressure (hPa). */
    float ReadPressure();
    /** \brief Compute altitude from pressure (meters). */
    float ReadAltitude(float seaLevelhPa = 1013.25f);
    
    /** \brief Calibrate sea-level pressure using a known altitude. */
    void CalibrateSeaLevel(float knownAltitude);

private:
    i2c_inst_t* i2c;
    uint8_t address;
    CalibrationData calib;
    int32_t t_fine;
    float seaLevelPressure;

    void ReadCalibration();
    int32_t CompensateTemp(int32_t adc_T);
    uint32_t CompensatePressure(int32_t adc_P);
    void GetRawData(int32_t &adc_P, int32_t &adc_T);
};

#endif