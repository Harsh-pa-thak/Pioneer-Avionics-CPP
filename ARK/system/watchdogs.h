#ifndef WATCHDOGS_H
#define WATCHDOGS_H

#include <stdint.h>

class Watchdogs {
public:
    Watchdogs();
    void Init(uint32_t timeout_ms);
    void Reset();
    bool IsCheckFailed();

private:
    uint32_t last_kick_time;
    uint32_t timeout_limit;
};

#endif