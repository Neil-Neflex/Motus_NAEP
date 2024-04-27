/**
 * Ce programme est un jeu de réflexion basé sur les connaissances de la langue française
 * qu'a le joueur. Le programmme présente la première lettre d'un mot au joueur et ce 
 * dernier a 6 essaies pour trouver le mot. Pour l'aider le programme indique au joueur 
 * si les lettres du mot entré sont bien positionnées ou non
 *
 * @authors N. Amrane & E. Patijunas     neil.amrane@etu.univ-cotedazur.fr  
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "dico.h"
#include "mot.h"


//retourne un nouveau mot après l'avoir créé
Mot initMot(){
    Mot res;                            //définition d'un nouveau mot
    char *p = malloc(sizeof(Mot));      //allocation d'un espace mémoire p
    choixMot(p);                        //appel de la fct° choixmot param : p
    res.mot = p;                        //asso° du mot aléatoire au nouveau mot
    res.size = strlen(res.mot);         // asso° au nveau mot taille mot aléatoire
    return res;
}
//retourne le teste d'égalité entre taille de la chaine de char en param
//et la const int en param
int longeurMot(Mot p, const int t){
    return (strlen(p.size) == t);            
}

int presence(Mot p, const char c){
    for (int i = 0; i<p.size-1; i++){

    }
}


