#include <stdint.h>

extern uint32_t _etext, _sdata, _edata, _sbss, _ebss;
extern int main(void);

void Reset_Handler(void);
void Default_Handler(void);

__attribute__ ((section(".isr_vector")))
void (* const vector_table[])(void) = {
    (void (*)(void))(&_ebss), // Initial stack pointer (placeholder)
    Reset_Handler,            // Reset handler
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
