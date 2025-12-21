#ifndef LOOPS_H
#define LOOPS_H

#include "statesmanager.h"
#include "../system/watchdogs.h"
#include "../system/timer.hpp"
#include "../modules/bmp/bmp.h"

class Loops {
public:
    Loops();
    void Run();

private:
    void StreamTelemetry();
    StatesManager manager;
    Watchdogs wdt; 
    BMP280 bmp;
};

#endif