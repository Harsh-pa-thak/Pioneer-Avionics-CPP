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
* File:        mpu9250.h
* Author:      Kunsh Jain
* Created On:  2025-12-22
* Brief:       MPU9250/MPU-family IMU interface.
* Description: Provides Init and ReadData methods for accelerometer, gyro and temp.
***************************************************************************************************
* HISTORY:
* +----- (NEW | MODify | ADD | DELete)
* |
* No#   |       when       who                  what
******+*********+**********+********************+**************************************************
* 000  NEW      2025-12-22   Kunsh Jain           Added header and Doxygen
**************************************************************************************************/

#ifndef MPU9250_H
#define MPU9250_H

#include "pico/stdlib.h"
#include "hardware/i2c.h"

/** \brief Simple MPU9250 wrapper for I2C reads. */
class MPU9250 {
public:
    MPU9250(i2c_inst_t* i2c_inst = i2c1);
    bool Init();
    void ReadData(float* acc, float* gyro, float* temp);
private:
    i2c_inst_t* _i2c;
    const uint8_t addr = 0x68;
};

#endif