#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>




typedef struct {
    int size;
    char *mot;
}Mot;

FILE* dico = NULL; //Ce pointeur de fichier contiendra notre dictionnaire
int NBMOTS = 0;
const char PATH[] =  "../ressources/DicoMotus"; //chemin vers le dictionnaire


/**
 *
 * Rôle : Cette fonction gère l'ouverture et la lecture du dictionnaire de mots. Elle compte également le nombre total de mots dans le dictionnaire.
 * Conséquents : Renvoie 1 si le dictionnaire a été ouvert et lu correctement, sinon 0 en cas d'erreur.
 */
int Gestion(void){
    int cLu;
    dico = fopen("C:/Users/edvin/CLionProjects/ProjetMotus/DicoMotus", "r"); //on ouvre dico.txt en lecture seule
    //On test si le dictionnaire s'est bien ouvert
    if (dico == NULL){
        printf("Ouverture du dictionnaire impossible\n");
        return 0; //on retourne 0 s'il y a une erreur
    }

    printf("Initialisation du fichier achevée\n");
    //On parcours le dictionnaire pour compter le nombre de mots
    do{
        cLu = fgetc(dico);          //cLu parcours tous les caractères du fichier
        if (cLu == '\n') NBMOTS++;  //il y a un mot par ligne, on compte donc les "\n"
    }while(cLu != EOF);         //on boucle tant que l'on ne rencontre pas l'EOF du fichier
    return 1;
}

/**
 * Antécédents : Un entier nbMax qui est la borne supérieure pour la génération de nombres aléatoires.
 * Rôle : Cette fonction génère et renvoie un nombre aléatoire entre 0 et nbMax.
 * Conséquents : Renvoie un nombre aléatoire entre 0 et nbMax.
 */
int aleatoire(int nbMax){
    srand(time(NULL));      //initialisation du générateur pseudo-aléatioire sur l'horloge de l'ordinateur
    return (rand() % nbMax);     //retour d'une valeur comprise entre 0 et nbMax
}

/**
 * Antécédents : Un pointeur adress vers une chaîne de caractères où le mot choisi doit être stocké.
 * Rôle : Cette fonction choisit un mot aléatoire du dictionnaire et le stocke à l'adresse pointée par adress.
 * Conséquents : Renvoie 1 pour confirmer la fin et la bonne exécution du programme. Le mot choisi est stocké à l'adresse pointée par adress.
 * Retourne 0 en cas d'erreur lors de la lecture du dictionnaire ou du choix du mot.
 */
int choixMot(char *adress){
    int cLu;
    int numMot; //numMot contiendra la ligne du mot choisi aléatoirement
    //Si le dictionnaire n'a pas encore été chargé, choixMot fait un appel à Gestion
    if (dico == NULL){
        if(!(Gestion())){
            //si dico est toujour NULL, une erreur persiste et le programme doit s'arrêter
            printf("fatal error dico § impossible de choisir un mot\n");
            return 0;
        }}
    numMot = aleatoire(NBMOTS); //appel à la fonction aléatoire

    rewind(dico);               //retour au début du dictionnaire

    //on parcourt une nouvelle fois le dictionnaire pour s'arrêter à la ligne choisie
    while(numMot>0){
        cLu = fgetc(dico);
        if (cLu == '\n') numMot--;
    }
    fgets(adress, 50, dico); //appel à la procédure fgets pour lire la ligne choisie
                            //le mot lu est stocker à l'adresse du pointeur

    adress[strlen(adress)-1] = '\0'; //on retire le caractère '\0' et on le remplace par '\0'

    fclose(dico); //on referme le dictionnaire
    return 1; // on retourne 1 pour confirmer la fin et bonne exécution du programme
}

bool motExistant(const char *mot) {
    FILE *dictionnaire = fopen("C:/Users/edvin/CLionProjects/ProjetMotus/DicoMotus", "r");
    char motDico[35];
    bool existant = false;

    if(dictionnaire == NULL){
        perror("Erreur d'ouverture du fichier");
        return false;
    }

    while (fgets(motDico, sizeof(motDico), dictionnaire) != NULL) {
        size_t longueur = strlen(motDico);
        if (longueur > 0 && motDico[longueur - 1] == '\n') {
            motDico[longueur - 1] = '\0';
        }

        if (strcmp(motDico, mot) == 0) {
            existant = true;
            break;
        }
    }

    fclose(dictionnaire);
    return existant;
}


/**
 * Rôle : Initialise un nouveau mot
 * Conséquent : Renvoie une structure Mot initialisée avec un mot aléatoire et sa taille
 */
Mot initMot(){
    Mot res;
    char *p = malloc(sizeof(char) * 10);
    choixMot(p);
    res.mot = p;
    res.size = strlen(res.mot);
    return res;
}


/**
 * Antécédents : Deux chaînes de caractères, motPropose et motMystere.
 * Rôle : Compare la longueur de deux chaînes de caractères.
 * Conséquent : Renvoie true si les deux chaînes ont la même longueur, false sinon.
 */
 bool longueurMot(char *motPropose, char *motMystere) {
    if (strlen(motPropose) == strlen(motMystere)) {
        return true;
    }
    return false;
}


/**
 * Antécédents : Le mot proposé, le mot à deviner, et l'état actuel de la chaîne.
 * Rôle : Détermine la position de chaque lettre dans les mots proposés et à deviner.
 * Conséquents : Ne retourne rien mais modifie la chaîne d'état; marque les lettres comme correctement placées ('x'), mal placées ('o'), ou non présentes ('-').
 */
void position(char *motPropose, const char *motADeviner, char *etat) {
    int i, j;
    int taille = strlen(motPropose);

    for(i = 0; i < taille; i++) {
        etat[i] = '-'; // On initialise toutes les valeurs à '-'.
    }

    for(i = 0; i < taille; i++) {
        for(j = 0; j < taille; j++){
            // On vérifie d'abord si la lettre est dans la bonne position.
            if(i == j && motPropose[i] == motADeviner[j]) {
                etat[i] = 'x';
            }
            // On vérifie ensuite si la lettre est ailleurs dans le mot.
            else if(motPropose[i] == motADeviner[j]) {
                // On ne modifie la valeur que si elle n'est pas déjà marquée comme correctement positionnée.
                if(etat[i] != 'x') {
                    etat[i] = 'o';
                }
            }
        }
    }
}


/**
 * Antécédents : Le mot proposé, le mot à deviner, et l'état actuel de la chaîne.
 * Rôle : Vérifie si le mot proposé est égal au mot à deviner.
 * Conséquents : Renvoie 1 si le mot proposé est correct, 0 sinon.
 */
int verifMot(char *motPropose, const char *motADeviner, char *etat){

    if(strlen(motPropose) != strlen(motADeviner)) {
        return 0; //la longueur du mot à deviner n'est pas la même que celle du mot proposé donc erreur
    }

    position(motPropose, motADeviner, etat);

    for (int i=0; i <strlen(motPropose); i++) {
        if (etat[i] != 'x') {
            return 0;
        }
    }
    return 1;
}

/**
 * Antécédents : Le mot à deviner et l'état actuel.
 * Rôle : Affiche l'état actuel du mot à deviner.
 * Conséquents : Ne retourne rien mais affiche l'état du mot.
 */
void affichageMot(const char* mot, const char* etat) {
    int taille = strlen(mot);

    for (int i = 0; i < taille; i++) {
        switch(etat[i]) {
            case 'x':    // La lettre est bien placée
                printf("%c", mot[i]);
                break;
            case 'o':    // La lettre est présente dans le mot, mais mal placée
                printf("o");
                break;
            default:    // La lettre n'est pas dans le mot
                printf("-");
                break;
        }
    }

    printf("\n");  // Ajoute une nouvelle ligne à la fin pour une séparation entre les tentatives
}

/**
 * Antécédents : Le mot à deviner et l'état actuel.
 * Rôle : Affiche l'état actuel du mot à deviner.
 */
int finPartie(int t, int p[]) {
    if (p == NULL || t <= 0) {
        printf("Erreur : paramètres invalides.\n");
        return -1; // on retourne -1 en cas d'erreur
    }

    for (int i = 0; i < t; i++) {
        if (p[i] != 1)
            return 0; // le jeu continue
    }

    printf("Félicitations ! Vous avez contré Motus\n");
    return 1; // le joueur a gagné
}


/**
 * Rôle : Cette fonction démarre et gère une partie du jeu Motus.
 */
void Partie() {
    const int TAILLE_MAX_MOT = 50;
    const int MAX_ESSAIS = 6;
    char motPropose[TAILLE_MAX_MOT + 1];
    char etat[TAILLE_MAX_MOT + 1];
    int essais = 0;
    int gagne = 0;
    bool conditionAffichage = false;

    Mot motMystere = initMot();
    printf(" %s\n", motMystere.mot);
    etat[motMystere.size] = '\0';

    printf("Bienvenue dans le jeu Motus !\n");
    printf("Devinez le mot lettre par lettre. Le mot est de longueur %lu\n", strlen(motMystere.mot));

    while(essais < MAX_ESSAIS && gagne == 0) {
        printf("\nEntrez votre proposition : ");
        fgets(motPropose,TAILLE_MAX_MOT , stdin);


        // Supprimer le caractère de nouvelle ligne à la fin si présent
        motPropose[strcspn(motPropose, "\n")] = 0;

        gagne = verifMot(motPropose, motMystere.mot, etat);

        if (!longueurMot(motPropose, motMystere.mot) && gagne != 1) {
            printf("\nLe mot proposé n'est pas de la bonne longueur. Essayez à nouveau.\n");
            conditionAffichage = true;
        }
        fflush(stdin);

        if (!motExistant(motPropose)) {
            printf("\nLe mot proposé n'est pas dans le dictionnaire. Essayez à nouveau.\n");
            conditionAffichage = true;
        }

        if (!conditionAffichage) {
            affichageMot(motPropose,etat);
        }
        conditionAffichage = false;
        essais++;
    }

    if(gagne == 1) {
        printf("\nFélicitations ! Vous avez trouvé le mot %s.\n", motMystere.mot);
    } else {
        printf("\nMalheureusement, vous n'avez pas trouvé le mot. Le mot était %s.\n", motMystere.mot);
    }

    free(motMystere.mot);
}

int main(void) {
    Partie();    // Démarrer le jeu
    return 0;    // Retourner 0 si le programme se termine normalement
}
