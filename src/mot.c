/**
* Ce programme est un jeu de réflexion basé sur les connaissances de la langue française
 * qu'a le joueur. Le programmme présente la première lettre d'un mot au joueur et ce
 * dernier a 6 essaies pour trouver le mot. Pour l'aider le programme indique au joueur
 * si les lettres du mot entré sont bien positionnées ou non
 *
 * @authors N. Amrane & E. Patijunas     neil.amrane@etu.univ-cotedazur.fr
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dico.h"
#include "mot.h"
#include <stdbool.h>
#define TAILLE_MAX_MOT 50


//retourne un nouveau mot après l'avoir créé
Mot initMot(){
    Mot res;//définition d'un nouveau mot
    char *p = malloc(sizeof(char) * TAILLE_MAX_MOT);  //allocation d'un espace mémoire p  //allocation d'un espace mémoire p
    choixMot(p);                        //appel de la fct° choixmot param : p
    res.mot = p;                        //asso° du mot aléatoire au nouveau mot
    res.size = strlen(res.mot);         // asso° au nveau mot taille mot aléatoire
    return res;
}


//retourne le test d'égalité entre la taille de la chaîne de caractères en paramètres et la constante int
 bool longueurMot(char *motPropose, char *motMystere) {
    if (strlen(motPropose) == strlen(motMystere)) {
        return true;
    }
    return false;
}



void positionLettres(char lettre, const char *motATrouver, char *etat, int index) {
    int i;
    int taille = strlen(motATrouver);

    etat[index] = '-'; //par défaut on déclare que la lettre est incorrecte;

    for(i = 0; i < taille; i++) {
        if(lettre == motATrouver[i]) {
            if(i == index) {
                etat[index] = 'x';   // la lettre est bien placée
            } else {
                etat[index] = 'o';   // la lettre est mal placée
            }
            break;
        }
    }
}


void position(char *motPropose, const char *motADeviner, char *etat) {
    int i, j;
    int taille = strlen(motPropose);

    for(i = 0; i < taille; i++) {
        etat[i] = '-'; // On initialise toutes les valeurs à '-'.
    }

    for(i = 0; i < taille; i++) {
        for(j = 0; j < taille; j++){
            // On vérifie d'abord si la lettre est dans la bonne position.
            if(i == j && motPropose[i] == motADeviner[j]) {
                etat[i] = 'x';
            }
            // On vérifie ensuite si la lettre est ailleurs dans le mot.
            else if(motPropose[i] == motADeviner[j]) {
                // On ne modifie la valeur que si elle n'est pas déjà marquée comme correctement positionnée.
                if(etat[i] != 'x') {
                    etat[i] = 'o';
                }
            }
        }
    }
}

int verifMot(char *motPropose, const char *motADeviner, char *etat){

    if(strlen(motPropose) != strlen(motADeviner)) {
        return 0; //la longueur du mot à deviner n'est pas la même que celle du mot proposé donc erreur
    }

    position(motPropose, motADeviner, etat);

    for (int i=0; i <strlen(motPropose); i++) {
        if (etat[i] != 'x') {
            return 0;
        }
    }
    return 1;
}

void affichageMot(const char* mot, const char* etat) {
    int taille = strlen(mot);

    for (int i = 0; i < taille; i++) {
        switch(etat[i]) {
            case 'x':    // La lettre est bien placée
                printf("%c", mot[i]);
                break;
            case 'o':    // La lettre est présente dans le mot, mais mal placée
                printf("o");
                break;
            default:    // La lettre n'est pas dans le mot
                printf("-");
                break;
        }
    }

    printf("\n");  // Ajoute une nouvelle ligne à la fin pour une séparation entre les tentatives
}
