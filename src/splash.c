#include "splash.h"
#include <gb/gb.h>
#include <stdio.h>
#include "sprite_manager.h"
#include "sprites.h"
#include "assert.h"

void run_splash()
{
	int count;

	Sprite* gbL = alloc_sprite(GAMEBOYS_L);
    Sprite* gbR = alloc_sprite(GAMEBOYS_R);

    Sprite* gobbe = alloc_sprite(LITEN_GUBBE);

	Sprite* prL = alloc_sprite(PRESENTS_L);
    Sprite* prR = alloc_sprite(PRESENTS_R);

    Sprite* ddL = alloc_sprite(DUNG_L);
    Sprite* ddR = alloc_sprite(DUNG_R);

	put_sprite(gbL, 144, 40);
	put_sprite(gbR, 144 + 16, 40);
	put_sprite(gobbe, 138, 42);

	put_sprite(prL, 144, 70);
	put_sprite(prR, 144 + 16, 70);

	put_sprite(ddL, 144, 100);
	put_sprite(ddR, 144 + 16, 100);

	count = 128;
	while(count > 0)
	{
		wait_vbl_done();
		shift_sprite(gbL, -1, 0);
		shift_sprite(gbR, -1, 0);
		shift_sprite(gobbe, -1, 0);
		shift_sprite(prL, -1, 0);
		shift_sprite(prR, -1, 0);
		shift_sprite(ddL, -1, 0);
		shift_sprite(ddR, -1, 0);
		update_sprites();
		count--;
	}

	free_sprite(gbL);
	free_sprite(gbR);
	free_sprite(prL);
	free_sprite(prR);
	free_sprite(ddL);
	free_sprite(ddL);
	free_sprite(gobbe);

	return;
}
