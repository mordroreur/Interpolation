#include "liste.h"
#include <stdlib.h>

Liste creerListe(){
  Liste l;
  l.first = NULL;
  return l;
}

void detruireListe(Liste l){
  Maillon *old;
  Maillon *new;
  
  new = l.first;
  while (new != NULL) {
    old = new;
    new = new->suiv;
    free(old);
  }
}

void ajouteDebut(Liste *l, int n){
  Maillon *M = (Maillon *)malloc(sizeof(Maillon));
  M->val = n;
  M->suiv = l->first;
  l->first = M;
}

void ajouteFin(Liste *l, int n){
  Maillon *M = (Maillon *)malloc(sizeof(Maillon));
  Maillon *new;

  M->val = n;
  M->suiv = NULL;
  if(l->first == NULL){
    l->first = M;
  }else{
    new = l->first;
    while (new->suiv != NULL) {
      new = new->suiv;
    }
    new->suiv = M;
  }
}

void afficheListe(Liste l){
  Maillon *new;
  
  new = l.first;
  if(new == NULL){
    printf("La suite est vide.\n");
  }else{
    printf("La suite vaut : %d", new->val);
    new = new->suiv;
    while(new != NULL) {
      printf(", %d", new->val);
      new = new->suiv;
    }
    printf("\n");
  }
}

int ListLenght(Liste l){
  Maillon *new;
  int result = 0;
  

  if(l.first != NULL){
    new = l.first;
    while (new != NULL) {
      new = new->suiv;
      result++;
    }
  }
  return result;
}


void supprDebut(Liste *l){
  Maillon *new;
  if(l->first != NULL){
    new = l->first;
    l->first = new->suiv;
    free(new);
  }
}

void supprFin(Liste *l){
  Maillon *new;
  if(l->first != NULL){
    new = l->first;
    while (new->suiv != NULL) {
      new = new->suiv;
    }
    free(new->suiv);
    new->suiv = NULL;
  }
}

void supprValeur(Liste *l, int val){
  Maillon *new;
  Maillon *old;
  if(l->first != NULL){
    if(l->first->val == val){
      supprDebut(l);
    }else{
      new = l->first;
      while ((new->suiv != NULL) && (new->suiv->val != val)) {
	new = new->suiv;
      }
      if(new->suiv != NULL){
	old = new->suiv->suiv;
	free(new->suiv);
	new->suiv = old;
      }
    }
  }
}

void supprMaillon(Liste *l, int nbMaillon){
  Maillon *new;
  Maillon *old;

  if(nbMaillon == 0){
    supprDebut(l);
  }else{
    new = l->first;
    for(int i = 0; i < nbMaillon-1; i++){
      new = new->suiv;
      if(new == NULL){
	break;
      }
    }
    if(new != NULL){
      old = new->suiv->suiv;
      free(new->suiv);
      new->suiv = old;
    }
  }
}
