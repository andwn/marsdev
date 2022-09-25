#include <stddef.h>
#include <stdint.h>

#include "error.h"
#include "string.h"
#include "vdp.h"

#define hard_reset() __asm__("move   #0x2700,%sr\n\t" \
                             "move.l (0),%a7\n\t"     \
                             "jmp    _hard_reset")

#define enable_ints __asm__("move #0x2500,%sr")
#define disable_ints __asm__("move #0x2700,%sr")
