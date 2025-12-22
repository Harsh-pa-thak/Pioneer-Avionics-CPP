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
* File:        mpu9250.cpp
* Author:      Kunsh Jain
* Created On:  2025-12-22
* Brief:       MPU9250 I2C driver implementation.
* Description: Implements basic wake/init and sensor read helpers.
***************************************************************************************************
* HISTORY:
* +----- (NEW | MODify | ADD | DELete)
* |
* No#   |       when       who                  what
******+*********+**********+********************+**************************************************
* 000  NEW      2025-12-22   Kunsh Jain           Added header and Doxygen
**************************************************************************************************/

#include "mpu9250.h"

/** \brief Construct MPU wrapper with an I2C instance. */
MPU9250::MPU9250(i2c_inst_t* i2c_inst) : _i2c(i2c_inst) {}

/** \brief Initialize MPU9250 (wake from sleep). */
bool MPU9250::Init() {
    uint8_t wake[] = {0x6B, 0x00};
    i2c_write_blocking(_i2c, addr, wake, 2, false);
    return true;
}

/** \brief Read accelerometer, gyro and temperature data. */
void MPU9250::ReadData(float* acc, float* gyro, float* temp) {
    uint8_t reg = 0x3B;
    uint8_t data[14];
    i2c_write_blocking(_i2c, addr, &reg, 1, true);
    i2c_read_blocking(_i2c, addr, data, 14, false);

    acc[0] = (int16_t)(data[0] << 8 | data[1]) / 16384.0f;
    acc[1] = (int16_t)(data[2] << 8 | data[3]) / 16384.0f;
    acc[2] = (int16_t)(data[4] << 8 | data[5]) / 16384.0f;
    *temp = ((int16_t)(data[6] << 8 | data[7]) / 333.87f) + 21.0f;
    gyro[0] = (int16_t)(data[8] << 8 | data[9]) / 131.0f;
    gyro[1] = (int16_t)(data[10] << 8 | data[11]) / 131.0f;
    gyro[2] = (int16_t)(data[12] << 8 | data[13]) / 131.0f;
}