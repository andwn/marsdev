#ifndef MEGADRIVE_HPP
#define MEGADRIVE_HPP

// -------------------------------------------------------------------------------------------------
// Types
// -------------------------------------------------------------------------------------------------
typedef signed char  int8;
typedef signed short int16;
typedef signed long  int32;
typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef unsigned long  uint32;

// -------------------------------------------------------------------------------------------------
// Hardware Registers
// -------------------------------------------------------------------------------------------------
static volatile uint8 * const md_reg_version = (uint8*) 0xA10001;
static volatile uint32 * const md_reg_tmss = (uint32*) 0xA40000;

// Variables from linker script containing the locations and size of sections
// For some reason, they have to be defined as arrays, or the values will be wrong
extern const uint32 ld_text_start[];
extern const uint32 ld_text_end[];
extern const uint32 ld_text_size[];
extern const uint32 ld_bss_start[];
extern const uint32 ld_bss_end[];
extern const uint32 ld_bss_size[];
extern const uint32 ld_data_start[];
extern const uint32 ld_data_end[];
extern const uint32 ld_data_size[];
extern const uint32 ld_stack_start[];
extern const uint32 ld_stack_end[];
extern const uint32 ld_stack_size[];


extern const uint16 blank_data[0x80];

#endif //MEGADRIVE_HPP
