LDFLAGS  := -std=c99 -Os -Wall -ffast-math -s USE_GLFW=3 --shell-file out/shell.html --preload-file assets -DWEB
SRC_DIRS := src src/flower
SOURCES  := $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c))
OUTPUT   := $(patsubst src/%.c, bin/%.o, $(SOURCES))
TARGET   := out/index.html
INCLUDES := -Isrc -Iinclude
LIBS     := -Llib -lraylib

.PHONY: all link run clean

all: $(OUTPUT) link run

bin/%.o: src/%.c
	@mkdir -p $(@D)
	@echo '[ Building $<... ]'
	emcc $(LDFLAGS) -c $^ -o $@ $(INCLUDES)

link:
	@echo '[ Linking... ]'
	emcc $(LDFLAGS) $(OUTPUT) -o $(TARGET) $(LIBS)

run:
	@echo '[ Running... ]'
	./$(TARGET)

clean:
	@echo '[ Cleaning... ]'
	rm -fr bin/*.o $(TARGET)
