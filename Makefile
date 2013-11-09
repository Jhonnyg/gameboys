CC = lcc
CCFLAGS = -Iinclude -Ibuild/gen -Wl-m -Wl-j -Wa-l
LDFLAGS = -Wl-yt1 -Wl-yo4 -Wl-ya0

PYTHON = python

EXE_NAME = game.gb
OUT = build
GEN = $(OUT)/gen

TARGET = $(OUT)/$(EXE_NAME)

all: CCFLAGS += -DDEBUG
all: $(TARGET)

release: $(TARGET)

C_SOURCES = $(notdir $(wildcard src/*.c assets/*.c))
ASM_SOURCES = $(notdir $(wildcard src/*.asm))
OBJECTS = $(addprefix $(OUT)/, $(C_SOURCES:%.c=%.o) $(ASM_SOURCES:%.asm=%.o))

# Custom dependencies
$(OUT)/game.o: $(GEN)/sprites.h
$(OUT)/sprite_manager.o: $(GEN)/sprite_data.h

$(GEN)/sprites.h: $(OUT)/pack_sprites.py assets/config.json
	mkdir -p $(GEN)
	$(PYTHON) build/pack_sprites.py
$(GEN)/sprite_data.h: $(OUT)/pack_sprites.py assets/config.json
	mkdir -p $(GEN)
	$(PYTHON) build/pack_sprites.py

$(OUT)/%.o: src/%.asm
	$(CC) $(CCFLAGS) -c -o $@ $<
$(OUT)/%.o: src/%.c
	$(CC) $(CCFLAGS) -c -o $@ $<
$(OUT)/%.o: assets/%.c
	$(CC) $(CCFLAGS) -c -o $@ $<

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	rm -f $(OUT)/*.gb $(OUT)/*.o $(GEN)/*
