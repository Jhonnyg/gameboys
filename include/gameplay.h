#ifndef _GAMEPLAY_H_
#define _GAMEPLAY_H_

#include "sprite_manager.h"

typedef struct Player_t
{
	Sprite* sprite;
} Player;

typedef struct World_t
{
	int x;
} World;

enum TileType
{
	EMPTY,
	WALL,
	ENEMY,
	POWERUP
};

// 1: true, 0: false
uint8 collides(World* w, Player* p);

#endif
