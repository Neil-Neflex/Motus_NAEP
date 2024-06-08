CC = gcc
CFLAGS = -Wall -Wextra
LIBS = -lm -L/usr/X11R6/lib -lX11 -lXaw -lXmu -lXt -lXext -lXpm -lSM -lICE
INCLUDES = -I/chemin/vers/libsx/headers 

SRC = data.c vue.c callback.c
OBJ = $(SRC:.c=.o)
EXEC = motus

all: $(EXEC)

$(EXEC): $(OBJ)
    $(CC) $(OBJ) -o $(EXEC) $(LIBS)

%.o: %.c
    $(CC) -c $< -o $@ $(CFLAGS) $(INCLUDES)

clean:
    rm -f $(OBJ) $(EXEC)
