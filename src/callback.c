#include <stdio.h>
#include <stdlib.h>
#include <libsx.h>
#include "data.h"

#define MAX_ROWS 6
#define MAX_COLS 8
#define WORD_LEN 8

Widget tiles[MAX_ROWS][MAX_COLS];
Widget input_text;
char motMystere[WORD_LEN];
char etat[WORD_LEN];
int essais = 0;

void create_interface(void);
void quit_callback(Widget w, void *data);
void check_word_callback(Widget w, void *data);

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

    Widget button_box = MakeHorizBox(NULL);
    Widget grid_box = MakeVertBox(NULL);

    SetWidgetPos(button_box, PLACE_UNDER, grid_box, NULL);
    SetWidgetPos(quit_button, PLACE_RIGHT, check_button, NULL);
    SetWidgetPos(input_text, PLACE_UNDER, button_box, NULL);

    for (int i = 0; i < MAX_ROWS; i++) {
        Widget row_box = MakeHorizBox(grid_box);
        for (int j = 0; j < WORD_LEN; j++) {
            tiles[i][j] = MakeButton(" ", NULL, NULL);
            SetBgColor(tiles[i][j], "blue");
            SetWidgetPos(tiles[i][j], PLACE_RIGHT, NULL, NULL);
        }
    }

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
    for (int i = 0; i < WORD_LEN; i++) {
        if (etat[i] == 'x') {
            SetBgColor(tiles[essais][i], "orange");
        } else if (etat[i] == 'o') {
            SetBgColor(tiles[essais][i], "blue");
        } else {
            SetBgColor(tiles[essais][i], "red");
        }
        SetLabel(tiles[essais][i], motPropose + i);
    }
    essais++;

    if (gagne) {
        printf("Félicitations ! Vous avez trouvé le mot %s.\n", motMystere);
        exit(0);
    } else if (essais >= MAX_ROWS) {
        printf("Malheureusement, vous n'avez pas trouvé le mot. Le mot était %s.\n", motMystere);
        exit(0);
    }
}
