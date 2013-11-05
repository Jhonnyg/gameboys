#include <gb/gb.h>
#include "../include/input.h"

/* global key state */
int key_start 	= KEY_NONE;
int key_select 	= KEY_NONE;
int key_a 		= KEY_NONE;
int key_b 		= KEY_NONE;
int key_up 		= KEY_NONE;
int key_down 	= KEY_NONE;
int key_left 	= KEY_NONE;
int key_right 	= KEY_NONE;

void update_input( int state )
{
	/* warning: copy-paste code */
	if ( state & J_START ) key_start = KEY_PRESS;
	else 
	{
		if ( key_start == KEY_PRESS ) 
			 key_start = KEY_RELEASE;
		else key_start = KEY_NONE;
	}

	if ( state & J_SELECT ) key_select = KEY_PRESS;
	else 
	{
		if ( key_select == KEY_PRESS ) 
			 key_select = KEY_RELEASE;
		else key_select = KEY_NONE;
	}

	if ( state & J_B ) key_b = KEY_PRESS;
	else 
	{
		if ( key_b == KEY_PRESS ) 
			 key_b = KEY_RELEASE;
		else key_b = KEY_NONE;
	}

	if ( state & J_A ) key_a = KEY_PRESS;
	else 
	{
		if ( key_a == KEY_PRESS ) 
			 key_a = KEY_RELEASE;
		else key_a = KEY_NONE;
	}

	if ( state & J_DOWN ) key_down = KEY_PRESS;
	else 
	{
		if ( key_down == KEY_PRESS ) 
			 key_down = KEY_RELEASE;
		else key_down = KEY_NONE;
	}

	if ( state & J_UP ) key_up = KEY_PRESS;
	else 
	{
		if ( key_up == KEY_PRESS ) 
			 key_up = KEY_RELEASE;
		else key_up = KEY_NONE;
	}

	if ( state & J_LEFT ) key_left = KEY_PRESS;
	else 
	{
		if ( key_left == KEY_PRESS ) 
			 key_left = KEY_RELEASE;
		else key_left = KEY_NONE;
	}

	if ( state & J_RIGHT ) key_right = KEY_PRESS;
	else 
	{
		if ( key_right == KEY_PRESS ) 
			 key_right = KEY_RELEASE;
		else key_right = KEY_NONE;
	}
}