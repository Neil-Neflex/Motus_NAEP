#pragma once

//Définition d'un nouveau type 'Mot'
typedef struct { 
    int size;       //size spécifie la taille du mot
    char mot[];     //mot est une liste de caractère qui contient le mot
}Mot;


extern Mot initMot(); 
// Rôle : compare longueure du mot entré en param avec la valeur attendue
extern int longueurMot(const char[],const int);
// Rôle : renvoie vrai si pile est vide faux sinon
extern int presence(const char[],const char);
// Rôle : renvoie 1 si l'élément à la position entrée en param est bien la même pour
// les deux mots 
extern int position (int, const char[], const char[]); 
// Rôle : empile en sommet de la pile un nouvel élément