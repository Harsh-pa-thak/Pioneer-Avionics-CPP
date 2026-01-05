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
* File:        buzzer.h
* Author:      Kunsh Jain
* Created On:  2025-12-22
* Brief:       Buzzer driver interface.
* Description: Simple PWM-based buzzer helper for tones and melodies.
***************************************************************************************************
* HISTORY:
* +----- (NEW | MODify | ADD | DELete)
* |
* No#   |       when       who                  what
******+*********+**********+********************+**************************************************
* 000  NEW      2025-12-22   Kunsh Jain           Added header and Doxygen
**************************************************************************************************/

#ifndef BUZZER_H
#define BUZZER_H

#include "pico/stdlib.h"
#include "hardware/pwm.h"

/** \brief Simple PWM buzzer helper class. */
class Buzzer {
public:
    /** \brief Create buzzer bound to `pin` (default 6). */
    Buzzer(uint pin = 6);
    /** \brief Initialize PWM hardware for buzzer. */
    void Init();
    /** \brief Play a tone at `freq` Hz for `duration_ms`. */
    void PlayTone(uint freq, uint duration_ms);
    /** \brief Play a short melody (Mario). */
    void PlayMario();
    void Stop();
private:
    uint _pin;
    uint _slice;
};

#endif