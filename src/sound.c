#include <gb/gb.h>
#include "sound.h"
#include "sound_data.h"

struct sound_container {
	char* name;
	UBYTE volume;
	UBYTE length;
	UBYTE note;
};

const struct sound_container sound_effects[] = {
	{"SOUND_FX_TEST",0xF3,0x10,C3}, // guess!
	{NULL,0,0,0,0}
};

/*
struct sound_channel {
	UBYTE tmp;
};

const struct sound_channel channels[] = { 
	{0}, 	// Square 1
	{0}, 	// Square 2 
	{0}, 	// Waveform
	{0} 	// Noise
}; */

void sound_on()
{
	NR50_REG = 0x77;
    NR51_REG = 0xFF;
    NR52_REG = 0x80;
}

void sound_off()
{
	// dunno man
}

void play_effect(unsigned int effect)
{
	struct sound_container* fx = &sound_effects[effect];
	UWORD freq = frequencies[fx->note];

	// play sound
	NR11_REG = fx->length;
	NR12_REG = fx->volume;
	NR13_REG =        (UBYTE) freq & 0xFF;
	NR14_REG = 0x80 | (UBYTE) ((freq & 0x0700)>> 8);
}


// void play_note(UBYTE notevalue, UBYTE length){

//     UBYTE flo, fhi;

//     UWORD freq = frequencies[notevalue];



//     // Volume envelope

//     NR12_REG = 0xF3;    // F=maximum volume, 3=sound fade out

//     // Waveform

//     NR11_REG = length;    // 50% square wave

//     // Frequency

//     flo = (UBYTE)freq & 0xFF;

//     fhi = (UBYTE)((freq & 0x0700)>>8);

//     NR13_REG = flo;    // Take lower 8 bits from the function argument

//     NR14_REG = 0x80 | fhi;

//     // Take 3 more bits from the function argument, and set the start bit

// }




