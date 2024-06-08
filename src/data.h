#pragma once
#include <stdbool.h>

typedef struct {
    int size;
    char *mot;
}Mot;

extern int choixMot(char*);
extern int Gestion(void);
extern int aleatoire(int);
extern bool motExistant(const char*);

extern void affichage(int, int[], const char[]);
extern void Partie();
extern int finPartie(int, int[]);

extern Mot initMot();
extern bool longueurMot(char *, char *);
extern int presence(Mot,const char);
extern void position(char *, const char *, char *);
extern int verifMot(char *, const char *, char *);
extern void positionLettres(char, const char *, char *, int);
extern void affichageMot(const char *, const char *);
