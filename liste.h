#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct Maillon{
  struct Maillon *suiv;
  int val;
}Maillon;


typedef struct Liste{
  struct Maillon *first;
}Liste;


Liste creerListe();
void detruireListe(Liste l);
void ajouteDebut(Liste *l, int n);
void ajouteFin(Liste *l, int n);
void afficheListe(Liste l);
int ListLenght(Liste l);
void supprDebut(Liste *l);
void supprFin(Liste *l);
void supprValeur(Liste *l, int val);
void supprMaillon(Liste *l, int nbMaillon);


#endif
