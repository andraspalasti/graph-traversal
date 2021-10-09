TARGET = app

SRCS  = $(shell find ./src -type f -name *.c)
HEADS = $(shell find ./src -type f -name *.h)
OBJS = $(SRCS:.c=.o)

CC = gcc

CFLAGS =  -Wall -Wextra -Wpedantic -std=c99 \
          -Wformat=2 -Wno-unused-parameter -Wshadow \
          -Wwrite-strings -Wstrict-prototypes -Wold-style-definition \
          -Wredundant-decls -Wnested-externs -Wmissing-include-dirs

all: $(TARGET)

$(TARGET):
	$(CC) -o $(TARGET) $(SRCS) $(CFLAGS)
	@./$(TARGET)

run: all
	@./$(TARGET)

debug:
	$(CC) -o $(TARGET) $(SRCS) $(CFLAGS) -g

clean:
	$(RM) $(OBJS) $(TARGET)
	$(RM) -r *.dSYM/