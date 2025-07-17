#include "ili9341.h"
#include <stdint.h>
#include "font5x7.h"

// These are GPIO pin stubs — replace with your real GPIO and SPI code
#define LCD_CS_HIGH()   // Set CS pin HIGH here
#define LCD_CS_LOW()    // Set CS pin LOW here
#define LCD_DC_HIGH()   // Set DC pin HIGH here
#define LCD_DC_LOW()    // Set DC pin LOW here
#define LCD_RST_HIGH()  // Set RESET pin HIGH here
#define LCD_RST_LOW()   // Set RESET pin LOW here

// Stub SPI write function — replace with your SPI send code
void spi_write(uint8_t data) {
    // Send data over SPI
}

// Send command byte to LCD
static void lcd_write_command(uint8_t cmd) {
    LCD_DC_LOW();
    LCD_CS_LOW();
    spi_write(cmd);
    LCD_CS_HIGH();
}

// Send data bytes to LCD
static void lcd_write_data(const uint8_t* buff, int buff_size) {
    LCD_DC_HIGH();
    LCD_CS_LOW();
    for (int i=0; i < buff_size; i++) {
        spi_write(buff[i]);
    }
    LCD_CS_HIGH();
}

void ili9341_init(void) {
    // Reset sequence
    LCD_RST_LOW();
    // Delay 10ms
    LCD_RST_HIGH();
    // Delay 10ms

    lcd_write_command(0x01); // Software reset
    // Delay 150ms

    lcd_write_command(0x28); // Display OFF
    // More initialization commands here ...

    lcd_write_command(0x29); // Display ON
}

void ili9341_fill_screen(uint16_t color) {
    // Fill screen with color (convert 16-bit color to bytes, send)
}

void ili9341_draw_text(int x, int y, const char* text, uint16_t color) {
    // Draw each character using font5x7 at x,y
}
