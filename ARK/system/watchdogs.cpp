#include "watchdogs.h"
#include "timer.hpp"

Watchdogs::Watchdogs() : last_kick_time(0), timeout_limit(0) {}

void Watchdogs::Init(uint32_t timeout_ms) {
    timeout_limit = timeout_ms;
    last_kick_time = millis();
}

void Watchdogs::Reset() {
    last_kick_time = millis();
}

bool Watchdogs::IsCheckFailed() {
    return (millis() - last_kick_time) > timeout_limit;
}