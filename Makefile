LDFLAGS  := -std=c99 -no-pie -ffast-math
SRC_DIRS := src src/flower
SOURCES  := $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c))
OUTPUT   := $(patsubst src/%.c, bin/%.o, $(SOURCES))
TARGET   := main
INCLUDES := -Isrc `pkg-config --cflags raylib`
LIBS     := `pkg-config --libs raylib` -lm

.PHONY: all link run clean

all: $(OUTPUT) link run

bin/%.o: src/%.c
	@mkdir -p $(@D)
	@echo '[ Building $<... ]'
	gcc $(LDFLAGS) -c $^ -o $@ $(INCLUDES)

link:
	@echo '[ Linking... ]'
	gcc $(LDFLAGS) $(OUTPUT) -o $(TARGET) $(LIBS)

run:
	@echo '[ Running... ]'
	./$(TARGET)

clean:
	@echo '[ Cleaning... ]'
	rm -fr bin/*.o $(TARGET)
