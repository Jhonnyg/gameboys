setlocal
set PATH=%PATH%;gbdk/bin/

:: prepare generated sources
python build/pack_sprites.py

:: compile game files
lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -Iinclude -c -o build/input.o src/input.c
lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -Iinclude -c -o build/sound.o src/sound.c
lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -Iinclude -c -o build/game.o src/game.c
lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -Iinclude -c -o build/sprite_manager.o src/sprite_manager.c
lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -Iinclude -c -o build/text.o src/text.c

:: gbt player files
lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -Iinclude -c -o build/gbt_player.o src/gbt_player.asm
lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -Iinclude -c -o build/gbt_player_bank1.o src/gbt_player_bank1.asm

:: music files
lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -Iinclude -c -o build/music.o assets/output.c

:: link into rom
lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -Wl-yt1 -Wl-yo4 -Wl-ya0 -o build/game.gb build/game.o build/input.o build/sound.o build/sprite_manager.o build/text.o build/gbt_player.o build/gbt_player_bank1.o build/music.o
