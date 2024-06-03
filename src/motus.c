/**
 * Ce programme est un jeu de réflexion basé sur les connaissances de la langue française
 * qu'a le joueur. Le programmme présente la première lettre d'un mot au joueur et ce
 * dernier a 6 essais pour trouver le mot. Pour l'aider le programme indique au joueur
 * si les lettres du mot entré sont bien positionnées ou non
 *
 * @authors N. Amrane & E. Patijunas      neil.amrane@etu.univ-cotedazur.fr edvinas.patiejunas@etu.univ-cotedazur.fr
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
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

int finPartie(int t, int p[]) {
    if (p == NULL || t <= 0) {
        printf("Erreur : paramètres invalides.\n");
        return -1; // on retourne -1 en cas d'erreur
    }

    for (int i = 0; i < t; i++) {
        if (p[i] != 1)
            return 0; // le jeu continue
    }

    printf("Félicitations ! Vous avez contré Motus\n");
    return 1; // le joueur a gagné
}

void viderBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void Partie() {
    const int TAILLE_MAX_MOT = 50;
    const int MAX_ESSAIS = 6;
    char motPropose[TAILLE_MAX_MOT + 1];
    char etat[TAILLE_MAX_MOT + 1];
    int essais = 0;
    int gagne = 0;
    bool condiLong = false;

    Mot motMystere = initMot();
    printf(" %s\n", motMystere.mot);
    etat[motMystere.size] = '\0';

    printf("Bienvenue dans le jeu Motus !\n");
    printf("Devinez le mot lettre par lettre.\n");

    while(essais < MAX_ESSAIS && gagne == 0) {
        printf("\nEntrez votre proposition : ");
        fgets(motPropose,TAILLE_MAX_MOT , stdin);


        // Supprimer le caractère de nouvelle ligne à la fin si présent
        motPropose[strcspn(motPropose, "\n")] = 0;

        gagne = verifMot(motPropose, motMystere.mot, etat);

        if (!longueurMot(motPropose, motMystere.mot) && gagne != 1) {
            printf("\nLe mot proposé n'est pas de la bonne longueur. Essayez à nouveau.\n");
            condiLong = true;
        }
        fflush(stdin);

        // Commentaire sur le mot proposé
        if (!condiLong) {
            affichageMot(motPropose,etat);
        }

        condiLong = false;
        essais++;
    }

    if(gagne == 1) {
        printf("\nFélicitations ! Vous avez trouvé le mot %s.\n", motMystere.mot);
    } else {
        printf("\nMalheureusement, vous n'avez pas trouvé le mot. Le mot était %s.\n", motMystere.mot);
    }

    free(motMystere.mot);
}
