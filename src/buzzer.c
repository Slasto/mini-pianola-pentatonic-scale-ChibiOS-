#include "../lib/buzzer.h"

const int melody[] = {
//Based on the arrangement at https://www.flutetunes.com/tunes.php?id=192

    NOTE_E5,
    4, NOTE_B4, 8, NOTE_C5, 8, NOTE_D5, 4, NOTE_C5, 8, NOTE_B4, 8,
    NOTE_A4,
    4, NOTE_A4, 8, NOTE_C5, 8, NOTE_E5, 4, NOTE_D5, 8, NOTE_C5, 8,
    NOTE_B4,
    -4, NOTE_C5, 8, NOTE_D5, 4, NOTE_E5, 4,
    NOTE_C5,
    4, NOTE_A4, 4, NOTE_A4, 8, NOTE_A4, 4, NOTE_B4, 8, NOTE_C5, 8,

    NOTE_D5,
    -4, NOTE_F5, 8, NOTE_A5, 4, NOTE_G5, 8, NOTE_F5, 8,
    NOTE_E5,
    -4, NOTE_C5, 8, NOTE_E5, 4, NOTE_D5, 8, NOTE_C5, 8,
    NOTE_B4,
    4, NOTE_B4, 8, NOTE_C5, 8, NOTE_D5, 4, NOTE_E5, 4,
    NOTE_C5,
    4, NOTE_A4, 4, NOTE_A4, 4, REST, 4,

    NOTE_E5,
    4, NOTE_B4, 8, NOTE_C5, 8, NOTE_D5, 4, NOTE_C5, 8, NOTE_B4, 8,
    NOTE_A4,
    4, NOTE_A4, 8, NOTE_C5, 8, NOTE_E5, 4, NOTE_D5, 8, NOTE_C5, 8,
    NOTE_B4,
    -4, NOTE_C5, 8, NOTE_D5, 4, NOTE_E5, 4,
    NOTE_C5,
    4, NOTE_A4, 4, NOTE_A4, 8, NOTE_A4, 4, NOTE_B4, 8, NOTE_C5, 8,

    NOTE_D5,
    -4, NOTE_F5, 8, NOTE_A5, 4, NOTE_G5, 8, NOTE_F5, 8,
    NOTE_E5,
    -4, NOTE_C5, 8, NOTE_E5, 4, NOTE_D5, 8, NOTE_C5, 8,
    NOTE_B4,
    4, NOTE_B4, 8, NOTE_C5, 8, NOTE_D5, 4, NOTE_E5, 4,
    NOTE_C5,
    4, NOTE_A4, 4, NOTE_A4, 4, REST, 4,

    NOTE_E5,
    2, NOTE_C5, 2,
    NOTE_D5,
    2, NOTE_B4, 2,
    NOTE_C5,
    2, NOTE_A4, 2,
    NOTE_GS4,
    2, NOTE_B4, 4, REST, 8,
    NOTE_E5,
    2, NOTE_C5, 2,
    NOTE_D5,
    2, NOTE_B4, 2,
    NOTE_C5,
    4, NOTE_E5, 4, NOTE_A5, 2,
    NOTE_GS5,
    2,

};

const int notes_number = sizeof(melody) / sizeof(melody[0]) / 2;

static PWMConfig pwmcfg = {
PWM_FREQ,
                           PWM_PERIOD, NULL, { {PWM_OUTPUT_ACTIVE_LOW, NULL}, {
                               PWM_OUTPUT_DISABLED, NULL},
                                              {PWM_OUTPUT_DISABLED, NULL},
                                              {
                                              PWM_OUTPUT_DISABLED,
                                               NULL}},
                           0, 0, 1};

void buzzer_init(void) {
  palSetPadMode(GPIOA, 6, PAL_MODE_ALTERNATE(2)); // TIM3_CH1

  // Start PWM Driver on Timer 3
  pwmStart(&PWMD3, &pwmcfg);
}

void tone(int freq, int vol) {
  if (freq == 0) {
    noTone();
  }
  else {
    pwmChangePeriod(&PWMD3, 1000000 / freq);
                            //
    pwmEnableChannel(&PWMD3, 0, PWM_PERCENTAGE_TO_WIDTH(&PWMD3, vol));
  }
}

void noTone(void) {
  pwmDisableChannel(&PWMD3, 0);
}

void play_music(int tempo) {
  int wholenote = (60000 * 4) / tempo;

  int divider = 0, noteDuration = 0;
  for (int i = 0; i < notes_number&&palReadLine(BTN_SONG)==PAL_HIGH; i += 2) {

    divider = melody[i + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    }
    else if (divider < 0) {
      noteDuration = (wholenote) / (divider);
      noteDuration *= -1.5;
    }

    tone(melody[i], SOUND_VOLUME);
    chThdSleepMilliseconds(9 * noteDuration / 10);

    noTone();
    chThdSleepMilliseconds(noteDuration / 10);

  }
}
