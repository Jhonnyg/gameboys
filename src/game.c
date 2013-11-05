#include <gb/gb.h>
#include <stdio.h>

/* game includes */
#include "../include/sprites.h"
#include "../include/input.h"

/* keyboard state stored in input.c */
extern int key_start;
extern int key_select;

extern int key_a;
extern int key_b;

extern int key_up;
extern int key_down;
extern int key_left;
extern int key_right;

void init_background()
{
    int i = 0, j = 0;
    unsigned char _bktiles = { 1 };

    set_bkg_data( 1,1, sprite_gonads);

    /* draw amazing background sprite 01 */
    for(i = 0; i < 16; i+=16)
        for(j = 0; j < 16; j+=16)
            set_bkg_tiles(i, j, 1, 1, _bktiles);

    /* display 2 screen */
    SHOW_BKG;
}

void main()
{
    /* martin timell tells the time */
    int frame = 0;

    /* pre-draw setup code */
    // disable_interrupts();
    // DISPLAY_OFF;
    // LCDC_REG = 0x67;

    /* set background */
    // init_background();

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

        if ( IS_PRESSED(key_start) )        printf("KEY_PRESSED: START\n");
        else if ( IS_RELEASED(key_start) )  printf("KEY_RELEASED: START\n");

        if ( IS_PRESSED(key_select) )        printf("KEY_PRESSED: SELECT\n");
        else if ( IS_RELEASED(key_select) )  printf("KEY_RELEASED: SELECT\n");

        if ( IS_PRESSED(key_up) )        printf("KEY_PRESSED: UP\n");
        else if ( IS_RELEASED(key_up) )  printf("KEY_RELEASED: UP\n");

        if ( IS_PRESSED(key_down) )        printf("KEY_PRESSED: DOWN\n");
        else if ( IS_RELEASED(key_down) )  printf("KEY_RELEASED: DOWN\n");

        if ( IS_PRESSED(key_left) )        printf("KEY_PRESSED: LEFT\n");
        else if ( IS_RELEASED(key_left) )  printf("KEY_RELEASED: LEFT\n");

        if ( IS_PRESSED(key_right) )        printf("KEY_PRESSED: RIGHT\n");
        else if ( IS_RELEASED(key_right) )  printf("KEY_RELEASED: RIGHT\n");
        
        frame++;
    }
}