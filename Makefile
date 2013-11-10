CC = lcc
CCFLAGS = -Iinclude -Ibuild/gen -Wl-m -Wl-j -Wa-l
LDFLAGS = -Wl-yt1 -Wl-yo8 -Wl-ya0

PYTHON = python

EXE_NAME = game.gb
OUT = build
GEN = $(OUT)/gen

TARGET = $(OUT)/$(EXE_NAME)

all: CCFLAGS += -DDEBUG
all: $(TARGET)

release: CC_FLAGS += -DMUSIC_ON
release: $(TARGET)

C_SOURCES = $(notdir $(wildcard src/*.c assets/*.c))
ASM_SOURCES = $(notdir $(wildcard src/*.asm))
GEN_OBJECTS = sprite_data.o
OBJECTS = $(addprefix $(OUT)/, $(C_SOURCES:%.c=%.o) $(ASM_SOURCES:%.asm=%.o) $(GEN_OBJECTS))
BINS = $(wildcard assets/*.bin)

# ROM Bank layout:
# _CODE: Main ROM bank (includes gbt_player.asm)
# _CODE_1: gbt_player_bank1.asm, declared in .asm
# _CODE_2: output.o (sound data, declared in .c)
# _CODE_3: sprite_data.o

$(OUT)/sprite_data.o: CCFLAGS += -Wf-ba3

# Custom dependencies
$(OUT)/splash.o: $(GEN)/sprites.h
$(OUT)/game.o: $(GEN)/sprites.h
$(OUT)/sprite_manager.o: $(GEN)/sprites.h
$(OUT)/sprite_data.o: $(GEN)/sprite_data.c

$(GEN)/sprites.h: $(OUT)/pack_sprites.py assets/config.json $(BINS)
	mkdir -p $(GEN)
	$(PYTHON) build/pack_sprites.py
$(GEN)/sprite_data.c: $(OUT)/pack_sprites.py assets/config.json $(BINS)
	mkdir -p $(GEN)
	$(PYTHON) build/pack_sprites.py

$(OUT)/%.o: src/%.asm
	$(CC) $(CCFLAGS) -c -o $@ $<
$(OUT)/%.o: src/%.c
	$(CC) $(CCFLAGS) -c -o $@ $<
$(OUT)/%.o: $(GEN)/%.c
	$(CC) $(CCFLAGS) -c -o $@ $<
$(OUT)/%.o: assets/%.c
	$(CC) $(CCFLAGS) -c -o $@ $<

$(TARGET): $(OBJECTS) build/sprite_data.o
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	rm -f $(OUT)/*.gb $(OUT)/*.o $(GEN)/*
