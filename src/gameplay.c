#include "gameplay.h"

#include "assert.h"
#include "sprites.h"

#include "quirks.h"

#define PLAYER_WIDTH 10
#define PLAYER_HEIGHT 10

Player player;
Object player_object;

World world;

World* init_world()
{
    world.objects = NULL;
}

void add_object(World* w, Object* o)
{
    w->objects->prev_object = o;
    o->next_object = w->objects->prev_object;
    o->prev_object = NULL;

    w->objects = o;
}

void remove_object(World* w, Object* o)
{
    if (w->objects == o) {
        w->objects = o->next_object;
    } else {
        ASSERT(o->prev_object);
        o->prev_object = o->next_object;
    }

    o->next_object = NULL;
    o->prev_object = NULL;
}

Player* init_player()
{
    player.object = &player_object;
    player.object->sprite = alloc_sprite(DUDETTE);

    player.object->hitbox.w = PLAYER_WIDTH;
    player.object->hitbox.h = PLAYER_HEIGHT;

    return &player;
}

int8 object_collides(Object* a, Object* b)
{
    uint8 ax = a->pos.x;
    uint8 ay = a->pos.y;
    uint8 aw = a->hitbox.w;
    uint8 ah = a->hitbox.h;

    uint8 bx = b->pos.x;
    uint8 by = b->pos.y;
    uint8 bw = b->hitbox.w;
    uint8 bh = b->hitbox.h;

    if (ax + aw <= bx)
        return 0;

    if (bx + bw <= ax)
        return 0;

    if (ay + ah <= by)
        return 0;

    if (by + bh <= ay)
        return 0;

    return 1;
}

Object* collides(World* w, const Object* o)
{
    Object* current_object = w->objects;

    while (current_object)
    {
        if (o == current_object)
            continue;

        if (object_collides(o, current_object)) {
            return current_object;
        }

        current_object = current_object->next_object;
    }

    return NULL;
}

