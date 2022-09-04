#ifndef BUZZER_H
#define BUZZER_H

#include "ch.h"
#include "hal.h"
#include "music.h"

#define PWM_FREQ    1000000    // PWM Timer Frequency  1MHz
#define PWM_PERIOD  100     // PWM Period           1ms
#define SOUND_VOLUME 1000

#define BTN_SONG PAL_LINE( GPIOA, 15U )

//#define START_POWER_PERCENTAGE  0
//#define MAX_POWER_PERCENTAGE    1000
//#define PERCENTAGE_STEP         1

#define BUZ_LINE PAL_LINE(GPIOA, 6)

/*
 * PWM Driver Configuration.
 */

void buzzer_init(void);
void tone(int freq, int vol);
void noTone(void);
void play_music(int);
#endif
