#include <stdio.h>
#include <stdlib.h>
#include <libsx.h>
#include <string.h>
#include "data.h"

#define MAX_ROWS 6
#define WORD_LEN 8

Widget input_text;
Widget draw_area;
char motMystere[WORD_LEN];
char etat[WORD_LEN];
int essais = 0;

void create_interface(void);
void quit_callback(Widget w, void *data);
void check_word_callback(Widget w, void *data);
void draw_callback(Widget w, int width, int height, void *data);

int main(int argc, char *argv[])
{
    if (OpenDisplay(argc, argv) == 0) {
        fprintf(stderr, "Can't open display\n");
        return EXIT_FAILURE;
    }

    // Initialisation du mot mystère
    Mot mot = initMot();
    strncpy(motMystere, mot.mot, WORD_LEN);
    free(mot.mot);

    // Crée les widgets et l'interface
    create_interface();

    // Passe le contrôle à la bibliothèque libsx
    MainLoop();

    return EXIT_SUCCESS;
}

void create_interface(void)
{
    SetBgColor("white");

    Widget quit_button = MakeButton("Quit", quit_callback, NULL);
    Widget check_button = MakeButton("Check", check_word_callback, NULL);
    input_text = MakeStringEntry(NULL, 20, NULL, NULL);
    draw_area = MakeDrawArea(400, 300, draw_callback, NULL);

    // Positionnement des boutons et de l'entrée de texte
    SetWidgetPos(check_button, NO_CARE, NULL, NO_CARE, NULL);
    SetWidgetPos(quit_button, PLACE_RIGHT, check_button, NO_CARE, NULL);
    SetWidgetPos(input_text, PLACE_UNDER, check_button, NO_CARE, NULL);
    SetWidgetPos(draw_area, PLACE_UNDER, input_text, NO_CARE, NULL);

    ShowDisplay();
}

void quit_callback(Widget w, void *data)
{
    exit(0);
}

void check_word_callback(Widget w, void *data)
{
    char motPropose[WORD_LEN];
    GetStringEntry(input_text, motPropose, sizeof(motPropose));

    if (!motExistant(motPropose)) {
        printf("Le mot proposé n'est pas dans le dictionnaire. Essayez à nouveau.\n");
        return;
    }

    if (strlen(motPropose) != strlen(motMystere)) {
        printf("Le mot proposé n'est pas de la bonne longueur. Essayez à nouveau.\n");
        return;
    }

    int gagne = verifMot(motPropose, motMystere, etat);
    essais++;

    ClearDrawArea(draw_area);

    if (gagne) {
        printf("Félicitations ! Vous avez trouvé le mot %s.\n", motMystere);
        exit(0);
    } else if (essais >= MAX_ROWS) {
        printf("Malheureusement, vous n'avez pas trouvé le mot. Le mot était %s.\n", motMystere);
        exit(0);
    }

    DrawText(draw_area, 10, essais * 30, motPropose, strlen(motPropose));
}

void draw_callback(Widget w, int width, int height, void *data)
{
    for (int i = 0; i < essais; i++) {
        for (int j = 0; j < WORD_LEN; j++) {
            char c = etat[j];
            switch (c) {
                case 'x':
                    SetColor("red");
                    break;
                case 'o':
                    SetColor("orange");
                    break;
                default:
                    SetColor("blue");
                    break;
            }
            DrawBox(draw_area, j * 30, i * 30, 25, 25);
        }
    }
}
