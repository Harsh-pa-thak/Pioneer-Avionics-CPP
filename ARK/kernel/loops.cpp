#include "loops.h"

#include "../../tests/test.hpp"

Loops::Loops() : bmp(i2c0) { 
    wdt.Init(5000);
    
    if (!bmp.Init(4, 5)) {
        while(1){
            printf("[ERROR] BMP280 initialization failed!\n");
        }
    } else {
        bmp.CalibrateSeaLevel(0.0f);
    }
}

void Loops::StreamTelemetry() {
    // Continuously throw values and add the requested delay
    printf("ALT: %.2f | TEMP: %.2f\n", bmp.ReadAltitude(), bmp.ReadTemperature());
    sleep_ms(10); 
}

void Loops::Run() {
    while (true) {
        
        blink_test();
        StreamTelemetry();

        if (wdt.IsCheckFailed()) {
            manager.SetState(FlightState::FAILSAFE);
        }

        if (manager.GetState() != FlightState::FAILSAFE) {
            wdt.Reset();
        }

        switch (manager.GetState()) {
            case FlightState::BOOT:
                manager.HandleBoot();
                break;
            case FlightState::IDLE:
                manager.HandleIdle();
                break;
            case FlightState::ARMED:
                manager.HandleArmed();
                break;
            case FlightState::LAUNCH:
                manager.HandleLaunch();
                break;
            case FlightState::ASCENT:
                manager.HandleAscent();
                break;
            case FlightState::CRUISING:
                manager.HandleCruising();
                break;
            case FlightState::APOGEE:
                manager.HandleApogee();
                break;
            case FlightState::DEPLOYMENT:
                manager.HandleDeployment();
                break;
            case FlightState::DESCENT:
                manager.HandleDescent();
                break;
            case FlightState::LANDED:
                manager.HandleLanded();
                break;
            case FlightState::FAILSAFE:
                manager.HandleFailsafe();
                break;
        }
    }
}