#include <libsx.h>
#include <stdio.h>
#include <stdbool.h>
#include "callback.h"
#include "data.h"

extern Widget zone_text; // Déclaration de la zone de texte externe

// Variables globales
Mot motMystere;
int essais;
const int MAX_ESSAIS = 6;
char etat[51]; // Assuming the maximum word size is 50 + 1 for '\0'

// Rôle : est appelée quand le joueur appuie sur le bouton tester
void test_callback(Widget w, void *data)
{
    char motPropose[51]; // Assuming the maximum word size is 50 + 1 for '\0'
    static bool initialised = false;
    bool valid_input = true;

    // Initialiser le jeu si ce n'est pas déjà fait
    if (!initialised) {
        motMystere = initMot();
        essais = 0;
        etat[motMystere.size] = '\0';
        initialised = true;
        printf("Nouveau mot à deviner : %s\n", motMystere.mot); // Debugging purpose
    }

    // Récupérer le texte saisi par l'utilisateur
    GetText(zone_text, motPropose, sizeof(motPropose) - 1);
    motPropose[sizeof(motPropose) - 1] = '\0'; // Assurer la terminaison de la chaîne

    // Vérifier la validité du mot proposé
    if (!longueurMot(motPropose, motMystere.mot)) {
        printf("Le mot proposé n'est pas de la bonne longueur.\n");
        valid_input = false;
    }

    if (valid_input && !motExistant(motPropose)) {
        printf("Le mot proposé n'est pas dans le dictionnaire.\n");
        valid_input = false;
    }

    if (valid_input) {
        if (verifMot(motPropose, motMystere.mot, etat)) {
            printf("Félicitations ! Vous avez trouvé le mot : %s\n", motMystere.mot);
            initialised = false; // Reset for a new game
        } else {
            affichageMot(motPropose, etat);
            GenereBoxDisp(etat, 0, 0); // Exemple de positionnement (à adapter)
            essais++;
            if (essais >= MAX_ESSAIS) {
                printf("Malheureusement, vous n'avez pas trouvé le mot. Le mot était %s.\n", motMystere.mot);
                initialised = false; // Reset for a new game
            }
        }
    }

    // Réinitialiser la zone de texte pour la prochaine entrée
    SetText(zone_text, "");
}

// Rôle : est appelée quand le joueur appuie sur le bouton recommencer
void restart_callback(Widget w, void *data)
{
    printf("Partie recommencée!\n");

    // Réinitialiser le jeu
    motMystere = initMot();
    essais = 0;
    etat[motMystere.size] = '\0';

    // Effacer le texte de la zone de texte
    SetText(zone_text, "");

    // Réinitialiser l'affichage (si nécessaire)
    printf("Nouveau mot à deviner : %s\n", motMystere.mot); // Debugging purpose
}

// Rôle : est appelée quand le joueur appuie sur le bouton arrêter
void stop_callback(Widget w, void *data)
{
    printf("Partie arrêtée!\n");

    // Fermer l'application (ou retourner à un menu principal, selon votre design)
    exit(0); // Ou une autre action selon votre logique
}
