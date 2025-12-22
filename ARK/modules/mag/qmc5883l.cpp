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
* File:        qmc5883l.cpp
* Author:      Kunsh Jain
* Created On:  2025-12-22
* Brief:       QMC5883L magnetometer implementation.
* Description: Implements init, raw reads and heading computation.
***************************************************************************************************
* HISTORY:
* +----- (NEW | MODify | ADD | DELete)
* |
* No#   |       when       who                  what
******+*********+**********+********************+**************************************************
* 000  NEW      2025-12-22   Kunsh Jain           Added header and Doxygen
**************************************************************************************************/

#include "qmc5883l.h"

/** \brief Construct with I2C instance. */
QMC5883L::QMC5883L(i2c_inst_t* i2c) : _i2c(i2c) {}

/** \brief Initialize magnetometer registers. */
bool QMC5883L::Init() {
    uint8_t cfg1[] = {0x0B, 0x01};
    i2c_write_blocking(_i2c, addr, cfg1, 2, false);
    uint8_t cfg2[] = {0x09, 0x1D};
    i2c_write_blocking(_i2c, addr, cfg2, 2, false);
    return true;
}

/** \brief Read raw X/Y/Z magnetometer registers. */
void QMC5883L::ReadRaw(int16_t &x, int16_t &y, int16_t &z) {
    uint8_t reg = 0x00;
    uint8_t data[6];
    i2c_write_blocking(_i2c, addr, &reg, 1, true);
    i2c_read_blocking(_i2c, addr, data, 6, false);
    x = (int16_t)(data[1] << 8 | data[0]);
    y = (int16_t)(data[3] << 8 | data[2]);
    z = (int16_t)(data[5] << 8 | data[4]);
}

/** \brief Compute a simple heading (deg) from X/Y. */
float QMC5883L::GetHeading() {
    int16_t x, y, z;
    ReadRaw(x, y, z);
    float h = atan2((float)y, (float)x) * 180.0f / M_PI;
    if (h < 0) h += 360.0f;
    return h;
}