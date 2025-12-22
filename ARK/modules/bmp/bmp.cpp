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
* File:        bmp.cpp
* Author:      Kunsh Jain
* Created On:  2025-12-22
* Brief:       BMP280 sensor driver implementation.
* Description: Implements initialization, calibration and raw reads for BMP280.
***************************************************************************************************
* HISTORY:
* +----- (NEW | MODify | ADD | DELete)
* |
* No#   |       when       who                  what
******+*********+**********+********************+**************************************************
* 000  NEW      2025-12-22   Kunsh Jain           Added header and Doxygen
**************************************************************************************************/

#include "bmp.h"

/** \brief Construct BMP280 wrapper with I2C instance and address. */
BMP280::BMP280(i2c_inst_t* i2c_instance, uint8_t addr) 
    : i2c(i2c_instance), address(addr), t_fine(0), seaLevelPressure(1013.25f) {}

/** \brief Initialize BMP280 on given SDA/SCL pins. */
bool BMP280::Init(uint sda, uint scl, uint32_t baudrate) {
    i2c_init(i2c, baudrate);
    gpio_set_function(sda, GPIO_FUNC_I2C);
    gpio_set_function(scl, GPIO_FUNC_I2C);
    gpio_pull_up(sda);
    gpio_pull_up(scl);

    uint8_t id;
    uint8_t reg = 0xD0;
    i2c_write_blocking(i2c, address, &reg, 1, true);
    i2c_read_blocking(i2c, address, &id, 1, false);

    if (id != 0x58) return false;

    ReadCalibration();

    uint8_t config[2];
    config[0] = 0xF4;
    config[1] = 0x27;
    i2c_write_blocking(i2c, address, config, 2, false);

    return true;
}

/** \brief Read calibration block from device into `calib`. */
void BMP280::ReadCalibration() {
    uint8_t data[24];
    uint8_t reg = 0x88;
    i2c_write_blocking(i2c, address, &reg, 1, true);
    i2c_read_blocking(i2c, address, data, 24, false);

    calib.dig_T1 = data[1] << 8 | data[0];
    calib.dig_T2 = data[3] << 8 | data[2];
    calib.dig_T3 = data[5] << 8 | data[4];
    calib.dig_P1 = data[7] << 8 | data[6];
    calib.dig_P2 = data[9] << 8 | data[8];
    calib.dig_P3 = data[11] << 8 | data[10];
    calib.dig_P4 = data[13] << 8 | data[12];
    calib.dig_P5 = data[15] << 8 | data[14];
    calib.dig_P6 = data[17] << 8 | data[16];
    calib.dig_P7 = data[19] << 8 | data[18];
    calib.dig_P8 = data[21] << 8 | data[20];
    calib.dig_P9 = data[23] << 8 | data[22];
}

/** \brief Read raw pressure/temp ADC values from sensor. */
void BMP280::GetRawData(int32_t &adc_P, int32_t &adc_T) {
    uint8_t data[6];
    uint8_t reg = 0xF7;
    i2c_write_blocking(i2c, address, &reg, 1, true);
    i2c_read_blocking(i2c, address, data, 6, false);

    adc_P = (data[0] << 12) | (data[1] << 4) | (data[2] >> 4);
    adc_T = (data[3] << 12) | (data[4] << 4) | (data[5] >> 4);
}

/** \brief Get compensated temperature in degrees Celsius. */
float BMP280::ReadTemperature() {
    int32_t p, t;
    GetRawData(p, t);
    return CompensateTemp(t) / 100.0f;
}

/** \brief Get compensated pressure (returns hPa). */
float BMP280::ReadPressure() {
    int32_t p, t;
    GetRawData(p, t);
    CompensateTemp(t); 
    return CompensatePressure(p) / 25600.0f; // Returns hPa
}

/** \brief Compute altitude (meters) from pressure using barometric formula. */
float BMP280::ReadAltitude(float seaLevelhPa) {
    float pressure = ReadPressure();
    return 44330.0f * (1.0f - pow(pressure / seaLevelhPa, 0.1903f));
}

/** \brief Calibrate sea-level pressure based on a known altitude. */
void BMP280::CalibrateSeaLevel(float knownAltitude) {
    float pressure = ReadPressure();
    seaLevelPressure = pressure / pow(1.0f - (knownAltitude / 44330.0f), 5.255f);
}

int32_t BMP280::CompensateTemp(int32_t adc_T) {
    int32_t var1, var2;
    var1 = ((((adc_T >> 3) - ((int32_t)calib.dig_T1 << 1))) * ((int32_t)calib.dig_T2)) >> 11;
    var2 = (((((adc_T >> 4) - ((int32_t)calib.dig_T1)) * ((adc_T >> 4) - ((int32_t)calib.dig_T1))) >> 12) * ((int32_t)calib.dig_T3)) >> 14;
    t_fine = var1 + var2;
    return (t_fine * 5 + 128) >> 8;
}

uint32_t BMP280::CompensatePressure(int32_t adc_P) {
    int64_t var1, var2, p;
    var1 = ((int64_t)t_fine) - 128000;
    var2 = var1 * var1 * (int64_t)calib.dig_P6;
    var2 = var2 + ((var1 * (int64_t)calib.dig_P5) << 17);
    var2 = var2 + ((int64_t)calib.dig_P4 << 35);
    var1 = ((var1 * var1 * (int64_t)calib.dig_P3) >> 8) + ((var1 * (int64_t)calib.dig_P2) << 12);
    var1 = (((((int64_t)1) << 47) + var1)) * ((int64_t)calib.dig_P1) >> 33;
    if (var1 == 0) return 0;
    p = 1048576 - adc_P;
    p = (((p << 31) - var2) * 3125) / var1;
    var1 = (((int64_t)calib.dig_P9) * (p >> 13) * (p >> 13)) >> 25;
    var2 = (((int64_t)calib.dig_P8) * p) >> 19;
    p = ((p + var1 + var2) >> 8) + ((int64_t)calib.dig_P7 << 4);
    return (uint32_t)p;
}