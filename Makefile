CC = lcc
CC_FLAGS = -Iinclude -Wl-m -Wl-j

EXE_NAME = game.gb
OUT_DIR = build

TARGET = $(OUT_DIR)/$(EXE_NAME)

all: $(TARGET)

build/%.o: src/%.c
	$(CC) $(CC_FLAGS) -c -o $@ $<

build/game.gb: build/game.o build/input.o build/sound.o build/sprite_manager.o
	$(CC) -o $@ $^

clean:
	rm -f $(OUT_DIR)/*.gb $(OUT_DIR)/*.o
