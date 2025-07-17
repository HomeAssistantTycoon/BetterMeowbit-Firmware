#include <stdint.h>
#include "ili9341.h"
#include "font5x7.h"

int main(void) {
    ili9341_init();
    ili9341_fill_screen(0x0000); // Black
    ili9341_draw_text(10, 10, "BetterMeowbit v0.1", 0xFFFF); // White

    while (1) {
        // Loop forever
    }
    return 0;
}
