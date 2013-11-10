#include <gb/gb.h>
#include "sound.h"
#include "sound_data.h"

int snd_init = 0;

struct sound_container {
	char* name;
	UBYTE volume;
	UBYTE length;
	UBYTE note;
};

const struct sound_container sound_effects[] = {
	{"SOUND_FX_TEST1",0xF3,0x01,F2},
	{"SOUND_FX_TEST2",0xF3,0x11,C1},
	{"SOUND_FX_TEST3",0xF3,0xA1,E3},
	{NULL 			 ,0x00,0x00,0}
};

void sound_on()
{
	NR50_REG = 0x77;
    NR51_REG = 0xFF;
    NR52_REG = 0x80;
    snd_init = 0x01;
}

void sound_off()
{
	// dunno man
	NR50_REG = 0x00;
    NR51_REG = 0x00;
    NR52_REG = 0x00;
    snd_init = 0x00;
}

void play_effect(unsigned int effect)
{
	struct sound_container* fx = &sound_effects[effect];
	UWORD freq = frequencies[fx->note];

	if(snd_init != 1) return;

	// play sound
	NR11_REG = fx->length;
	NR12_REG = fx->volume;
	NR13_REG =        (UBYTE) freq & 0xFF;
	NR14_REG = 0x80 | (UBYTE) ((freq & 0x0700)>> 8);
}


