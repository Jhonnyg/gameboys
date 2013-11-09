#ifndef __SOUND_H__
#define __SOUND_H__

#define SOUND_ON sound_on();

enum fx_tbl {
	SOUND_FX_TEST
};

void sound_on();
void sound_off();
void play_effect(unsigned int effect);

#endif 
