/**
 * Convenience functions for composite sprites
 *
 * In GameBoy, sprites are natively either 8x8 or 8x16 pixels. To support larger
 * sprites, multiple tiles are emitted as a group, producing a composite sprite.
 *
 */
#ifndef SPRITE_MANAGER_H_
#define SPRITE_MANAGER_H_

typedef int sprite;

enum SpriteLayout {
    SPRITE8x8,
    SPRITE8x16,
    SPRITE16x8,
    SPRITE16x16
};

struct Sprite {
    unsigned int id;

    unsigned int visible;

    unsigned int x;
    unsigned int y;

    enum SpriteLayout layout;
};

void init_sprites();

/**
 * Allocate a composite sprite as specified type.
 *
 * Returns -1 when :(
 */
sprite alloc_sprite(int hoolabaloo);
void free_sprite(sprite id);

void show_sprite(sprite id);
void hide_sprite(sprite id);

void shift_sprite(sprite id, int dx, int dy);
void put_sprite(sprite id, int x, int y);

void update_sprites();

#endif  // SPRITE_MANAGER_H_
