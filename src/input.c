#include <gb/gb.h>
#include "input.h"

/* global key state */
int key_start 	= KEY_NONE;
int key_select 	= KEY_NONE;
int key_a 		= KEY_NONE;
int key_b 		= KEY_NONE;
int key_up 		= KEY_NONE;
int key_down 	= KEY_NONE;
int key_left 	= KEY_NONE;
int key_right 	= KEY_NONE;

void update_key( int state, int *key, unsigned int key_enum )
{
	if ( state & key_enum ) 
	{
		if ( (*key) == KEY_NONE )
			 (*key) = KEY_PRESS;
		else (*key) = KEY_DOWN;
	} else 
	{
		if ( (*key) == KEY_PRESS ) 
			 (*key) = KEY_RELEASE;
		else (*key) = KEY_NONE;
	}
}

void update_input( int state )
{
	update_key(state,&key_start,J_START);
	update_key(state,&key_select,J_SELECT);
	update_key(state,&key_a,J_A);
	update_key(state,&key_b,J_B);
	update_key(state,&key_up,J_UP);
	update_key(state,&key_down,J_DOWN);
	update_key(state,&key_left,J_LEFT);
	update_key(state,&key_right,J_RIGHT);
}

