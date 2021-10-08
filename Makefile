TARGET = app

SRCS  = $(shell find ./src -type f -name *.c)
HEADS = $(shell find ./src -type f -name *.h)
OBJS = $(SRCS:.c=.o)

CC = gcc
LDFLAGS = -lm -g


all: $(TARGET)

$(TARGET):
	$(CC) -o $(TARGET) $(SRCS)
	@./$(TARGET)

run: all
	@./$(TARGET)

debug:
	$(CC) -o $(TARGET) $(SRCS) -g

clean:
	$(RM) $(OBJS) $(TARGET)
	$(RM) -r *.dSYM/