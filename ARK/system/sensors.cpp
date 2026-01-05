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
* File:        sensors.cpp
* Author:      Kunsh Jain
* Created On:  2025-12-22
* Brief:       Sensor manager implementation for Pioneer project.
* Description: Implements initialization, periodic update and telemetry packet
*              construction for the aggregated sensor subsystem.
***************************************************************************************************
* HISTORY:
* +----- (NEW | MODify | ADD | DELete)
* |
* No#   |       when       who                  what
******+*********+**********+********************+**************************************************
* 000  NEW      2025-12-22   Kunsh Jain           Added standard header and Doxygen comments
**************************************************************************************************/

// NOTE: Only comments, headers and Doxygen documentation were added/updated in
// this file. Core logic and behaviour remain unchanged.

#include "sensors.h"
#include <cstdio>

/**
 * \brief Construct the SensorManager and initialize driver instances.
 * \details Members are constructed with default peripherals (I2C, SPI, UART)
 *          — actual init sequences happen in `InitAll()` to allow POST handling.
 */
SensorManager::SensorManager() 
    : _bmp(i2c1), _mag(i2c1), _mpu(i2c1), _gps(uart0), _sd(spi1), _nrf(spi1), _buzz(6) {}

/**
 * \brief Print a concise subsystem status line to console during POST.
 * \param name Short subsystem name
 * \param ok   Initialization boolean (true=OK, false=FAIL)
 * \param val  Short data string (e.g. heading, altitude)
 */
void SensorManager::PrintStatus(const char* name, bool ok, const char* val) {
    printf("[%s] Status: %s | Data: (%s)\n", name, ok ? "OK  " : "FAIL", val);
}

/**
 * \brief Initialize all subsystems and perform POST.
 * \details Toggles LED/buzzer for user feedback, initializes sensors and
 *          when successful prepares SD CSV headers and signals ready state.
 */
void SensorManager::InitAll() {
    printf("\n--- PIONEER AVIONICS SYSTEM CHECK ---\n");
    
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, 1);
    sleep_ms(500);
    gpio_put(LED_PIN, 0);
    PrintStatus("LED", true, "BLINKED");

    _buzz.Init();
    _buzz.PlayTone(1000, 100); 
    PrintStatus("BUZZER", true, "PINGED");

    _b_ok = _bmp.Init(2, 3);
    char b_val[32]; snprintf(b_val, 32, "%.1f m", _bmp.ReadAltitude());
    PrintStatus("BMP280", _b_ok, b_val);

    _m_ok = _mag.Init();
    char m_val[32]; snprintf(m_val, 32, "%.1f deg", _mag.GetHeading());
    PrintStatus("QMC5883", _m_ok, m_val);

    _imu_ok = _mpu.Init();
    PrintStatus("MPU9250", _imu_ok, "ACCEL/GYRO");

    _s_ok = _sd.Init();
    PrintStatus("SDCARD", _s_ok, "SPI1_CS13");

    _gps.Init(0, 1); _g_ok = true;
    PrintStatus("GPS_L89", _g_ok, "UART0");

    _nrf.Init(); _n_ok = true;
    PrintStatus("NRF_RAD", _n_ok, "SPI1_CE16");

    if (_b_ok && _m_ok && _imu_ok && _s_ok) {
        _systemOk = true;
        std::vector<std::string> headers = {"TS","ALT","TMP","HDG","AX","AY","AZ","GX","GY","GZ","MX","MY","MZ"};
        _sd.CreateCSV("flight.csv", headers);
        printf("--- SYSTEM READY ---\n\n");
        _buzz.PlayMario();
    } else {
        printf("--- SYSTEM DEGRADED ---\n\n");
    }
}

/**
 * \brief Periodic sensor read, packet build and transmit/log when healthy.
 */
void SensorManager::Update() {
    if(_b_ok) { _alt = _bmp.ReadAltitude(); _temp = _bmp.ReadTemperature(); }
    if(_m_ok) { 
        int16_t rx, ry, rz; _mag.ReadRaw(rx, ry, rz);
        _mx=(float)rx; _my=(float)ry; _mz=(float)rz; _hdg=_mag.GetHeading(); 
    }
    if(_imu_ok) {
        float acc[3], gyro[3], t; _mpu.ReadData(acc, gyro, &t);
        _ax=acc[0]; _ay=acc[1]; _az=acc[2]; _gx=gyro[0]; _gy=gyro[1]; _gz=gyro[2];
    }
    
    BuildPacket();

    if (_systemOk) {
        _nrf.Send((uint8_t*)_packet.c_str(), _packet.length());
        char logBuf[256];
        snprintf(logBuf, sizeof(logBuf), "%lu,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f\n", 
                 to_ms_since_boot(get_absolute_time()), _alt, _temp, _hdg, _ax, _ay, _az, _gx, _gy, _gz, _mx, _my, _mz);
        _sd.LogData("flight.csv", logBuf);
    }
}

/**
 * \brief Build a human-readable telemetry packet stored in `_packet`.
 */
void SensorManager::BuildPacket() {
    char buf[512];
    uint32_t ts = to_ms_since_boot(get_absolute_time());
    //snprintf(buf, sizeof(buf), 
    //         "T:%lu | B:%d M:%d I:%d S:%d | A:%.1f | H:%.1f | ACC:%.2f,%.2f,%.2f | GYR:%.1f,%.1f,%.1f", 
    //         ts, _b_ok, _m_ok, _imu_ok, _s_ok, _alt, _hdg, _ax, _ay, _az, _gx, _gy, _gz);

    
    snprintf(buf, sizeof(buf),
            "%lu,%d,%d,%d,%d,%.1f,%.1f,%.2f,%.2f,%.2f,%.1f,%.1f,%.1f",
            ts, _b_ok, _m_ok, _imu_ok, _s_ok, _alt, _hdg, _ax, _ay, _az, _gx, _gy, _gz);
    
    _packet = std::string(buf);
}