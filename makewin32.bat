setlocal
set PATH=%PATH%;gbdk/bin/

:: compile game files
lcc -Iinclude -c -o build/input.o src/input.c
lcc -Iinclude -c -o build/sound.o src/sound.c
lcc -Iinclude -c -o build/game.o src/game.c

:: link into rom
lcc -o build/game.gb build/game.o build/input.o build/sound.o
