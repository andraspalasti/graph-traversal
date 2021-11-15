TARGET = graph-traversal

CC = clang

SRC = src
OBJ = obj

LIBS = $(shell pkg-config --libs --cflags sdl2 sdl2_gfx SDL2_ttf) # libs to include

CFLAGS = -Wall -std=c99 -Wno-unused-command-line-argument $(LIBS)

SRCS = $(wildcard $(SRC)/*.c) # get all src files
OBJS = $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS)) # create all obj file names from src files

all: $(TARGET)

# create executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

debug:
	$(CC) -o $(TARGET) $(SRCS) $(CFLAGS) -g

# create all object files
$(OBJ)/%.o: $(SRC)/%.c
	mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(TARGET)
	$(RM) -r $(OBJ)
