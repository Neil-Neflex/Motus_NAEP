#ifndef MOTUS_H
#define MOTUS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "libsx.h"

#define MAX_TAILLE_MOT 50
#define MAX_TENTATIVES 6
#define FICHIER_DICTIONNAIRE "dictionnaire.txt"

typedef struct {
    char mot_secret[MAX_TAILLE_MOT + 1];
    char tentatives[MAX_TENTATIVES][MAX_TAILLE_MOT + 1];
    int nb_tentatives;
    Widget zone_dessin;
    Widget message_erreur;
} SystemeJeu;

void initialiser_jeu(SystemeJeu *systeme, char *mot_secret);
char* choisir_mot_aleatoire();
int est_mot_valide(const char *mot);
int faire_tentative(SystemeJeu *systeme, const char *tentative);
void afficher_erreur(SystemeJeu *systeme, const char *format, ...);
void action_terminer(Widget widget, void *param);
void aide_action(Widget widget, void *param);
void soumettre_tentative(Widget w, char *saisie, void *donnees);
void reinitialiser_jeu(Widget w, void *donnees);
void afficher_premiere_lettre(SystemeJeu *systeme);
void dessiner_retour(SystemeJeu *systeme, int indice_essai);
void redimensionner_action(Widget widget, int largeur, int hauteur, void *param);
void initialiser_interface(int argc, char **argv, SystemeJeu *systeme);

#endif /* MOTUS_H */
