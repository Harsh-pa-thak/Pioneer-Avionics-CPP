#ifndef TIMER_HPP
#define TIMER_HPP

#include "pico/stdlib.h"

inline uint32_t millis() {
    return to_ms_since_boot(get_absolute_time());
}

#endif
