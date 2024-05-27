/**
 * Ce fichier s'occupe de la gestion des fichiers et de la gestion relative au dictionnaire
 * Il n'intervient qu'au début de l'exécution du programme
 *
 * @authors N. Amrane & E. Patijunas     neil.amrane@etu.univ-cotedazur.fr 
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "dico.h"

FILE* dico = NULL; //Ce pointeur de fichier contiendra notre dictionnaire
int NBMOTS = 0;
const char PATH[] =  "../ressources/DicoMotus"; //chemin vers le dictionnaire


//Cette procédure a pour but l'ouverture et la gestion du dictionnaire
int Gestion(void){
    int cLu;
    dico = fopen("../ressources/DicoMotus", "r"); //on ouvre dico.txt en lecture seule
    //On test si le dictionnaire s'est bien ouvert
    if (dico == NULL){
        printf("Ouverture du dictionnaire impossilbe\n");
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

//cette fonction retourne une valeur pseudo-aléatoire entre à et le paramètre nbMax
int aleatoire(int nbMax){
    srand(time(NULL));      //initialisation du générateur pseudo-aléatioire 
                            //sur l'horloge de l'ordinateur
    return (rand() % nbMax);     //retour d'une valeur comprise entre 0 et nbMax
}

//Cette procédure à pour but le choix du mot dans le ditctionnaire 
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


int main(int argc, char *argv[]){
    Mot motSecret;
    char *p = malloc(sizeof(Mot));
    Gestion();
    choixMot(p);
    printf(p);
}
