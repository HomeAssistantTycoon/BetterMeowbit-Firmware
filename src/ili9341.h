#ifndef ILI9341_H
#define ILI9341_H

#include <stdint.h>

void ili9341_init(void);
void ili9341_fill_screen(uint16_t color);
void ili9341_draw_text(int x, int y, const char* text, uint16_t color);

#endif
