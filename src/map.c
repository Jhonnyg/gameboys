#include <gb/gb.h>
#include "map.h"


const unsigned char _bktiles[] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
    17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32
};

extern const unsigned char bkgdata[];

const unsigned char _tmpmap[] = {
    0, 0, 0, 0, 0,
    0, 1, 1, 0, 0,
    0, 1, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};

void init_background()
{
    HIDE_BKG;
    SWITCH_ROM_MBC1(4);
    set_bkg_data(0, 0x20, bkgdata);
    SHOW_BKG;

    generate_visual_map( _tmpmap );

}

// TODO change position etc so its not 8bit values, since it's probably too small

unsigned char calculate_tile( unsigned char x, unsigned char y, unsigned char* _map )
{
    unsigned char tile = 0;

    if (_map[y * MAP_SIZE + x])
    {
        return 5; // return if "inside of wall"
    }  

    if (y > 0 && _map[(y-1) * MAP_SIZE + x]) // top
        tile |= 0x1;

    if (x < MAP_SIZE-1 && _map[y * MAP_SIZE + (x+1)]) // right
        tile |= 0x2;

    if (y < MAP_SIZE-1 && _map[(y+1) * MAP_SIZE + x]) // bottom
        tile |= 0x4;

    if (x > 0 && _map[y * MAP_SIZE + (x-1)]) // left
        tile |= 0x8;


    if (tile == 0)
    {
        if (x < MAP_SIZE-1 && y > 0 && _map[(y-1) * MAP_SIZE + (x+1)] ) // top-right
            tile |= 0x1;

        if (x < MAP_SIZE-1 && y < MAP_SIZE-1 && _map[(y+1) * MAP_SIZE + (x+1)] ) // bottom-right
            tile |= 0x2;

        if (x > 0 && y < MAP_SIZE-1 && _map[(y+1) * MAP_SIZE + (x-1)] ) // bottom-left
            tile |= 0x4;

        if (x > 0 && y > 0 && _map[(y-1) * MAP_SIZE + (x-1)] ) // bottom-left
            tile |= 0x8;

        if (tile != 0)
        {
            tile += 16;
        }
    }

    return tile;
}

void generate_visual_map( unsigned char* _map )
{
    unsigned char tile;
    unsigned char x;
    unsigned char y;

    HIDE_BKG;

    // build visible map from "REAAUHLL MAP"
    // TODO fix so that y and x start from the player position (minus the screensize or something?)
    for (y = 0; y < MAP_VISIBLE_SIZE; y++)
    {
        for (x = 0; x < MAP_VISIBLE_SIZE; x++)
        {
            tile = calculate_tile(x, y, _map);
            set_bkg_tiles(x, y, 1, 1, &(_bktiles[tile]));
        }
    }
    //set_bkg_tiles(0, 0, 16, 1, &_bktiles[0]); // DEBUG view all possible wall-combinations

    SHOW_BKG;

}

