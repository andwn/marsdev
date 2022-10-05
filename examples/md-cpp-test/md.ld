OUTPUT_ARCH(m68k)
__DYNAMIC  =  0;

MEMORY
{
    rom (rx) : ORIGIN = 0x00000000, LENGTH = 0x00400000
    ram (wx) : ORIGIN = 0x00FF0000, LENGTH = 0x00010000
}

SECTIONS
{
  .text :
  {
    ld_text_start = .;
    KEEP(*(.text.vectors))
	KEEP(*(.text.header))
	*(.text .text.*)
    . = ALIGN (0x4);
    __CTOR_LIST__ = .;
	LONG((__CTOR_END__ - __CTOR_LIST__) / 4 - 2)
	*(.ctors)
	LONG(0)
	__CTOR_END__ = .;
	__DTOR_LIST__ = .;
	LONG((__DTOR_END__ - __DTOR_LIST__) / 4 - 2)
	*(.dtors)
	LONG(0)
	__DTOR_END__ = .;
    *(.rodata .rodata.*)
    . = ALIGN (0x2);
    ld_text_end = .;
  } > rom
  ld_text_size = SIZEOF(.text);

  .bss (NOLOAD) :
  {
    ld_bss_start = .;
    *(.bss .bss.*)
    . = ALIGN (0x2);
    ld_bss_end = .;
  } > ram
  ld_bss_size = SIZEOF(.bss);

  .data :
  {
    ld_data_start = .;
    *(.data .data.*)
    . = ALIGN (0x2);
    ld_data_end = .;
  } > ram AT > rom
  ld_data_size = SIZEOF(.data);

  .stack (NOLOAD) :
  {
    ld_stack_start = .;
    . = 0x400;
    ld_stack_end = .;
  } > ram
  ld_stack_size = SIZEOF(.stack);
}
