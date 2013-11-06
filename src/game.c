#include <gb/gb.h>
#include <stdio.h>

/* game includes */
#include "sprites.h"
#include "input.h"
#include "sound.h"

/* keyboard state stored in input.c */
extern int key_start;
extern int key_select;

extern int key_a;
extern int key_b;

extern int key_up;
extern int key_down;
extern int key_left;
extern int key_right;

int pos_x;
int pos_y;

enum SpriteLayout {
    SPRITE8x8,
    SPRITE8x16,
    SPRITE16x8,
    SPRITE16x16
};

struct Sprite {
    UINT16 x;
    UINT16 y;
    UINT16 id;

    enum SpriteLayout layout;
};

struct Sprite dude_s = {
    0x30, 0x30, 0, SPRITE16x16
};

/*void draw_sprite(struct Sprite s)*/
void draw_sprite()
{
    switch (dude_s.layout)
    {
        case SPRITE8x8:
            move_sprite(dude_s.id, dude_s.x, dude_s.y);
            break;
        case SPRITE8x16:
            move_sprite(dude_s.id, dude_s.x, dude_s.y);
            move_sprite(dude_s.id+1, dude_s.x, dude_s.y+8);
            break;
        case SPRITE16x8:
            move_sprite(dude_s.id, dude_s.x, dude_s.y);
            move_sprite(dude_s.id+1, dude_s.x+8, dude_s.y);
            break;
        case SPRITE16x16:
            move_sprite(dude_s.id, dude_s.x, dude_s.y);
            move_sprite(dude_s.id+1, dude_s.x, dude_s.y+8);
            move_sprite(dude_s.id+2, dude_s.x+8, dude_s.y);
            move_sprite(dude_s.id+3, dude_s.x+8, dude_s.y+8);

    }
}

void init_background()
{
    int i = 0, j = 0;
    unsigned char _bktiles = { 1 };

    set_bkg_data( 1,1, sprite_gonads );

    /* draw amazing background sprite 01 */
    for(i = 0; i < 16; i+=16)
        for(j = 0; j < 16; j+=16)
            set_bkg_tiles(i, j, 1, 1, _bktiles);

    /* display 2 screen */
    SHOW_BKG;
}

void init_sprites()
{
    set_sprite_data(0, 4, dude);
    set_sprite_prop(0, 0x00);
    set_sprite_prop(1, 0x00);
    set_sprite_prop(2, 0x00);
    set_sprite_prop(3, 0x00);
    set_sprite_tile(0, 0);
    set_sprite_tile(1, 1);
    set_sprite_tile(2, 2);
    set_sprite_tile(3, 3);
    set_sprite_tile(4, 4);



}

/*void draw_sprite()*/
/*{*/

    /*SPRITES_8x8;*/
    /*move_sprite(0, 80-pos_x, 80-pos_y);*/
    /*move_sprite(1, 80-pos_x, 80-pos_y+8);*/
    /*move_sprite(2, 80-pos_x+8, 80-pos_y);*/
    /*move_sprite(3, 80-pos_x+8, 80-pos_y+8);*/

    /*SPRITES_8x16;*/
    /*move_sprite(0, pos_x, pos_y);*/
    /*move_sprite(1, pos_x, pos_y+8);*/
    /*move_sprite(2, pos_x+8, pos_y);*/
    /*move_sprite(3, pos_x+8, pos_y+8);*/
/*}*/

void main()
{
    /* martin timell tells the time */
    int frame = 0;

    pos_x = 0x30;
    pos_y = 0x30;

    /* Set palettes */
    BGP_REG = OBP0_REG = OBP1_REG = 0xE4U;

    SPRITES_8x8;

    init_sprites();
    draw_sprite();

    /* pre-draw setup code */
    // disable_interrupts();
    // DISPLAY_OFF;
    // LCDC_REG = 0x67;

    /* set background */
    // init_background();

    sound_on();

    DISPLAY_ON;
    SHOW_SPRITES;
    
    enable_interrupts(); 


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

        /*if ( IS_PRESSED(key_b) )        draw_sprite();*/
        /*else if ( IS_RELEASED(key_b) )  draw_sprite();*/

        /*if ( IS_PRESSED(key_start) )        draw_sprite();*/
        /*else if ( IS_RELEASED(key_start) )  draw_sprite();*/

        /*if ( IS_PRESSED(key_select) )        draw_sprite();*/
        /*else if ( IS_RELEASED(key_select) )  draw_sprite();*/

        if ( IS_PRESSED(key_up) )        dude_s.y -= 2;
        /*else if ( IS_RELEASED(key_up) )  draw_sprite();*/

        if ( IS_PRESSED(key_down) )        dude_s.y += 2;
        /*else if ( IS_RELEASED(key_down) )  draw_sprite();*/

        if ( IS_PRESSED(key_left) )        dude_s.x -= 2;
        /*else if ( IS_RELEASED(key_left) )  draw_sprite();*/

        if ( IS_PRESSED(key_right) )        dude_s.x += 2;
        /*else if ( IS_RELEASED(key_right) )  draw_sprite();*/
        
        draw_sprite();
        frame++;
    }
}

