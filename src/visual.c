#include "../lib/visual.h"

static SSD1306Driver SSD1306D1;

/*
 * Initializes the game display.
 */
void init_display(void) {

  palSetLineMode(
      LINE_ARD_D15,
      PAL_MODE_ALTERNATE(4) | PAL_STM32_OTYPE_OPENDRAIN | PAL_STM32_OSPEED_HIGHEST | PAL_STM32_PUPDR_PULLUP);
  palSetLineMode(
      LINE_ARD_D14,
      PAL_MODE_ALTERNATE(4) | PAL_STM32_OTYPE_OPENDRAIN | PAL_STM32_OSPEED_HIGHEST | PAL_STM32_PUPDR_PULLUP);
  ssd1306ObjectInit(&SSD1306D1);

  /*
   * Start the SSD1306 Display Driver Object with
   * configuration.
   */
  ssd1306Start(&SSD1306D1, &ssd1306cfg_visual);
  ssd1306FillScreen(&SSD1306D1, 0x00);
}

/*prints a string to a specified y-coordinate and centered*/
void print_string_centered(char *s, int heigth, const ssd1306_font_t *font) {
  int s_length = (font->fw) * strlength(s);
  int x_string = DISPLAY_WIDTH / 2 - s_length / 2;
  print_string(s, x_string, heigth, font);
}

/*prints a string to a specified x and y coordinates*/
void print_string(char *s, int x, int y, const ssd1306_font_t *font) {
  ssd1306GotoXy(&SSD1306D1, x, y);
  ssd1306Puts(&SSD1306D1, s, font, SSD1306_COLOR_WHITE);
  ssd1306UpdateScreen(&SSD1306D1);
}

/* sets all the pixels of the
 * game display to black */

void clear_display(void) {
  ssd1306FillScreen(&SSD1306D1, 0x00);
  ssd1306UpdateScreen(&SSD1306D1);
}

/*returns the length of the string*/
int strlength(char *s) {
  int length = 0;
  while (s[length] != '\0')
    length++;
  return length;
}
