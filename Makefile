TARGET = graph-traversal

SRCS = $(shell find ./src -type f -name *.c)
HEADS = $(shell find ./src -type f -name *.h)
OBJS = $(SRCS:.c=.o)

INCLUDES = $(shell pkg-config --libs --cflags sdl2 sdl2_gfx SDL2_ttf)

CC = clang

CFLAGS =  -Wall -Wextra -Wpedantic -std=c99 \
          -Wformat=2 -Wno-unused-parameter -Wshadow \
          -Wwrite-strings -Wstrict-prototypes -Wold-style-definition \
          -Wredundant-decls -Wnested-externs -Wmissing-include-dirs $(INCLUDES)

all: $(TARGET)

$(TARGET): $(SRCS) $(HEADS)
	$(CC) -o $(TARGET) $(SRCS) $(CFLAGS) 
	@./$(TARGET)

run: all
	@./$(TARGET)

debug:
	$(CC) -o $(TARGET) $(SRCS) $(CFLAGS) -g

sanatize:
	$(CC) -o $(TARGET) $(SRCS) $(CFLAGS) -fno-omit-frame-pointer -fsanitize=address
	ASAN_OPTIONS=detect_leaks=1 ./$(TARGET)

clean:
	$(RM) $(OBJS) $(TARGET)
	$(RM) -r *.dSYM/
