#!/usr/bin/env python2

import json
import os
import sys

kTileSize = 16

def read_bin(bin_file):
    with open(bin_file, 'rb') as f:
        bytes = f.read()
        return bytes


# Modified from tools/compile.py
def hexify(name, data):
    if sys.version_info.major is 2:
        hex_chunk = ["0x%02X" % int(byte.encode("hex"), 16) + ("\n    " if index % 16 == 15 and index != len(data)-1 else "")
                     for index, byte in enumerate(data)]
    else:
        hex_chunk = ["0x%02X" % byte + ("\n    " if index % 16 == 15  and index != len(data)-1 else "")
                     for index, byte in enumerate(data)]
    hex_data = "const unsigned char %s[] = {\n     " % name
    hex_data += ",".join(hex_chunk)
    hex_data += "\n};\n"

    return hex_data


def main(args):
    # TODO: Argument parsing, if anyone feels like it
    build_dir = os.path.dirname(os.path.abspath(__file__))
    gen_dir = os.path.normpath(os.path.join(build_dir, 'gen'))
    assets_dir = os.path.normpath(
        os.path.join(build_dir, os.path.pardir, 'assets'))

    try:
        os.mkdir(gen_dir)
    except:
        pass

    config_file_path = os.path.join(assets_dir, 'config.json')

    layout_map = {
        '8x8': 0,
        '8x16': 1,
        '16x8': 2,
        '16x16': 3
    }

    tile_data = b''
    defines = []
    start = 0
    with open(os.path.join(config_file_path), 'r') as config_file:
        config = json.load(config_file)

        for s in config['sprites']:
            bin_data = read_bin(os.path.join(assets_dir, s['file_name']))
            assert len(bin_data) % kTileSize == 0
            assert s['layout'] in layout_map, "Layout must be one of 8x8, 8x16, 16x8 or 16x16"

            tile_data += bin_data

            layout = layout_map[s['layout']]
            defines.append((s['name'], layout << 6 | int(start/kTileSize)))

            start += len(bin_data)

    with open(os.path.join(gen_dir, 'sprites.h'), 'w') as sprites:
        sprites.write("#ifndef SPRITES_H_\n#define SPRITES_H_\n\n")
        sprites.writelines(["#define %s 0x%02X\n" % (name, layout) for (name, layout) in defines])
        sprites.write("\n#endif  // SPRITES_H_\n")

    with open(os.path.join(gen_dir, 'sprite_data.h'), 'w') as sprite_data:
        sprite_data.write("#ifndef SPRITE_DATA_H_\n#define SPRITE_DATA_H_\n\n")
        sprite_data.write(hexify('sprite_data', tile_data))
        sprite_data.write("\n#endif  // SPRITE_DATA_H_")


if __name__ == '__main__':
    main(sys.argv[1:])
