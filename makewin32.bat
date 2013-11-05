:: compile game files
lcc -Wa-l -Wl-m -Wl-j -c -o build/input.o src/input.c
lcc -Wa-l -Wl-m -Wl-j -c -o build/sound.o src/sound.c
lcc -Wa-l -Wl-m -Wl-j -c -o build/game.o src/game.c

:: link into rom
lcc -Wa-l -Wl-m -Wl-j -o build/game.gb build/game.o build/input.o build/sound.o