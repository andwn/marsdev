#include "joypad.hpp"
#include "string.hpp"
#include "text.hpp"
#include "vdp.hpp"

typedef void (*vfunc)();

extern void main();

[[gnu::section(".text.vectors"), gnu::unused]]
const vfunc M68K_VECTORS[] = {
        // Initial Stack Pointer Position
        (vfunc) ld_stack_end,
        // Program Entry Point
        []() __attribute__((__noreturn__)) {
            if(!(*joypad::reg_ctrl1 || *joypad::reg_ctrl2 || *joypad::reg_ctrl3)) {
                if (*md_reg_version & 0xF) *md_reg_tmss = 0x53454741;
            }
            for(;;) {
                memcpy((void*) ld_data_start, (void*) ld_text_size, (uint32) ld_data_size);
                vdp::init();
                joypad::init();
                main();
            }
        },
        // Bus Error
        nullptr,
        // Address Error
        []() __attribute__((interrupt)) {
            vdp::init();
            Text::puts("ADDRESS ERROR", 4, 1);
            for(;;);
        },
        // Illegal Instruction
        []() __attribute__((interrupt)) {
            vdp::init();
            Text::puts("ILLEGAL INSTRUCTION", 4, 1);
            for(;;);
        },
        // Divide by Zero
        []() __attribute__((interrupt)) {
            vdp::init();
            Text::puts("DIVIDE BY ZERO", 4, 1);
            for(;;);
        },
        // Chk, trap, etc
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        // Exceptions
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        // External Interrupt
        []() __attribute__((interrupt)) {},
        nullptr,
        // Horizontal Interrupt
        []() __attribute__((interrupt)) {},
        nullptr,
        // Vertical Interrupt
        []() __attribute__((interrupt)) {},
        nullptr,
        // Crap
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
};
