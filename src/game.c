#include <gb/gb.h>
#include <stdio.h>

/* game includes */
#include "../include/sprites.h"
#include "../include/input.h"

/* keyboard state stored in input.c */
extern int key_a;
extern int key_b;

extern int key_up;
extern int key_down;
extern int key_left;
extern int key_right;

void main()
{
    /* martin timell tells the time */
    int frame = 0;

    /* pre-draw setup code */
    DISPLAY_ON;
    enable_interrupts(); 

    /* gameloop */
    while(1) 
    {
        /* wait for vertical blank, guess it's a complete screen redraw sync */
        wait_vbl_done();

        /* update input "state" */
        update_input( joypad() );

        /* deal with buttons bro */
        if ( IS_PRESSED(key_a) )        printf("KEY_PRESSED: A\n");
        else if ( IS_RELEASED(key_a) )  printf("KEY_RELEASED: A\n");

        if ( IS_PRESSED(key_b) )        printf("KEY_PRESSED: B\n");
        else if ( IS_RELEASED(key_b) )  printf("KEY_RELEASED: B\n");
        
        frame++;
    }
}