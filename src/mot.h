#pragma once

//Définition d'un nouveau type 'Mot'
typedef struct { 
    int size;       //size spécifie la taille du mot
    char mot[];     //mot est une liste de caractère qui contient le mot
}Mot;

//crée un nouvel élément de type Mot
extern Mot initMot(); 
// Rôle : compare longueure du mot entré en param avec la valeur attendue
extern int longueurMot(Mot,const int);
// Rôle : renvoie vrai si pile est vide faux sinon
extern int presence(Mot,const char);
// Rôle : renvoie 1 si l'élément à la position entrée en param est bien la même pour
// le mot et l'entrée du joueur
extern int position (int, Mot, const char[]);
// Rôle : vérifie le mot entrée par le joueur par rapport au mot à trouver
extern char * verifMot(Mot, const char[]);
//
extern int positionLettres();