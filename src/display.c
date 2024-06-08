#include <libsx.h>
#include <stdio.h>
#include "callback.h"

// Déclaration des widgets globaux pour les utiliser dans les callbacks
Widget zone_text;

// Initialisation de l'affichage
void init_display(int argc, char *argv[])
{
    Widget test, restart, stop;

    // Génération des boutons utilisateur
    test = MakeButton("Tester", test_callback, NULL);  // Initialisation bouton tester
    restart = MakeButton("Recommencer", restart_callback, NULL); // Initialisation bouton recommencer
    stop = MakeButton("Arrêter", stop_callback, NULL); // Initialisation bouton arrêter

    SetWidgetPos(stop, PLACE_RIGHT, NULL, PLACE_ABOVE, NULL); // Positionnement bouton stop
    SetWidgetPos(test, PLACE_LEFT, NULL, PLACE_ABOVE, NULL); // Positionnement bouton test
    SetWidgetPos(restart, PLACE_CENTER, NULL, PLACE_ABOVE, NULL); // Positionnement bouton restart

    // Génération de l'espace textuel
    zone_text = MakeTextWidget(NULL, 20, 100, TRUE); // Initialisation zone textuelle
    SetWidgetPos(zone_text, PLACE_ABOVE, NULL, NO_CARE, NULL); // Positionnement de la zone de texte
}

// Rôle : crée une boîte orange avec la lettre à l'intérieur
void box_orangeDef(char l) {
    Widget orange;
    orange = MakeDrawArea(100, 100, NULL); // Boîte orange
    SetWidgetPos(orange, PLACE_UNDER, NULL, NO_CARE, NULL);
    DrawFilledBox(orange, GetFgColor(), GetRGBColor(255, 165, 0), 100, 100); // Boîte orange
    DrawText(orange, &l, 1, 50, 50); // Insertion de la lettre dans la case
}

// Rôle : crée une boîte bleue avec la lettre à l'intérieur
void box_bleuDef(char l) {
    Widget bleu;
    bleu = MakeDrawArea(100, 100, NULL); // Boîte bleue
    SetWidgetPos(bleu, PLACE_UNDER, NULL, NO_CARE, NULL);
    DrawFilledBox(bleu, GetFgColor(), GetRGBColor(0, 0, 255), 100, 100); // Boîte bleue
    DrawText(bleu, &l, 1, 50, 50); // Insertion de la lettre dans la case
}

// Rôle : crée une boîte rouge avec la lettre à l'intérieur
void box_rougeDef(char l) {
    Widget rouge;
    rouge = MakeDrawArea(100, 100, NULL); // Boîte rouge
    SetWidgetPos(rouge, PLACE_UNDER, NULL, NO_CARE, NULL);
    DrawFilledBox(rouge, GetFgColor(), GetRGBColor(255, 0, 0), 100, 100); // Boîte rouge
    DrawText(rouge, &l, 1, 50, 50); // Insertion de la lettre dans la case
}

// Rôle : génère les boîtes en fonction du résultat du test du mot que l'utilisateur a entré
void GenereBoxDisp(char result[], int pos_x, int pos_y) {
    for (int i = 0; i < strlen(result); i++) {
        switch (result[i]) {
            case 'O': // Lettre bien placée
                box_orangeDef(result[i]);
                break;
            case 'B': // Lettre présente mais mal placée
                box_bleuDef(result[i]);
                break;
            case 'R': // Lettre absente
                box_rougeDef(result[i]);
                break;
        }
    }
}
