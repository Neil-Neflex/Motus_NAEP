#pragma once
#include <stdbool.h>

//Définition d'un nouveau type 'Mot'
typedef struct {
    int size;       //size spécifie la taille du mot
    char *mot;     //mot est une liste de caractère qui contient le mot
}Mot;

//crée un nouvel élément de type Mot
extern Mot initMot();
// Rôle : compare longueure du mot entré en param avec la valeur attendue
extern bool longueurMot(char *, char *);
// Rôle : renvoie vrai si pile est vide faux sinon
extern int presence(Mot,const char);
// Rôle : renvoie 1 si l'élément à la position entrée en param est bien la même pour
// le mot et l'entrée du joueur
extern void position(char *, const char *, char *);
// Rôle : vérifie le mot entrée par le joueur par rapport au mot à trouver
extern int verifMot(char *, const char *, char *);
//
extern void positionLettres(char, const char *, char *, int);

extern void affichageMot(const char *, const char *);
