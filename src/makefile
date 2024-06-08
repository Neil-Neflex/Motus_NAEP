CC = gcc
CFLAGS = -Wall -I$(HOME)/C/PROJET_MOTUS/libsx/include
LDFLAGS = -L$(HOME)/C/PROJET_MOTUS/libsx/lib -lX11 -lXaw -lXmu -lXt -lXext -lXpm -lSM -lICE -lm -lSX

# Fichiers sources et objets
SRC = data.c vue.c callback.c
OBJ = $(SRC:.c=.o)

# Nom de l'exécutable
EXEC = newMotus

# Règle par défaut
all: $(EXEC)

# Règle pour créer l'exécutable
$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

# Règle pour compiler les fichiers .c en fichiers .o
%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

# Règle pour nettoyer les fichiers générés
clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: clean
