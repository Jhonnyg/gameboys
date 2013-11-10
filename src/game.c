#include <gb/gb.h>

/* game includes */
#include "sprites.h"
#include "sprite_manager.h"
#include "input.h"
#include "sound.h"
#include "text.h"
#include "splash.h"
#include "map.h"
#include "quirks.h"

#include "gameplay.h"

/* music includes */
#include "gbt_player.h"

#include "assert.h"

extern const unsigned char * test_Data[];

/* keyboard state stored in input.c */
extern int key_start;
extern int key_select;

extern int key_a;
extern int key_b;

extern int key_up;
extern int key_down;
extern int key_left;
extern int key_right;

void main()
{
    /* martin timell tells the time */
    unsigned int frame = 0;
    int fx_cnt = 0;

    Sprite* gubbe;
    Sprite* snubbe;
    Sprite* sture;
    Sprite* arne;
    Sprite* ghost;

    Object test_object;

    int8 lol;
    /*Object* apa;*/

    World* w;
    Player* p;

    /* Set palettes */
    BGP_REG = OBP0_REG = OBP1_REG = 0xE4U;

    init_sprites();

    SWITCH_ROM_MBC1(6);

    w = init_world();
    p = init_player();

    test_object.type = PICKUP;
    test_object.pos.x = 40;
    test_object.pos.y = 40;
    test_object.hitbox.w = 10;
    test_object.hitbox.h = 10;

    touch(test_object.pos.x + test_object.pos.y + test_object.hitbox.w + test_object.hitbox.h);

    p->object->pos.x = 35;
    p->object->pos.y = 35;


    touch(p->object->pos.x);
    touch(p->object->pos.x + p->object->pos.y);

    add_object(w, p->object);
    add_object(w, &test_object);



    /*apa = collides(w, p->object);*/
    /*ASSERT(apa);*/

    /*gprintf("%d  ", test_object.pos.x);*/
    /*ASSERT(object_collides(p->object, &test_object));*/

    lol = object_collides(p->object, &test_object);
    /*gprintf("aoeu %d aoue", lol);*/

    /*SWITCH_ROM_MBC1(5);*/
    /*run_splash();*/

    gubbe = alloc_sprite(DUDETTE);
    snubbe = alloc_sprite(LITEN_GUBBE);
    sture = alloc_sprite(DUMLE);
    arne = alloc_sprite(LITEN_GUMMA);
    ghost = alloc_sprite(GHOST);


    put_sprite(gubbe, 30, 30);
    put_sprite(snubbe, 60, 60);
    put_sprite(sture, 60, 90);
    put_sprite(arne, 90, 90);
    put_sprite(ghost, 110, 90);

    start_animation(snubbe, 0);
    start_animation(arne, 0);
    start_animation(ghost, 0);

    /* pre-draw setup code */
    // disable_interrupts();
    // DISPLAY_OFF;
    // LCDC_REG = 0x67;

    /* set background */
    init_background();

    DISPLAY_ON;

    enable_interrupts();

    update_sprites(frame);
    /*draw_text("Banana PANIC!");*/

    /* music init & run */    

    #ifdef MUSIC_ON
        SOUND_ON; 
        gbt_play(test_Data, 2, 7 );
        gbt_loop(0);
        add_VBL(gbt_update);
    #endif

    /* gameloop */
    while(1)
    {
        /* wait for vertical blank, guess it's a complete screen redraw sync */
        wait_vbl_done();

        /* update input "state" */
        update_input( joypad() );

        /* INPUT STATES:
         * IS_PRESSED - is key pressed for the first time this frame?
         * IS_DOWN - is key down this frame?
         * IS_RELEASED - is key released this frame?
         */

        if ( IS_PRESSED(key_b) )       start_animation(gubbe, 0);

        if (IS_PRESSED(key_start)) {
            free_sprite(gubbe);
            gubbe = alloc_sprite(LITEN_GUMMA);
            put_sprite(gubbe, 90, 90);
        }

        if (IS_PRESSED(key_select)) {
            free_sprite(gubbe);
            gubbe = alloc_sprite(DUMLE);
            put_sprite(gubbe, 90, 90);
        }

        if ( IS_DOWN(key_up) )
        {
            shift_sprite(gubbe, 0, -2);
            scroll_bkg(0, -2);
        } 

        if ( IS_DOWN(key_down) )
        {
            shift_sprite(gubbe, 0, 2);
            scroll_bkg(0, 2);
        }

        if ( IS_DOWN(key_left) )
        {
            shift_sprite(gubbe, -2, 0);
            scroll_bkg(-2, 0);
        }

        if ( IS_DOWN(key_right) )
        {
            shift_sprite(gubbe, 2, 0);
            scroll_bkg(2, 0);
        }

        /*[>draw_sprite(0);<]*/
        update_sprites(frame);

        frame++;
    }
}

