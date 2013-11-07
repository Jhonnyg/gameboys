CC = lcc
CC_FLAGS = -Iinclude -Ibuild/gen -Wl-m -Wl-j

PYTHON = python

EXE_NAME = game.gb
OUT = build
GEN = $(OUT)/gen

TARGET = $(OUT)/$(EXE_NAME)

all: $(TARGET)

$(GEN)/sprites.h: $(OUT)/pack_sprites.py assets/config.json
	mkdir -p $(GEN)
	$(PYTHON) build/pack_sprites.py
$(GEN)/sprite_data.h: $(OUT)/pack_sprites.py assets/config.json
	mkdir -p $(GEN)
	$(PYTHON) build/pack_sprites.py

$(OUT)/game.o: src/game.c $(GEN)/sprites.h
$(OUT)/sprite_manager.o: src/sprite_manager.c $(GEN)/sprite_data.h
$(OUT)/%.o: src/%.c
	$(CC) $(CC_FLAGS) -c -o $@ $<

build/game.gb: build/game.o build/input.o build/sound.o build/sprite_manager.o
	$(CC) -o $@ $^

clean:
	rm -f $(OUT)/*.gb $(OUT)/*.o $(GEN)/*
