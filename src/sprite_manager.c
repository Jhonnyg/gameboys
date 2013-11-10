#include "sprite_manager.h"

#include <gb/gb.h>
#include <string.h>

#include "assert.h"
#include "sprite_data.h"
#include "quirks.h"


int8 allocated_tiles[40] = { -1 };
int8 allocation_index = 0;
int8 num_allocated_tiles = 0;

Sprite sprites[40]; // = { -1 };
int8 sprites_index = 0;


void init_sprites()
{
    // http://nocash.emubase.de/pandocs.htm#lcdcontrolregister
    SPRITES_8x8;
    SHOW_SPRITES;

    set_sprite_data(0, sizeof(sprite_data)/16, sprite_data);
}

Sprite* alloc_sprite(uint8 sprite_code)
{
    Sprite* s;

    int8 pending_allocations[4];
    int8 pending_index = 0;
    int8 required_tiles;

    uint8 addr = sprite_code & 0x3FU;
    uint8 layout = sprite_code >> 6;
    uint8 i;


    required_tiles = layout + 1;
    if (required_tiles == 3)
        required_tiles = 2;

    if (num_allocated_tiles + required_tiles > 40)
        return -1;

    for (i=allocation_index; i<sizeof(allocated_tiles); i += 1)
        if (allocated_tiles[i] != i) {
            pending_allocations[pending_index] = i;
            pending_index += 1;

            if (pending_index == required_tiles)
                goto alloc_complete;
        }

    for (i=0; i<allocation_index; i += 1)
        if (allocated_tiles[i] != i) {
            pending_allocations[pending_index] = i;
            pending_index += 1;

            if (pending_index == required_tiles)
                goto alloc_complete;
        }

    NOT_REACHED;
    return -1;

alloc_complete:
    allocation_index = i+1;

    for (i=sprites_index; i<40; i += 1)
        if (sprites[i].id != i)
            goto write_struct;

    for (i=0; i<sprites_index; i += 1)
        if (sprites[i].id != i)
            goto write_struct;

    NOT_REACHED;
    return -1;

write_struct:
    sprites_index = i+1;

    s = &sprites[i];
    s->id = i;
    s->visible = 1;
    s->x = 0;
    s->y = 0;
    s->layout = layout;
    memcpy(s->tiles, pending_allocations, required_tiles);

    switch (layout)
    {
        case SPRITE16x16:
            set_sprite_prop(pending_allocations[3], 0x00);
            set_sprite_tile(pending_allocations[3], addr+3);
            set_sprite_prop(pending_allocations[2], 0x00);
            set_sprite_tile(pending_allocations[2], addr+2);
            allocated_tiles[pending_allocations[3]] = pending_allocations[3];
            allocated_tiles[pending_allocations[2]] = pending_allocations[2];
        case SPRITE16x8:
        case SPRITE8x16:
            set_sprite_prop(pending_allocations[1], 0x00);
            set_sprite_tile(pending_allocations[1], addr+1);
            allocated_tiles[pending_allocations[1]] = pending_allocations[1];
        case SPRITE8x8:
            set_sprite_prop(pending_allocations[0], 0x00);
            set_sprite_tile(pending_allocations[0], addr);
            allocated_tiles[pending_allocations[0]] = pending_allocations[0];
    }

    num_allocated_tiles += required_tiles;
    touch(s->layout);

    return s;
}

void free_sprite(Sprite* sprite)
{
    sprites_index = sprite->id;
    sprite->id = -1;

    switch (sprite->layout)
    {
        case SPRITE16x16:
            move_sprite(sprite->tiles[3], 0, 0);
            move_sprite(sprite->tiles[2], 0, 0);
            allocated_tiles[sprite->tiles[3]] = -1;
            allocated_tiles[sprite->tiles[2]] = -1;
            num_allocated_tiles -= 2;
        case SPRITE16x8:
        case SPRITE8x16:
            move_sprite(sprite->tiles[1], 0, 0);
            allocated_tiles[sprite->tiles[1]] = -1;
            num_allocated_tiles -= 1;
        case SPRITE8x8:
            move_sprite(sprite->tiles[0], 0, 0);
            allocated_tiles[sprite->tiles[0]] = -1;
            num_allocated_tiles -= 1;
    }
}

void show_sprite(Sprite* sprite)
{
    sprite->visible = 1;
}

void hide_sprite(Sprite* sprite)
{
    sprite->visible = 0;
}

void shift_sprite(Sprite* sprite, int dx, int dy)
{
    sprite->x += dx;
    sprite->y += dy;
}

void put_sprite(Sprite* sprite, int x, int y)
{
    sprite->x = x;
    sprite->y = y;
}

void update_sprites()
{
    uint8 i;
    int base_x;
    int base_y;

    for (i=0; i!=40; i += 1)
    {
        if (sprites[i].id != i)
            continue;

        if (sprites[i].visible) {
            base_x = sprites[i].x;
            base_y = sprites[i].y;
        } else {
            base_x = 0;
            base_y = 0;
        }

        move_sprite(sprites[i].tiles[0], base_x, base_y);

        switch (sprites[i].layout)
        {
            case SPRITE16x8:
                move_sprite(sprites[i].tiles[1], base_x+8, base_y);
                break;
            case SPRITE16x16:
                move_sprite(sprites[i].tiles[2], base_x+8, base_y);
                move_sprite(sprites[i].tiles[3], base_x+8, base_y+8);
            case SPRITE8x16:
                move_sprite(sprites[i].tiles[1], base_x, base_y+8);

        }
    }
}

