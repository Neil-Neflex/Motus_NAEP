#pragma once

//Rôle : récupére une liste d'entiers et réalise l'affichage pour le joueur
extern void affichache(const int[], const char[]);
//Rôle : gestoin de la  partie
extern void Partie();
//Rôle : vérifie l'état de la partie et la stop si besoin
extern int finPartie(int,const int[]);
