#include <gb/gb.h>
#include <stdio.h>

/* game includes */
#include "sprite_manager.h"
#include "input.h"
#include "sound.h"
#include "text.h"

/* keyboard state stored in input.c */
extern int key_start;
extern int key_select;

extern int key_a;
extern int key_b;

extern int key_up;
extern int key_down;
extern int key_left;
extern int key_right;

int prev_key_start = 0;
int prev_key_select = 0;


/* TODO: TEMP YO */
#include "sprites.h"
/*#define S_GUBBE (0xC0U)*/
/*#define S_GONADS (0xC4U)*/
/*#define S_EARTH0 (0xC8U)*/
/*#define S_EARTH1 (0xCCU)*/

void init_background()
{
    int i = 0, j = 0;
    unsigned char _bktiles = { 1 };

    /*set_bkg_data( 1,1, sprite_gonads );*/

    /* draw amazing background sprite 01 */
    /*for(i = 0; i < 16; i+=16)*/
        /*for(j = 0; j < 16; j+=16)*/
            /*set_bkg_tiles(i, j, 1, 1, _bktiles);*/

    /*[> display 2 screen <]*/
    /*SHOW_BKG;*/
}


void main()
{
    /* martin timell tells the time */
    int frame = 0;
    Sprite* gubbe;
    Sprite* snubbe;
    Sprite* sture;

    /* Set palettes */
    BGP_REG = OBP0_REG = OBP1_REG = 0xE4U;

    init_sprites();
    gubbe = alloc_sprite(GUBBE);
    snubbe = alloc_sprite(GUBBE);
    sture = alloc_sprite(DUMLE);

    put_sprite(gubbe, 30, 30);
    put_sprite(snubbe, 60, 60);
    put_sprite(sture, 60, 90);

    /* pre-draw setup code */
    // disable_interrupts();
    // DISPLAY_OFF;
    // LCDC_REG = 0x67;

    /* set background */
    // init_background();

    sound_on();

    DISPLAY_ON;

    enable_interrupts();

    update_sprites();
    draw_text("Banana PANIC!");

    /* gameloop */
    while(1)
    {
        /* wait for vertical blank, guess it's a complete screen redraw sync */
        wait_vbl_done();

        /* update input "state" */
        update_input( joypad() );

        /* deal with buttons bro */
        /*if ( IS_PRESSED(key_a) )        draw_sprite();*/
        /*else if ( IS_RELEASED(key_a) )  draw_sprite();*/

        if ( IS_PRESSED(key_b) )        printf("g: %x\n", gubbe->id);
        /*else if ( IS_RELEASED(key_b) )  draw_sprite();*/

        if (IS_PRESSED(key_start) && (key_start ^ prev_key_start)) {
            free_sprite(gubbe);
            gubbe = alloc_sprite(GUBBE);
            put_sprite(gubbe, 90, 90);
        }
        /*else if ( IS_RELEASED(key_start) )  draw_sprite();*/

        if (IS_PRESSED(key_select)) {
            free_sprite(gubbe);
            gubbe = alloc_sprite(DUMLE);
            put_sprite(gubbe, 90, 90);
        }
        /*else if ( IS_RELEASED(key_select) )  draw_sprite();*/

        if ( IS_PRESSED(key_up) )        shift_sprite(gubbe, 0, -2);
        /*[>else if ( IS_RELEASED(key_up) )  draw_sprite();<]*/

        if ( IS_PRESSED(key_down) )        shift_sprite(gubbe, 0, 2);
        /*[>else if ( IS_RELEASED(key_down) )  draw_sprite();<]*/

        if ( IS_PRESSED(key_left) )         shift_sprite(gubbe, -2, 0);
        /*[>else if ( IS_RELEASED(key_left) )  draw_sprite();<]*/

        if ( IS_PRESSED(key_right) )        shift_sprite(gubbe, 2, 0);
        /*else if ( IS_RELEASED(key_right) )  draw_sprite();*/

        prev_key_start = key_start;
        /*draw_sprite(0);*/
        update_sprites();
        frame++;
    }
}

