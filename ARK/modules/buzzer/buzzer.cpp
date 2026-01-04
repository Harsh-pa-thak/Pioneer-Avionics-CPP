/*
                                        ::                                                      
                                        ::                                                      
                                        ::                                                      
                                        ::                                                      
                                        ::                                                      
    ..    ..........    :.      ::      ::     .........  ..    ..........    ...      .        
    ::    ::            : .:.   ::      .::.       ::      ::    ::       :    :: :.    :        
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
* File:        buzzer.cpp
* Author:      Kunsh Jain
* Created On:  2025-12-22
* Brief:       Buzzer driver implementation.
* Description: Implements PWM initialization and tone/melody playback.
***************************************************************************************************
* HISTORY:
* +----- (NEW | MODify | ADD | DELete)
* |
* No#   |       when       who                  what
******+*********+**********+********************+**************************************************
* 000  NEW      2025-12-22   Kunsh Jain           Added header and Doxygen
* 001  MODify   2025-12-24   Kunsh Jain           Added Stop() and made PlayTone non-blocking
**************************************************************************************************/

#include "buzzer.h"

/** \brief Construct buzzer for given pin. */
Buzzer::Buzzer(uint pin) : _pin(pin) {}

/** \brief Initialize PWM hardware for buzzer output. */
void Buzzer::Init() {
    gpio_set_function(_pin, GPIO_FUNC_PWM);
    _slice = pwm_gpio_to_slice_num(_pin);
    pwm_set_enabled(_slice, true);
}

/** * \brief Play a single tone at `freq` Hz. 
 * \details This is now non-blocking. Call Stop() to silence.
 */
void Buzzer::PlayTone(uint freq, uint duration_ms) {
    if (freq == 0) {
        Stop();
    } else {
        uint32_t clock = 125000000;
        uint32_t divider = clock / (freq * 65536);
        if (divider < 1) divider = 1;
        pwm_set_clkdiv(_slice, (float)divider);
        pwm_set_wrap(_slice, 65535);
        pwm_set_chan_level(_slice, pwm_gpio_to_channel(_pin), 32768);
    }
}

/** \brief Stop the PWM output to silence the buzzer. */
void Buzzer::Stop() {
    pwm_set_chan_level(_slice, pwm_gpio_to_channel(_pin), 0);
}

/** \brief Play a short Mario melody by sequencing tones. */
void Buzzer::PlayMario() {
    uint16_t mel[11][2] = {
        {660, 150}, {660, 150}, {0, 150}, {660, 150}, {0, 150},
        {523, 150}, {660, 150}, {0, 150}, {784, 150}, {0, 150}, {392, 150}
    };
    for(int i=0; i<11; i++) {
        if (mel[i][0] == 0) {
            Stop();
        } else {
            PlayTone(mel[i][0], 0);
        }
        sleep_ms(mel[i][1]);
    }
    Stop();
}