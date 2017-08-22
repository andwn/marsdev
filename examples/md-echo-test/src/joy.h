// Based on SGDK joy module

#define JOY_1           0x0000
#define JOY_2           0x0001

#define BUTTON_UP       0x0001
#define BUTTON_DOWN     0x0002
#define BUTTON_LEFT     0x0004
#define BUTTON_RIGHT    0x0008
#define BUTTON_A        0x0040
#define BUTTON_B        0x0010
#define BUTTON_C        0x0020
#define BUTTON_START    0x0080
#define BUTTON_X        0x0400
#define BUTTON_Y        0x0200
#define BUTTON_Z        0x0100
#define BUTTON_MODE     0x0800

#define BUTTON_DIR      0x000F
#define BUTTON_BTN      0x0FF0

#define JOY_TYPE_PAD3           0x00
#define JOY_TYPE_PAD6           0x01

void joy_init();
uint8_t joy_get_type(uint16_t joy);
uint16_t joy_get_state(uint16_t joy);
void joy_update();
