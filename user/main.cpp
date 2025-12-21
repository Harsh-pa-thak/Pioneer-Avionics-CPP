#include "../ARK/ark.h"
#include <cstdio>
#include "pico/stdlib.h"

int main() {
    stdio_init_all();

    const uint LED_PIN = 25;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    
    gpio_put(LED_PIN, 1);

    printf("\n--- PIONEER SYSTEM START ---\n");
    printf("Initializing Ark Kernel...\n");

    Ark ignition;
    ignition.Init();
    
    printf("Kernel Initialized. Handing over to Main Loop.\n");
    
    ignition.Start();
    
    return 0;
}