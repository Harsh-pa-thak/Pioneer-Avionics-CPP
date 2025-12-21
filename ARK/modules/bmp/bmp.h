#ifndef BMP_H
#define BMP_H

#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include <cmath>

class BMP280 {
public:
    struct CalibrationData {
        uint16_t dig_T1;
        int16_t  dig_T2, dig_T3;
        uint16_t dig_P1;
        int16_t  dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9;
    };

    BMP280(i2c_inst_t* i2c_instance, uint8_t addr = 0x76);
    
    bool Init(uint sda, uint scl, uint32_t baudrate = 400000);
    
    float ReadTemperature();
    float ReadPressure();
    float ReadAltitude(float seaLevelhPa = 1013.25f);
    
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