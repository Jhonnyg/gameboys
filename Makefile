CC = lcc
CC_FLAGS = -Iinclude -Ibuild/gen -Wl-m -Wl-j -Wa-l -Wl-yt1 -Wl-yo4 -Wl-ya0

PYTHON = python

EXE_NAME = game.gb
OUT = build
GEN = $(OUT)/gen

TARGET = $(OUT)/$(EXE_NAME)

all: CC_FLAGS += -DDEBUG
all: $(TARGET)

release: CC_FLAGS += -DMUSIC_ON
release: $(TARGET)

$(GEN)/sprites.h: $(OUT)/pack_sprites.py assets/config.json
	mkdir -p $(GEN)
	$(PYTHON) build/pack_sprites.py
$(GEN)/sprite_data.h: $(OUT)/pack_sprites.py assets/config.json
	mkdir -p $(GEN)
	$(PYTHON) build/pack_sprites.py

$(OUT)/game.o: src/game.c $(GEN)/sprites.h
$(OUT)/sprite_manager.o: src/sprite_manager.c $(GEN)/sprite_data.h

# i'm sorry
$(OUT)/output.o: assets/output.c 
	$(CC) $(CC_FLAGS) -c -o $@ $<
$(OUT)/%.o: src/%.asm
	$(CC) $(CC_FLAGS) -c -o $@ $<
$(OUT)/%.o: src/%.c
	$(CC) $(CC_FLAGS) -c -o $@ $<

build/game.gb: build/game.o build/input.o build/sound.o build/sprite_manager.o build/text.o build/gbt_player.o build/gbt_player_bank1.o build/output.o
	$(CC) $(CC_FLAGS) -o $@ $^

clean:
	rm -f $(OUT)/*.gb $(OUT)/*.o $(GEN)/*
