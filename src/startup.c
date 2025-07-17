#include <stdint.h>

extern uint32_t _etext, _sdata, _edata, _sbss, _ebss;
extern int main(void);

void Reset_Handler(void);
void Default_Handler(void);

#define RAM_START 0x20000000
#define RAM_SIZE  (96 * 1024)
#define RAM_END   (RAM_START + RAM_SIZE)

__attribute__ ((section(".isr_vector")))
void (* const vector_table[])(void) = {
    (void (*)(void))((uint32_t)RAM_END), // Initial stack pointer (top of RAM)
    Reset_Handler,
};

void Reset_Handler(void) {
    // Copy .data from flash to RAM
    uint32_t *src = &_etext;
    uint32_t *dst = &_sdata;
    while (dst < &_edata) {
        *dst++ = *src++;
    }

    // Zero .bss section
    dst = &_sbss;
    while (dst < &_ebss) {
        *dst++ = 0;
    }

    main();

    while (1);  // Loop forever if main returns
}

void Default_Handler(void) {
    while (1);
}
