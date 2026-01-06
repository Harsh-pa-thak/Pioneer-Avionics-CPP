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
* File:        main.cpp
* Author:      Kunsh Jain
* Created On:  2025-12-22
* Brief:       Entry point for Pioneer firmware on Pico.
* Description: Initializes stdio and starts the `Ark` application which runs the main loop.
***************************************************************************************************
* HISTORY:
* +----- (NEW | MODify | ADD | DELete)
* |
* No#   |       when       who                  what
******+*********+**********+********************+**************************************************
* 000  NEW      2025-12-22   Kunsh Jain           Added header and Doxygen
**************************************************************************************************/

// NOTE: Only file header and Doxygen comments were added; main logic is unchanged.

#include "../ARK/ark.h"
#include <cstdio>
#include "pico/stdlib.h"

/**
 * \brief Application entry point.
 * \details Initializes standard IO, blinks the LED, initializes the Ark kernel
 *          and hands control to the main loop.
 */
int main() {

    sleep_ms(1000); // Wait for power to stabilize
    stdio_init_all();
    
    const uint LED_PIN = 25;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    
    gpio_put(LED_PIN, 1);
    
    sleep_ms(5000); // Wait for power to stabilize
  
    gpio_put(LED_PIN, 0);

    printf("\n--- PIONEER SYSTEM START ---\n");
    printf("Initializing Ark Kernel...\n");
  
    gpio_put(LED_PIN, 1);
    
    sleep_ms(100); // Wait for power to stabilize
  
    gpio_put(LED_PIN, 0);

    Ark ignition;
    ignition.Init();
    


    printf("Kernel Initialized. Handing over to Main Loop.\n");
    
    ignition.Start();
    
    printf("Loop Started.-->However this message wont be seen\n");
  
    return 0;
}
