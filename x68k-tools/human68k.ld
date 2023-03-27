/* Default linker script, for normal executables */
OUTPUT_FORMAT("elf32-m68k")
ENTRY (_start)

SECTIONS
{
  .text 0x000000 : {
    *(.header)
    . = ALIGN(2);
    *(.init)
    *(.text)
    *(.text.*)
    *(.fini)
    . = ALIGN(2);
    __text_end = .;
  }

  .data SIZEOF(.text) + ADDR(.text) :
  {
    __ctor_list = .; *(.ctors) LONG (0);
    __dtor_list = .; *(.dtors) LONG (0);

    *(.data) *(.data*)
    *(.rodata) *(.rodata*)

    *(.gcc_exc*)
    ___EH_FRAME_BEGIN__ = .;
    *(.eh_fram*)
    ___EH_FRAME_END__ = .;
    . = ALIGN (2);
    __data_end = .;
  }

  .bss SIZEOF(.data) + ADDR(.data) :
  {
    *(.bss)
    *(COMMON)
    . = ALIGN(2);
    end = .;
    _end = .;
    __bss_end = .;
  }

  __stack_size = 0x8000;
  __heap_size = 0x10000;
}
