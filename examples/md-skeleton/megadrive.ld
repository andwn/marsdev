OUTPUT_ARCH(m68k)

MEMORY
{
  rom (rx) : ORIGIN = 0, LENGTH = 4M
  ram (wx) : ORIGIN = 0xFFFF0000, LENGTH = 64K
}

SECTIONS
{
  .text 0x00000000 :
  {
    KEEP(*(.text.keepboot))
    *(.text.*) *(.text)
    . = ALIGN(2);
    *(.rodata .rodata.*)
	. = ALIGN(2);
  } > rom
  _stext = SIZEOF (.text);

  .data 0xFFFF0000 :
  AT ( LOADADDR (.text) + SIZEOF (.text) )
  {
    *(.data .data.*)
    _edata = .;
    . = ALIGN(2);
  } > ram
  _sdata = SIZEOF (.data);

  .bss 0xFFFF0000 + SIZEOF (.data) :
  {
    __bss_start = . ;
    *(.bss .bss.*)
    *(COMMON)
    _end =  ALIGN (2);
    __end = _end;
    end = _end;
  } > ram
}
