CC = gcc
CFLAGS = -Wall -g
LIBS = -lsx -lX11

SRCS = main.c
OBJS = $(SRCS:.c=.o)

TARGET = motus

all: $(TARGET)

$(TARGET): $(OBJS)
    $(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

clean:
    rm -f $(OBJS) $(TARGET)
