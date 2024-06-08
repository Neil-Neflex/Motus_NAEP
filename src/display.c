#include <stdio.h>
#include <stdlib.h>
#include <libsx.h>
#include "data.h"
#include "callbacks.h"

#define TAILLEZONEAFFICHAGE 255
#define WORD_LENGTH 8 // Assuming the length of the word is 8
#define MAX_ATTEMPTS 5 // Assuming a maximum of 5 attempts

Widget ZoneSaisie; // la zone de saisie
Widget **WordLabels; // les labels pour afficher les mots
Widget BQuit; // le bouton Quit pour terminer le programme

/* Rôle: création et assemblage des widgets */
void init_display(int argc, char *argv[], void *d)
{
    int i, j;

    // créer les composants graphiques
    ZoneSaisie = MakeStringEntry(NULL, TAILLEZONEAFFICHAGE, NULL, NULL);
    BQuit = MakeButton("Quit", quit, NULL);

    // Créer les labels pour afficher les mots
    WordLabels = (Widget **)malloc(MAX_ATTEMPTS * sizeof(Widget *));
    for (i = 0; i < MAX_ATTEMPTS; i++) {
        WordLabels[i] = (Widget *)malloc(WORD_LENGTH * sizeof(Widget));
        for (j = 0; j < WORD_LENGTH; j++) {
            WordLabels[i][j] = MakeLabel(" ");
        }
    }

    // Placement des composants graphiques dans la fenêtre
    SetWidgetPos(ZoneSaisie, PLACE_UNDER, NULL, NO_CARE, NULL);
    SetWidgetPos(BQuit, PLACE_UNDER, ZoneSaisie, NO_CARE, NULL);

    for (i = 0; i < MAX_ATTEMPTS; i++) {
        for (j = 0; j < WORD_LENGTH; j++) {
            if (i == 0 && j == 0) {
                SetWidgetPos(WordLabels[i][j], PLACE_UNDER, BQuit, NO_CARE, NULL);
            } else if (j == 0) {
                SetWidgetPos(WordLabels[i][j], PLACE_UNDER, WordLabels[i - 1][0], NO_CARE, NULL);
            } else {
                SetWidgetPos(WordLabels[i][j], PLACE_RIGHT, WordLabels[i][j - 1], NO_CARE, NULL);
            }
        }
    }

    // pour gérer les couleurs
    GetStandardColors();

    // pour afficher l’interface
    ShowDisplay();
}
