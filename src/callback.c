/**
* Ce programme est un jeu de réflexion basé sur les connaissances de la langue française
 * qu'a le joueur. Le programmme présente la première lettre d'un mot au joueur et ce
 * dernier a 6 essaies pour trouver le mot. Pour l'aider le programme indique au joueur
 * si les lettres du mot entré sont bien positionnées ou non
 * 
 * Ce fichier gère les fonctions d'appel de l'interface utilisateur
 *
 * @authors N. Amrane & E. Patijunas     neil.amrane@etu.univ-cotedazur.fr
 */

#include <libsx.h>
#include <stdio.h>
#include "display.h"

//Rôle : est appelée quand le joueur appuie sur le boutton tester
void test_callback(Widget w, void *data)
{
    printf("Button clicked!\n");
    //doit appeler fonction  vérifications
}


//Rôle : est appelée quand le joueur appuie sur le boutton recommencer
void restart(Widget w, void *data)
{
    printf("Button clicked!\n");

    //doit arreter la partie en cours et en relancer une
}

//Rôle : est appelée quand le joueur appuie sur le boutton arreter
void stop(Widget w, void *data)
{
    printf("Button clicked!\n");

    //doit arreter la partie en cours et en relancer une
}
