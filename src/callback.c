#include <libsx.h>
#include <stdlib.h>
#include <string.h>
#include "callback.h"

void quit_cb(Widget w, void *data) {
    exit(0);
}

void help_cb(Widget w, void *data) {
    // Afficher une fenêtre d'aide
}

void reset_cb(Widget w, void *data) {
    // Réinitialiser le jeu
}

void submit_cb(Widget w, void *data) {
    char *input = GetStringEntry((Widget)data);
    // Vérifier le mot saisi et mettre à jour l'affichage du jeu
}
