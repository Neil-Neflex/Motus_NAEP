CC = gcc
CFLAGS = -Wall -I/usr/include/libsx
LIBS = -lX11 -lXext -lXpm -lm -L/usr/lib/libsx

all: motus

motus: main.o vue.o callback.o data.o
	$(CC) -o motus main.o vue.o callback.o data.o $(LIBS)

main.o: main.c data.h vue.h
	$(CC) $(CFLAGS) -c main.c

vue.o: vue.c vue.h callback.h
	$(CC) $(CFLAGS) -c vue.c

callback.o: callback.c callback.h vue.h data.h
	$(CC) $(CFLAGS) -c callback.c

data.o: data.c data.h
	$(CC) $(CFLAGS) -c data.c
