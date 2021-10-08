/*!
 * \file liste.c
 * \brief File containing all the function used on list.
 * \author Payard - Laurencot
 * \version pré-alpha
 * \date 8 Octobre 2021
 */
#include "liste.h"

/**
 * \fn Liste creerListe()
 * \brief Function that create a list.
 * 
 * 
 * \return l - l is a properly initialized list
 */
Liste creerListe(){
  Liste l;
  l.first = NULL;
  return l;
}

/**
 * \fn void detruireListe(Liste l)
 * \brief Function that free all the part of a list.
 * This function is very useful to avoid all memory leak while playing with
 * list. After the use of this function, you can reuse or let the pointer on a
 * list you sent here.
 * \param l - l is the list we work on 
 * \return void
 */
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

/**
 * \fn void ajouteDebut(Liste *l, void *n)
 * \brief Function that put a value as the first value of the list
 * \param l - l is the list we work on
 * \param n - the value we want to add to the list
 * \return void
 */
void ajouteDebut(Liste *l, void *n){
  Maillon *M = (Maillon *)malloc(sizeof(Maillon));
  M->val = n;
  M->suiv = l->first;
  l->first = M;
}

/**
 * \fn void ajouteFin(Liste *l, void *n)
 * \brief Function that put a value as the last value of the list
 *
 * \param l - l is the list we work on
 * \param n - the value we want to add to the list
 * \return void
 */
void ajouteFin(Liste *l, void *n){
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

/**
 * \fn void afficheListe(Liste l)
 * \brief Function that print every element on the terminal.
 * This function is mostly useful in debugging.
 * \param l - l is the list we work on 
 * \return void
 */
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
/**
 * \fn int ListLenght(Liste l)
 * \brief Function that get the size of a list.
 * Warning : This function as to read every element of the list, for big list it
 * can be pretty slow.
 * \param l - l is the list we work on 
 * \return result - result is the list length
 */
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

/**
 * \fn void supprDebut(Liste *l)
 * \brief Function that remove the first element of the list if there is one.
 *
 *
 * \param *l - l is the pointer of the list we work on 
 * \return void - l is a pointer, no need to return it
 */
void supprDebut(Liste *l){
  Maillon *new;
  if(l->first != NULL){
    new = l->first;
    l->first = new->suiv;
    free(new);
  }
}

/**
 * \fn void supprFin(Liste *l)
 * \brief Function that remove the last element of the list if there is one.
 *
 *
 * \param *l - l is the pointer of the list we work on 
 * \return void - l is a pointer, no need to return it
 */
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

/**
 * \fn void supprValeur(Liste *l, void *val)
 * \brief Function that remove one element of the list if there is one with the
 * same value as the one passed in parameter.
 *
 * \param val - val is the value we want to destroy in the list
 * \param *l - l is the pointer of the list we work on 
 * \return void - l is a pointer, no need to return it
 */
void supprValeur(Liste *l, void *val){
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

/**
 * \fn void supprMaillon(Liste *l, int nbMaillon)
 * \brief Function that remove the element of the list if there is one that as a
 * number equal to nbMaillon, with value 0 for the first.
 *
 *
 * \param *l - l is the pointer of the list we work on
 * \param nbMaillon - nbMaillon is the number of the maillon we want to destroy
 * \return void - l is a pointer, no need to return it
 */
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
