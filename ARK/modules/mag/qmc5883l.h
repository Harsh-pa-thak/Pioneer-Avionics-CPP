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
* File:        qmc5883l.h
* Author:      Kunsh Jain
* Created On:  2025-12-22
* Brief:       QMC5883L magnetometer interface.
* Description: Provides init and raw read helpers plus a simple heading computation.
***************************************************************************************************
* HISTORY:
* +----- (NEW | MODify | ADD | DELete)
* |
* No#   |       when       who                  what
******+*********+**********+********************+**************************************************
* 000  NEW      2025-12-22   Kunsh Jain           Added header and Doxygen
**************************************************************************************************/

#ifndef QMC5883L_H
#define QMC5883L_H

#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include <cmath>

/** \brief QMC5883L magnetometer helper. */
class QMC5883L {
public:
    QMC5883L(i2c_inst_t* i2c = i2c1);
    bool Init();
    void ReadRaw(int16_t &x, int16_t &y, int16_t &z);
    float GetHeading();
private:
    i2c_inst_t* _i2c;
    const uint8_t addr = 0x0D;
};

#endif