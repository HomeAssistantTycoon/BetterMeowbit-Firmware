MEMORY
{
  FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 512K
  RAM (rwx)  : ORIGIN = 0x20000000, LENGTH = 96K
}

SECTIONS
{
  .isr_vector : {
    KEEP(*(.isr_vector))
  } > FLASH

  .text : {
    *(.text*)
    *(.rodata*)
  } > FLASH

  .data : AT (ADDR(.text) + SIZEOF(.text)) {
    _sdata = .;
    *(.data*)
    _edata = .;
  } > RAM

  _etext = LOADADDR(.data);

  .bss : {
    _sbss = .;
    *(.bss*)
    *(COMMON)
    _ebss = .;
  } > RAM
}
