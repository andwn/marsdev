#include "megadrive.hpp"

typedef struct {
    char console[16];               /* Console Name (16) */
    char copyright[16];             /* Copyright Information (16) */
    char title_local[48];           /* Domestic Name (48) */
    char title_int[48];             /* Overseas Name (48) */
    char serial[14];                /* Serial Number (2, 12) */
    uint16 checksum;                /* Checksum (2) */
    char IOSupport[16];             /* I/O Support (16) */
    uint32 rom_start;               /* ROM Start Address (4) */
    uint32 rom_end;                 /* ROM End Address (4) */
    uint32 ram_start;               /* Start of Backup RAM (4) */
    uint32 ram_end;                 /* End of Backup RAM (4) */
    char sram_sig[2];               /* "RA" for save ram (2) */
    uint16 sram_type;               /* 0xF820 for save ram on odd bytes (2) */
    uint32 sram_start;              /* SRAM start address - normally 0x200001 (4) */
    uint32 sram_end;                /* SRAM end address - start + 2*sram_size (4) */
    char modem_support[12];         /* Modem Support (24) */
    char notes[40];                 /* Memo (40) */
    char region[16];                /* Country Support (16) */
} ROMHeader;

// Oh, you wanted to use strings without a null terminator? Sorry that's not valid C++
[[maybe_unused]] const ROMHeader rom_header __attribute((section(".text.header"))) = {
        "SEGA MEGA DRIVE",
        "ANDWN 2022.OCT",
        "C++ Test",
        "C++ Test",
        {'G','M',' ','C','H','A','N','G','E','M','E','-','X','X'},
        0x000,
        "JD",
        0x00000000,
        0x003FFFFF,
        0xE0FF0000,
        0xE0FFFFFF,
        {' ',' '},
        0xF820,
        0x00200000,
        0x0020FFFF,
        "",
        "",
        "JUE"
};
