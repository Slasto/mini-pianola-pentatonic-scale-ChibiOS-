#include "ch.h"
#include "hal.h"
#include "lib/buzzer.h"
#include "lib/music.h"
#include "lib/visual.h"

//NOTE
#define BTN_NOTE1 PAL_LINE( GPIOC, 0U )
#define BTN_NOTE2 PAL_LINE( GPIOC, 1U )
#define BTN_NOTE3 PAL_LINE( GPIOC, 2U )
#define BTN_NOTE4 PAL_LINE( GPIOC, 3U )
#define BTN_NOTE5 PAL_LINE( GPIOB, 0U )
//#define BTN_SONG PAL_LINE(GPIOA, 15U)
//BUZZ D12
//DISPLAY SCL to D15 || SDA to D14

/*Application entry point.*/
int main(void) {
  halInit();
  chSysInit();
  buzzer_init();
  init_display();
  clear_display();

  //SET PIN MODE
  palSetPadMode(GPIOB, 10U, PAL_MODE_ALTERNATE(2));
  chThdSleepMilliseconds(5);
  while (TRUE) {
    if (palReadLine(BTN_NOTE1) == PAL_HIGH) {
      print_string_centered("#C6", 40, &ssd1306_font_11x18);
      while (palReadLine(BTN_NOTE1) == PAL_HIGH) {
        tone(NOTE_C6, SOUND_VOLUME);
      }
      clear_display();
      print_string_centered("Nota", 0, &ssd1306_font_11x18);

    }
    else if (palReadLine(BTN_NOTE2) == PAL_HIGH) {
      print_string_centered("#D6", 40, &ssd1306_font_11x18);
      while (palReadLine(BTN_NOTE2) == PAL_HIGH) {
        tone(NOTE_D6, SOUND_VOLUME);
      }
      clear_display();
      print_string_centered("Nota", 0, &ssd1306_font_11x18);
    }
    else if (palReadLine(BTN_NOTE3) == PAL_HIGH) {
      print_string_centered("#E6", 40, &ssd1306_font_11x18);
      while (palReadLine(BTN_NOTE3) == PAL_HIGH) {
        tone(NOTE_E6, SOUND_VOLUME);
      }
      clear_display();
      print_string_centered("Nota", 0, &ssd1306_font_11x18);
    }
    else if (palReadLine(BTN_NOTE4) == PAL_HIGH) {
      print_string_centered("#A6", 40, &ssd1306_font_11x18);
      while (palReadLine(BTN_NOTE4) == PAL_HIGH) {
        tone(NOTE_A6, SOUND_VOLUME);
      }
      clear_display();
      print_string_centered("Nota", 0, &ssd1306_font_11x18);
    }
    else if (palReadLine(BTN_NOTE5) == PAL_HIGH) {
      print_string_centered("#G6", 40, &ssd1306_font_11x18);
      while (palReadLine(BTN_NOTE5) == PAL_HIGH) {
        tone(NOTE_G6, SOUND_VOLUME);
      }
      clear_display();
      print_string_centered("Nota", 0, &ssd1306_font_11x18);
    }
    else if (palReadLine(BTN_SONG) == PAL_HIGH) {
      print_string_centered("TETRIS", 40, &ssd1306_font_11x18);
      play_music(144);
      clear_display();
      print_string_centered("Nota", 0, &ssd1306_font_11x18);
    }
    else
      noTone();
    chThdSleepMilliseconds(20);
  }
}
