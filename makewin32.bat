setlocal
set PATH=%PATH%;gbdk/bin/

:: prepare generated sources

mkdir build\gen
call "build/pack_sprites.py"

:: compile game files
lcc -Iinclude -Ibuild/gen -c -o build/input.o src/input.c
lcc -Iinclude -Ibuild/gen -c -o build/sound.o src/sound.c
lcc -Iinclude -Ibuild/gen -c -o build/game.o src/game.c
lcc -Iinclude -Ibuild/gen -c -o build/sprite_manager.o src/sprite_manager.c
lcc -Iinclude -Ibuild/gen -c -o build/text.o src/text.c

:: link into rom
lcc -o build/game.gb build/game.o build/input.o build/sound.o build/sprite_manager.o build/text.o
