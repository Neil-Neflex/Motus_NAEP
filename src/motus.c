/**
 * Ce programme est un jeu de réflexion basé sur les connaissances de la langue française
 * qu'a le joueur. Le programmme présente la première lettre d'un mot au joueur et ce 
 * dernier a 6 essaies pour trouver le mot. Pour l'aider le programme indique au joueur 
 * si les lettres du mot entré sont bien positionnées ou non
 *
 * @authors N. Amrane & E. Patijunas      neil.amrane@etu.univ-cotedazur.fr
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "motus.h"
#include "mot.h"


void affichage(int t, int val[], const char mot[]){
    printf(mot);    // on affiche le mot entré par l'utilisateur
    printf("\n");
    for (int i=0; i<t; i++){   //le programme parcours le tableau d'entier resultat des tests
        switch (i)
        {
        case 1 : printf("x"); break;       //si la lettre est bien placée on affiche x
        case 2 : printf("o"); break;       //si la lettre est mal placée on affiche o
        default: printf("-");           //si la lettre n'est pas dans le mot on affiche -
        }
    }
    printf("\n");
}

int finPartie(int t, int p[]){
    //Problem
    for (int i=0; i<t;i++){
        if (p[i]!=1) return 0;
    }
    printf("Félicitations ! vous avez contré Motus");
    return 1;
}
int main(void){
    const char mot[7] = "Bonjour";
    int p[7] = {1,1,1,1,1,1,1};
    affichache(7, p, mot);
    int a = finPartie(7, p);
}
