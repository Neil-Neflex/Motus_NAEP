#include "motus.h"

// Déclaration de fonctions
void envoyer_message_erreur(SystemMotus *systeme, const char *msg);
void dessiner_resultat(SystemMotus *systeme, int indice_essai);
void reveler_premiere_lettre(SystemMotus *systeme);
void afficher_progression(SystemMotus *systeme);
void valider_saisie(Widget widget, char *texte, void *param);
void reinitialiser_action(Widget widget, void *param);

void fermer_application(Widget widget, void *param) {
    // Assurer que les paramètres ne causent pas d'avertissements de compilation
    if (widget != NULL || param != NULL) {
        // Quitter le programme après avoir effectué des nettoyages nécessaires
        exit(0);
    }
}


void gestionnaire_info(Widget w, void *d) {
    // Assurer que les paramètres ne causent pas d'avertissements de compilation
    (void)w;
    (void)d;

    // Afficher un message informatif à propos du jeu
    printf("Bienvenue dans notre jeu de devinettes !\n");
    printf("Vous devez trouver le mot secret en proposant des mots.\n");
    printf("Chaque proposition doit être de la même longueur que le mot secret.\n");
    printf("Les lettres correctes et bien placées sont indiquées par des couleurs spéciales.\n");
    printf("Vous disposez d'un nombre limité d'essais pour trouver le mot.\n");
    printf("Amusez-vous bien et bonne chance !\n");
}


void redimensionner_apparence(Widget w, int largeur, int hauteur, void *data) {
    // Ignorer les paramètres pour éviter les avertissements
    (void)w;
    (void)largeur;
    (void)hauteur;

    // Sécurité : vérifier si les données sont valides
    if (data == NULL) {
        return;
    }

    // Convertir les données en un système de jeu
    SystemMotus *systeme = (SystemMotus *)data;

    // Réinitialiser l'affichage en effaçant la zone de dessin
    EffacerZoneDessin();

    // Révéler la première lettre du mot secret
    reveler_premiere_lettre(systeme);

    // Afficher les résultats de chaque essai
    for (int i = 0; i < systeme->nb_essais; i++) {
        afficher_resultat(systeme, i);
    }

    // Afficher la progression actuelle du jeu
    afficher_progression(systeme);
}

void indiquer_erreur_jeu(SystemeJeu *systeme, const char *msg) {
    // Vérifier si le système de jeu est valide
    if (systeme == NULL || msg == NULL) {
        return;
    }

    // Afficher le message d'erreur sur la console
    fprintf(stderr, "Erreur : %s\n", msg);
}


void initialiser_jeu(SystemeJeu *systeme, const char *mot_secret) {
    // Vérifier si le système de jeu et le mot secret sont valides
    if (systeme == NULL || mot_secret == NULL) {
        return;
    }

    // Réinitialiser les données du système de jeu
    memset(systeme->mot_secret, 0, MAX_TAILLE_MOT + 1);
    strcpy(systeme->mot_secret, mot_secret);
    systeme->nb_essais = 0;
}


int faire_tentative(SystemeJeu *systeme, const char *tentative) {
    // Vérifier si le système de jeu et la tentative sont valides
    if (systeme == NULL || tentative == NULL) {
        return 0;
    }

    // Vérifier si la longueur de la tentative correspond à celle du mot secret
    if (strlen(tentative) != strlen(systeme->mot_secret)) {
        printf("Votre tentative doit contenir %lu lettres.\n", strlen(systeme->mot_secret));
        return 0;
    }

    // Enregistrer la tentative dans le système de jeu
    if (systeme->nb_tentatives < MAX_TENTATIVES) {
        strcpy(systeme->tentatives[systeme->nb_tentatives++], tentative);
        return 1;
    } else {
        printf("Nombre maximum de tentatives atteint.\n");
        return 0;
    }
}

int est_mot_valide(const char *mot) {
    // Vérifier si le mot est valide en le comparant à une liste en mémoire
    const char *liste_mots[] = {"chat", "chien", "maison", "voiture", "banane"};
    const int nb_mots = sizeof(liste_mots) / sizeof(liste_mots[0]);

    for (int i = 0; i < nb_mots; i++) {
        if (strcmp(liste_mots[i], mot) == 0) {
            return 1;
        }
    }

    return 0;
}

char* choisir_mot_aleatoire() {
    // Liste de mots valides prédéfinis
    const char *mots_valides[] = {"chat", "chien", "maison", "voiture", "banane"};
    const int nb_mots_valides = sizeof(mots_valides) / sizeof(mots_valides[0]);

    // Générer un index aléatoire pour choisir un mot parmi les mots valides
    srand(time(NULL));
    int index_aleatoire = rand() % nb_mots_valides;

    // Allouer de la mémoire pour le mot sélectionné
    char *mot_selectionne = (char *)malloc((strlen(mots_valides[index_aleatoire]) + 1) * sizeof(char));
    if (mot_selectionne == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire.\n");
        exit(EXIT_FAILURE);
    }

    // Copier le mot sélectionné dans la mémoire allouée
    strcpy(mot_selectionne, mots_valides[index_aleatoire]);

    // Retourner le mot sélectionné
    return mot_selectionne;
}


void dessiner_retour(SystemeJeu *systeme, int indice_essai) {
    // Tableau des couleurs pour les retours
    const char *couleurs_retours[] = {"rouge", "orange", "bleu"};

    // Tableau pour stocker les retours générés
    char retours[MAX_TAILLE_MOT + 1] = {0};

    // Compter les occurrences de chaque lettre du mot secret
    int compte_lettres[256] = {0};
    for (size_t j = 0; j < strlen(systeme->mot_secret); j++) {
        compte_lettres[(unsigned char)systeme->mot_secret[j]]++;
    }

    // Vérifier les lettres correctes à la bonne place
    for (size_t j = 0; j < strlen(systeme->mot_secret); j++) {
        if (systeme->tentatives[indice_essai][j] == systeme->mot_secret[j]) {
            retours[j] = 'x';
            compte_lettres[(unsigned char)systeme->mot_secret[j]]--;
        }
    }

    // Vérifier les lettres correctes à la mauvaise place
    for (size_t j = 0; j < strlen(systeme->mot_secret); j++) {
        if (retours[j] != 'x') {
            if (strchr(systeme->mot_secret, systeme->tentatives[indice_essai][j]) &&
                compte_lettres[(unsigned char)systeme->tentatives[indice_essai][j]] > 0) {
                retours[j] = 'o';
                compte_lettres[(unsigned char)systeme->tentatives[indice_essai][j]]--;
            } else {
                retours[j] = '-';
            }
        }
    }

    // Taille des carreaux
    int taille_carreaux = 40;

    // Dessiner les retours sur la zone de dessin
    for (size_t j = 0; j < strlen(systeme->mot_secret); j++) {
        // Choisir la couleur en fonction du retour
        const char *couleur = couleurs_retours[retours[j] == 'x' ? 0 : (retours[j] == 'o' ? 1 : 2)];
        
        // Dessiner un carré rempli avec la couleur correspondante
        RemplirRectangle(j * taille_carreaux, indice_essai * (taille_carreaux + 10), taille_carreaux, taille_carreaux, couleur);
        
        // Dessiner la lettre de la tentative
        char lettre[2] = {systeme->tentatives[indice_essai][j], '\0'};
        int position_x_texte = j * taille_carreaux + (taille_carreaux / 2) - 5;
        int position_y_texte = indice_essai * (taille_carreaux + 10) + (taille_carreaux / 2) + 5;
        DessinerTexte(lettre, position_x_texte, position_y_texte);
    }
}


void afficher_etat(SystemeJeu *systeme) {
    // Construire une chaîne de caractères décrivant l'état du jeu
    char etat[100];
    sprintf(etat, "Longueur du mot: %lu, Essais restants: %d", strlen(systeme->mot_secret), MAX_TENTATIVES - systeme->nb_tentatives);
    
    // Dessiner le texte décrivant l'état du jeu sur la zone de dessin
    DessinerTexte(etat, 10, 350);
}


void afficher_premiere_lettre(SystemeJeu *systeme) {
    // Choisir la couleur pour la première lettre
    const char *couleur = "rouge";

    // Taille des carreaux
    int taille_carreaux = 40;

    // Dessiner un carré rempli avec la couleur choisie
    RemplirRectangle(0, 0, taille_carreaux, taille_carreaux, couleur);
    
    // Dessiner la première lettre du mot secret
    char lettre[2] = {systeme->mot_secret[0], '\0'};
    int position_x_texte = (taille_carreaux / 2) - 5;
    int position_y_texte = (taille_carreaux / 2) + 5;
    DessinerTexte(lettre, position_x_texte, position_y_texte);
}


void soumettre_tentative(Widget w, char *saisie, void *donnees) {
    // Ignorer le widget pour éviter les avertissements de paramètre non utilisé
    (void)w;

    // Conversion des données en structure de jeu
    SystemeJeu *systeme = (SystemeJeu *)donnees;

    // Vérifier si la longueur de la saisie correspond à celle du mot secret
    if (strlen(saisie) != strlen(systeme->mot_secret)) {
        afficher_erreur(systeme, "Votre mot doit contenir %lu lettres.", strlen(systeme->mot_secret));
        return;
    }

    // Vérifier si la saisie est un mot valide
    if (!est_mot_valide(saisie)) {
        afficher_erreur(systeme, "Mot invalide");
        return;
    }

    // Enregistrer la tentative et mettre à jour l'affichage
    if (faire_tentative(systeme, saisie)) {
        EffacerZoneDessin();  // Effacer la zone de dessin
        afficher_premiere_lettre(systeme);  // Réafficher la première lettre
        for (int i = 0; i < systeme->nb_tentatives; i++) {
            dessiner_retour(systeme, i);
        }
        afficher_etat(systeme);
        afficher_erreur(systeme, "");  // Effacer le message d'erreur en cas de tentative valide
    }

    // Vérifier si le mot a été trouvé ou si le nombre maximum de tentatives a été atteint
    if (strcmp(saisie, systeme->mot_secret) == 0) {
        AfficherPopup("Bravo !!!");
        exit(0);
    } else if (systeme->nb_tentatives >= MAX_TENTATIVES) {
        AfficherPopup("Désolé, vous avez perdu.");
        exit(0);
    }
}


void reinitialiser_jeu(Widget w, void *donnees) {
    // Ignorer le widget pour éviter les avertissements de paramètre non utilisé
    (void)w;

    // Conversion des données en structure de jeu
    SystemeJeu *systeme = (SystemeJeu *)donnees;

    // Choisir un nouveau mot aléatoire
    char *nouveau_mot = choisir_mot_aleatoire();

    // Réinitialiser le jeu avec le nouveau mot
    initialiser_jeu(systeme, nouveau_mot);

    // Effacer la zone de dessin et réafficher la première lettre
    EffacerZoneDessin();
    afficher_premiere_lettre(systeme);

    // Afficher l'état du jeu et effacer le message d'erreur
    afficher_etat(systeme);
    afficher_erreur(systeme, "");
}

void initialiser_interface(int argc, char **argv, SystemeJeu *systeme) {
    // Ignorer les arguments argc et argv pour éviter les avertissements de paramètre non utilisé
    (void)argc;
    (void)argv;

    // Ouvrir la fenêtre d'affichage
    OuvrirFenetre();

    // Créer les widgets
    Widget bouton_quitter = CreerBouton("Quitter", action_terminer, NULL);
    Widget bouton_aide = CreerBouton("Aide", aide_action, (void *)systeme); // Associer la fonction de rappel Aide
    Widget zone_saisie = CreerZoneTexte(NULL, 200, soumettre_tentative, (void *)systeme);
    Widget bouton_reinitialiser = CreerBouton("Réinitialiser", reinitialiser_jeu, (void *)systeme); // Associer la fonction de rappel Réinitialiser
    systeme->zone_dessin = CreerZoneDessin(400, 400, redimensionner_action, (void *)systeme); // Ajouter une fonction de rappel de redimensionnement
    systeme->message_erreur = CreerWidgetTexte("", 400, 30, FALSE, FALSE); // Initialisation du widget pour les messages d'erreur

    // Positionner les widgets
    PositionnerWidget(bouton_quitter, DROITE, zone_saisie, AUCUN, NULL);      // Positionnement du bouton Quitter
    PositionnerWidget(bouton_aide, DROITE, bouton_quitter, AUCUN, NULL);      // Positionnement du bouton Aide
    PositionnerWidget(bouton_reinitialiser, DROITE, bouton_aide, AUCUN, NULL); // Positionnement du bouton Réinitialiser
    PositionnerWidget(systeme->zone_dessin, SOUS, zone_saisie, AUCUN, NULL);
    PositionnerWidget(systeme->message_erreur, SOUS, systeme->zone_dessin, AUCUN, NULL);

    // Afficher la fenêtre
    AfficherFenetre();

    // Afficher la première lettre dès le début
    afficher_premiere_lettre(systeme);

    // Afficher l'état du jeu
    afficher_etat(systeme);

    // Entrer dans la boucle principale
    MainLoop();
}

int main(int argc, char **argv) {
    // Initialiser le système de jeu
    SystemeJeu systeme;
    char *mot_secret = choisir_mot_aleatoire();
    initialiser_jeu(&systeme, mot_secret);

    // Initialiser l'interface utilisateur
    initialiser_interface(argc, argv, &systeme);

    return 0;
}
