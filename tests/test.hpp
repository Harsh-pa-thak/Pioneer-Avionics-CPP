#ifndef TEST_HPP
#define TEST_HPP

#include "pico/stdlib.h"
#include <cstdio>
#include "../ARK/system/timer.hpp"

inline void init_test_led() {
    const uint LED_PIN = 25;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
}

inline void blink_test() {
    static uint32_t last_blink = 0;
    static bool state = false;
    const uint LED_PIN = 25;

    if (millis() - last_blink >= 500) {
        last_blink = millis();
        state = !state;
        gpio_put(LED_PIN, state);
        
        if (state) {
            printf("[TEST] LED HIGH | Time: %lu ms\n", millis());
        } else {
            printf("[TEST] LED LOW  | Time: %lu ms\n", millis());
        }
    }
}

#endif