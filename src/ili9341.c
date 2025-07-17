#include "ili9341.h"
#include <stdint.h>
#include "font5x7.h"
#include "stm32f4xx.h"  // This is the STM32 HAL header for Meowbit v1.6

// Meowbit SPI1 pins and control pins (GPIOB and GPIOC)
#define LCD_CS_PORT GPIOB
#define LCD_CS_PIN  GPIO_PIN_0

#define LCD_DC_PORT GPIOB
#define LCD_DC_PIN  GPIO_PIN_1

#define LCD_RST_PORT GPIOB
#define LCD_RST_PIN  GPIO_PIN_2

// Helper macros for pin control
#define CS_HIGH() HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET)
#define CS_LOW()  HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET)

#define DC_HIGH() HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET)
#define DC_LOW()  HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_RESET)

#define RST_HIGH() HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, GPIO_PIN_SET)
#define RST_LOW()  HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, GPIO_PIN_RESET)

// SPI write using SPI1 peripheral
static void spi_write(uint8_t data) {
    while(!(SPI1->SR & SPI_SR_TXE));  // Wait for TX buffer empty
    *((__IO uint8_t*)&SPI1->DR) = data;  // Write data
    while(!(SPI1->SR & SPI_SR_RXNE));  // Wait for RX buffer not empty (receive complete)
    (void)SPI1->DR;  // Read to clear RXNE flag
}

static void lcd_write_command(uint8_t cmd) {
    DC_LOW();
    CS_LOW();
    spi_write(cmd);
    CS_HIGH();
}

static void lcd_write_data(uint8_t* buff, int len) {
    DC_HIGH();
    CS_LOW();
    for(int i=0; i < len; i++) {
        spi_write(buff[i]);
    }
    CS_HIGH();
}

static void delay_ms(int ms) {
    // Simple software delay, tune if needed
    for(int i = 0; i < ms * 4000; i++) {
        __asm__("nop");
    }
}

void ili9341_init(void) {
    // Initialize GPIO pins for CS, DC, RST as output and SPI1 peripheral
    // This must be called once at start.

    // Reset LCD
    RST_LOW();
    delay_ms(10);
    RST_HIGH();
    delay_ms(10);

    lcd_write_command(0x01);  // Software reset
    delay_ms(150);

    // Exit sleep
    lcd_write_command(0x11);
    delay_ms(150);

    // Pixel format 16 bits
    lcd_write_command(0x3A);
    uint8_t pixel_format = 0x55;
    lcd_write_data(&pixel_format, 1);

    // Display ON
    lcd_write_command(0x29);
    delay_ms(150);
}

void ili9341_fill_screen(uint16_t color) {
    // Fill screen with color (16-bit)
    // This is a simplified example; real code sets window and sends data

    // You would set the window (column/page address) and send color repeated for all pixels here.
}

void ili9341_draw_text(int x, int y, const char* text, uint16_t color) {
    // Draw text using font5x7 at x,y with color
    // This requires a real drawing function; for now, stub
}
