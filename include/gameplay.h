#ifndef _GAMEPLAY_H_
#define _GAMEPLAY_H_

#include "sprite_manager.h"
#include "typedefs.h"

enum ObjectType
{
    PLAYER,
    ENEMY,
    PICKUP
};

typedef struct Object_t Object;
struct Object_t
{
    enum ObjectType type;
    Sprite* sprite;
    void* traits;

    struct {
        uint8 w;
        uint8 h;
    } hitbox;

    struct {
        uint8 x;
        uint8 y;
    } pos;

    Object* next_object;
    Object* prev_object;
};

typedef struct Player_t
{
    Sprite* sprite;
    Object* object;

} Player;

typedef struct World_t
{
    Object* objects;
} World;

enum TileType
{
    EMPTY,
    WALL,
};

World* init_world();
Player* init_player();

int8 object_collides(Object* a, Object* b);
Object* collides(World* w, const Object* o);


void add_object(World* w, Object* o);
void remove_object(World* w, Object* o);

#endif
