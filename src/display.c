#include <libsx.h>
#include <stdio.h>
#include "callback.h"

// Déclaration des widgets globaux pour les utiliser dans les callbacks
Widget zone_text;

// Callback pour redessiner une boîte colorée
void RedrawColorBox(Widget w, int width, int height, void *data)
{
    int color = *(int *)data;
    SetFgColor(w, color);
    DrawFilledBox(w, 0, 0, width, height);
}

// Initialisation de l'affichage
void init_display(int argc, char *argv[])
{
    Widget test, restart, stop;

    // Génération des boutons utilisateur
    test = MakeButton("Tester", test_callback, NULL);  // Initialisation bouton tester
    restart = MakeButton("Recommencer", restart_callback, NULL); // Initialisation bouton recommencer
    stop = MakeButton("Arrêter", stop_callback, NULL); // Initialisation bouton arrêter

    SetWidgetPos(test, PLACE_UNDER, NULL, NO_CARE, NULL); // Positionnement bouton tester
    SetWidgetPos(restart, PLACE_RIGHT, test, NO_CARE, NULL); // Positionnement bouton recommencer
    SetWidgetPos(stop, PLACE_RIGHT, restart, NO_CARE, NULL); // Positionnement bouton arrêter

    // Génération de l'espace textuel
    zone_text = MakeTextWidget(NULL, 0, TRUE, 20, 100); // Initialisation zone textuelle
    SetWidgetPos(zone_text, PLACE_UNDER, test, NO_CARE, NULL); // Positionnement de la zone de texte
}

// Rôle : crée une boîte colorée avec la lettre à l'intérieur
void create_color_box(char l, int color)
{
    Widget box;
    box = MakeDrawArea(100, 100, RedrawColorBox, &color); // Boîte colorée
    SetWidgetPos(box, PLACE_UNDER, NULL, NO_CARE, NULL);
    char letter[2] = {l, '\0'};
    DrawText(box, letter, 1, 50, 50); // Insertion de la lettre dans la case
}

// Rôle : génère les boîtes en fonction du résultat du test du mot que l'utilisateur a entré
void GenereBoxDisp(char result[], int pos_x, int pos_y)
{
    for (int i = 0; i < strlen(result); i++) {
        switch (result[i]) {
            case 'O': // Lettre bien placée
                create_color_box(result[i], GetRGBColor(255, 165, 0)); // Orange
                break;
            case 'B': // Lettre présente mais mal placée
                create_color_box(result[i], GetRGBColor(0, 0, 255)); // Bleu
                break;
            case 'R': // Lettre absente
                create_color_box(result[i], GetRGBColor(255, 0, 0)); // Rouge
                break;
        }
    }
}
