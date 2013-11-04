#ifndef __INPUT_H__
#define __INPUT_H__

#define KEY_NONE 	0
#define KEY_PRESS 	1
#define KEY_RELEASE 2

#define IS_PRESSED(key) key == KEY_PRESS
#define IS_RELEASED(key) key == KEY_RELEASE

void update_input( int state );

#endif