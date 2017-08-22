#include "stdint.h"
#include "echo.h"
#include "joy.h"
#include "vdp.h"
#include "res_audio.h"

#define SONG_COUNT 12

const void *const echo_list[] = {
	res_psg_flat,
	res_fm_dguitar,
	res_pcm_snare,
	res_pcm_kick,
	res_fm_string,
	res_fm_bass,
	res_psg_soft,
	res_psg_piano,
	res_psg_square,
	res_fm_piano,
	res_fm_square,
	res_fm_saw,
	res_fm_flute,
	res_psg_nepel,
	res_fm_ebass,
	res_fm_squaref,
	res_fm_sawf,
	res_psg_seahorse,
	res_psg_hithat,
	res_psg_string,
	res_fm_eguitar,
	NULL
};

const void *const songs[SONG_COUNT] = {
	res_bgm_doomsday,
	res_bgm_hol,
	res_bgm_megajysays,
	res_bgm_midnas,
	res_bgm_minion,
	res_bgm_nelpel,
	res_bgm_test_drums,
	res_bgm_test_flute,
	res_bgm_test_piano,
	res_bgm_test_psg,
	res_bgm_test_squsaw_1ch,
	res_bgm_test_squsaw_2ch,
};

const uint16_t pal[16] = { 
	0xC00,0x000,0x404,0x606,0x808,0xA0A,0xC0C,0xE0E,
	0xE2E,0xE4E,0xE6E,0xE8E,0xEAE,0xECE,0xE00,0xEEE 
};

// Underscore because GCC complains if main's return type isn't int
void _main() {
    __asm__("move #0x2500,%sr"); // Enable vertical int
    vdp_init();
    joy_init();
    echo_init(echo_list);
    
	vdp_set_colors(0, pal, 16);
	
	uint8_t songindex = 0;
	uint8_t volume = 255;
	echo_play_bgm(songs[songindex]);
	
	vdp_puts(VDP_PLAN_A, "left / right - change track", 4, 8);
	vdp_puts(VDP_PLAN_A, "up / down (hold) - volume", 4, 10);
	//vdp_puts(VDP_PLAN_A, "C - Sound effect", 4, 12);
	vdp_puts(VDP_PLAN_A, "B - pause", 4, 14);
	vdp_puts(VDP_PLAN_A, "A - resume", 4, 16);
	
	uint16_t joystate = ~0, oldstate;
	while(TRUE) {
		joy_update();
		oldstate = joystate;
		joystate = joy_get_state(JOY_1);
		
		if((joystate & BUTTON_LEFT) && !(oldstate & BUTTON_LEFT)) {
			if(--songindex >= SONG_COUNT) songindex = SONG_COUNT - 1;
			echo_play_bgm(songs[songindex]);
		}
		if((joystate & BUTTON_RIGHT) && !(oldstate & BUTTON_RIGHT)) {
			if(++songindex >= SONG_COUNT) songindex = 0;
			echo_play_bgm(songs[songindex]);
		}
		if(joystate & BUTTON_UP) {
			if(volume < 255) {
				volume++;
				if((volume & 3) == 0) echo_set_volume(volume);
			}
		}
		if(joystate & BUTTON_DOWN) {
			if(volume > 0) {
				volume--;
				if((volume & 3) == 0) echo_set_volume(volume);
			}
		}
		//if((joystate & BUTTON_C) && !(oldstate & BUTTON_C)) {
		//	echo_play_sfx(???);
		//}
		if((joystate & BUTTON_B) && !(oldstate & BUTTON_B)) {
			echo_pause_bgm();
		}
		if((joystate & BUTTON_A) && !(oldstate & BUTTON_A)) {
			echo_resume_bgm();
		}
		
		vdp_vsync();
	}
}
