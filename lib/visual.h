#ifndef VISUAL_H
#define VISUAL_H

#include "ch.h"
#include "hal.h"
#include "ssd1306.h"

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGTH 64

/*
 * I2C1 configuration
 */
static const I2CConfig i2ccfg_visual = {OPMODE_I2C, 400000, FAST_DUTY_CYCLE_2, };

/*
 * game SSD1306 configuration
 */
static const SSD1306Config ssd1306cfg_visual = {&I2CD1, &i2ccfg_visual,
                                                SSD1306_SAD_0X78, };

/*
 * enum used to differentiate between
 * left and right half of the screen
 */
typedef enum {
  LEFT_SIDE,
  RIGHT_SIDE,
} side_t;

/*
 * enum used to specify black
 * or white color for text
 */
typedef enum {
  BLACK,
  WHITE,
} color_t;

/*
 * Functions declarations
 */
void init_display(void);
void print_string_centered(char*, int, const ssd1306_font_t*);
void print_string_centered_side(char*, int, const ssd1306_font_t*, side_t,
                                color_t);
void print_string(char*, int, int, const ssd1306_font_t*);
void clear_display(void);
int strlength(char*);

#endif
