#include "sprite_manager.h"

#include "sprite_data.h"

#include <stdio.h>
#include <gb/gb.h>

struct Sprite sprites[40] = {
    { 0, 1, 0x30, 0x30, SPRITE16x16 }
};

/*int num_sprites = sizeof(sprites) / sizeof(struct Sprite);*/
int num_sprites = 1;

void init_sprites()
{
    // http://nocash.emubase.de/pandocs.htm#lcdcontrolregister
    SPRITES_8x8;
    SHOW_SPRITES;

    set_sprite_data(0, 16, sprite_data);
}

sprite alloc_sprite(int hoolabaloo)
{
    UINT8 addr = hoolabaloo & 0x3FU;
    UINT8 type = hoolabaloo >> 6;
    int new_sprite = -1;

    switch (type)
    {
        case 3:
            set_sprite_prop(3, 0x00);
            set_sprite_tile(3, addr+3);
        case 2:
            set_sprite_prop(2, 0x00);
            set_sprite_tile(2, addr+2);
        case 1:
            set_sprite_prop(1, 0x00);
            set_sprite_tile(1, addr+1);
        case 0:
            set_sprite_prop(0, 0x00);
            set_sprite_tile(0, addr);
    }

    /* TODO: Actually allocate :S */
    new_sprite = 0;
    sprites[new_sprite].layout = type;

    return new_sprite;
}

void free_sprite(sprite id)
{
    id += 0;
}

void show_sprite(sprite id)
{
    sprites[id].visible = 1;
}

void hide_sprite(sprite id)
{
    sprites[id].visible = 0;
}

void shift_sprite(sprite id, int dx, int dy)
{
    sprites[id].x += dx;
    sprites[id].y += dy;
}

void put_sprite(sprite id, int x, int y)
{
    sprites[id].x = x;
    sprites[id].y = y;
}

void update_sprites()
{
    int i;
    for (i=0; i!=num_sprites; i += 1)
    {
        switch (sprites[i].layout)
        {
            case SPRITE8x8:
                if (sprites[i].visible)
                    move_sprite(sprites[i].id, sprites[i].x, sprites[i].y);
                else
                    move_sprite(sprites[i].id, -128, -128);
                break;
            case SPRITE8x16:
                if (sprites[i].visible) {
                    move_sprite(sprites[i].id, sprites[i].x, sprites[i].y);
                    move_sprite(sprites[i].id+1, sprites[i].x, sprites[i].y+8);
                } else {
                    move_sprite(sprites[i].id, -128, -128);
                    move_sprite(sprites[i].id+1, -128, -128);
                }
                break;
            case SPRITE16x8:
                if (sprites[i].visible) {
                    move_sprite(sprites[i].id, sprites[i].x, sprites[i].y);
                    move_sprite(sprites[i].id+1, sprites[i].x+8, sprites[i].y);
                } else {
                    move_sprite(sprites[i].id, -128, -128);
                    move_sprite(sprites[i].id+1, -128, -128);
                }
                break;
            case SPRITE16x16:
                if (sprites[i].visible) {
                    move_sprite(sprites[i].id, sprites[i].x, sprites[i].y);
                    move_sprite(sprites[i].id+1, sprites[i].x, sprites[i].y+8);
                    move_sprite(sprites[i].id+2, sprites[i].x+8, sprites[i].y);
                    move_sprite(sprites[i].id+3, sprites[i].x+8, sprites[i].y+8);
                } else {
                    move_sprite(sprites[i].id, -128, -128);
                    move_sprite(sprites[i].id+1, -128, -128);
                    move_sprite(sprites[i].id+2, -128, -128);
                    move_sprite(sprites[i].id+3, -128, -128);
                }
        }
    }
}

