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

// Rôle : crée une box orange avec la lettre à l'intérieur
void box_orangeDef(char p[], char l) {
    Widget orange, label;
    orange = MakeColorBox(GetRGBColor(255, 165, 0), 100, 100); // Orange box
    label = MakeLabel(&l); // Insertion de la lettre dans la case

    // Positionnement des éléments créés
    SetWidgetPos(orange, PLACE_UNDER, NULL, NO_CARE, NULL);
    SetWidgetPos(label, PLACE_UNDER, orange, NO_CARE, NULL);
}

// Rôle : crée une box bleue avec la lettre à l'intérieur
void box_bleuDef(char p[], char l) {
    Widget bleu, label;
    bleu = MakeColorBox(GetRGBColor(0, 0, 255), 100, 100); // Blue box
    label = MakeLabel(&l); // Insertion de la lettre dans la case

    // Positionnement des éléments créés
    SetWidgetPos(bleu, PLACE_UNDER, NULL, NO_CARE, NULL);
    SetWidgetPos(label, PLACE_UNDER, bleu, NO_CARE, NULL);
}

// Rôle : crée une box rouge avec la lettre à l'intérieur
void box_rougeDef(char p[], char l) {
    Widget rouge, label;
    rouge = MakeColorBox(GetRGBColor(255, 0, 0), 100, 100); // Red box
    label = MakeLabel(&l); // Insertion de la lettre dans la case

    // Positionnement des éléments créés
    SetWidgetPos(rouge, PLACE_UNDER, NULL, NO_CARE, NULL);
    SetWidgetPos(label, PLACE_UNDER, rouge, NO_CARE, NULL);
}

// Rôle : génère les boxes en fonction du résultat du test du mot que l'utilisateur a entré
void GenereBoxDisp(char result[], int pos_x, int pos_y) {
    for (int i = 0; i < strlen(result); i++) {
        switch (result[i]) {
            case 'O': // Lettre bien placée
                box_orangeDef(NULL, result[i]);
                break;
            case 'B': // Lettre présente mais mal placée
                box_bleuDef(NULL, result[i]);
                break;
            case 'R': // Lettre absente
                box_rougeDef(NULL, result[i]);
                break;
        }
    }
}
