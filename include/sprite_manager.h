/**
 * Convenience functions for composite sprites
 *
 * In GameBoy, sprites are natively either 8x8 or 8x16 pixels. To support larger
 * sprites, multiple tiles are emitted as a group, producing a composite sprite.
 *
 */
#ifndef SPRITE_MANAGER_H_
#define SPRITE_MANAGER_H_

#include "typedefs.h"

enum SpriteLayout {
    SPRITE8x8,
    SPRITE8x16,
    SPRITE16x8,
    SPRITE16x16
};

typedef struct s_sprite Sprite;
struct s_sprite {
    int8 id;

    int8 flags;

    uint8 x;
    uint8 y;

    enum SpriteLayout layout;
    uint8 frames;
    uint8 current_frame;

    int8 tiles[4];
};

void init_sprites();

/**
 * Allocate a composite sprite as specified type.
 *
 * Returns -1 when :(
 */

Sprite* alloc_sprite(unsigned int sprite_code);
void free_sprite(Sprite* sprite);

void show_sprite(Sprite* sprite);
void hide_sprite(Sprite* sprite);

void start_animation(Sprite* sprite, int8 once);
void stop_animation(Sprite* sprite);

void shift_sprite(Sprite* sprite, int dx, int dy);
void put_sprite(Sprite* sprite, int x, int y);

void update_sprites(unsigned int frame);

#endif  // SPRITE_MANAGER_H_
