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
* File:        sensors.h
* Author:      Kunsh Jain
* Created On:  2025-12-22
* Brief:       Sensor manager public interface for Pioneer project.
* Description: Declares `SensorManager` which aggregates BMP, MAG, MPU, GPS, SD, NRF and Buzzer.
***************************************************************************************************
* HISTORY:
* +----- (NEW | MODify | ADD | DELete)
* |
* No#   |       when       who                  what
******+*********+**********+********************+**************************************************
* 000  NEW      2025-12-22   Kunsh Jain           Added standard header and Doxygen stubs
**************************************************************************************************/

#ifndef SENSORS_H
#define SENSORS_H

// NOTE: This file was updated to include the project standard header and
// Doxygen documentation. No functional logic changed — only comments and
// declarations were added for documentation and compliance.

#include "pico/stdlib.h"
#include <string>
#include <vector>
#include "../modules/bmp/bmp.h"
#include "../modules/mag/qmc5883l.h"
#include "../modules/mpu/mpu9250.h"
#include "../modules/gnss/l89ha.h"
#include "../modules/sdcard/sdcard.h"
#include "../modules/nrf/nrf24.h"
#include "../modules/buzzer/buzzer.h"

/**
 * \brief Manager for all board sensors and telemetry output.
 * \details Aggregates sensor drivers (BMP280, QMC5883L, MPU9250, L89HA GPS),
 *          SD logging, NRF radio transmission and buzzer feedback. Initialization
 *          runs a Power-On Self-Test (POST) and prepares CSV logging when healthy.
 */
class SensorManager {
public:
    /**
     * \brief Construct a SensorManager instance.
     * \details Initializes member driver objects with default peripherals.
     */
    SensorManager();

    /**
     * \brief Run initialization sequence for all subsystems.
     * \details Performs POST, toggles LED/buzzer, initializes drivers and
     *          creates CSV header on SD card when the system is healthy.
     */
    void InitAll();

    /**
     * \brief Periodic update to read sensors and transmit/log data.
     */
    void Update();
    
    /**
     * \brief Get latest telemetry packet string.
     */
    std::string GetPacket() const { return _packet; }

    /**
     * \brief Query overall system health after InitAll().
     */
    bool IsHealthy() const { return _systemOk; }

private:
    BMP280 _bmp;
    QMC5883L _mag;
    MPU9250 _mpu;
    L89HA _gps;
    SDCard _sd;
    NRF24 _nrf;
    Buzzer _buzz;

    const uint LED_PIN = 25; 
    float _alt = 0.0f, _temp = 0.0f, _hdg = 0.0f;
    float _ax=0, _ay=0, _az=0, _gx=0, _gy=0, _gz=0, _mx=0, _my=0, _mz=0;
    
    bool _b_ok=0, _m_ok=0, _imu_ok=0, _s_ok=0, _g_ok=0, _n_ok=0;
    bool _systemOk = false;
    std::string _packet = "INIT";
    
    /**
     * \brief Build human-readable telemetry string stored in `_packet`.
     */
    void BuildPacket();

    /**
     * \brief Helper to print status info during POST.
     * \param name  Short name of subsystem
     * \param ok    true if subsystem passed its init
     * \param val   short data string to print alongside status
     */
    void PrintStatus(const char* name, bool ok, const char* val);
};

#endif