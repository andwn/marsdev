#include "string.hpp"
#include "text.hpp"
#include "vdp.hpp"

void main() {
    char str[10];
    uint16 y = 1;
    Text::puts("SECTION  START    END      SIZE", 2, y); y += 2;
    Text::puts("TEXT", 2, y);
    intToHex((uint32)ld_text_start, str, 6); Text::puts(str, 11, y);
    intToHex((uint32)ld_text_end,   str, 6); Text::puts(str, 20, y);
    intToHex((uint32)ld_text_size,  str, 6); Text::puts(str, 29, y); y++;
    Text::puts("BSS", 2, y);
    intToHex((uint32)ld_bss_start, str, 6); Text::puts(str, 11, y);
    intToHex((uint32)ld_bss_end,   str, 6); Text::puts(str, 20, y);
    intToHex((uint32)ld_bss_size,  str, 6); Text::puts(str, 29, y); y++;
    Text::puts("DATA", 2, y);
    intToHex((uint32)ld_data_start, str, 6); Text::puts(str, 11, y);
    intToHex((uint32)ld_data_end,   str, 6); Text::puts(str, 20, y);
    intToHex((uint32)ld_data_size,  str, 6); Text::puts(str, 29, y); y++;
    Text::puts("STACK", 2, y);
    intToHex((uint32)ld_stack_start, str, 6); Text::puts(str, 11, y);
    intToHex((uint32)ld_stack_end,   str, 6); Text::puts(str, 20, y);
    intToHex((uint32)ld_stack_size,  str, 6); Text::puts(str, 29, y);
	
	while(1) {
		vdp::vsync();
	}
}
