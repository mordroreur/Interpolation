/*!
 * \file main.c
 * \brief Fichier principale de notre programme d'interpolation
 * \author Payard - Laurencot
 * \version pré-alpha
 * \date 8 Octobre 2021
 *
 *
 */

/*!
  \mainpage Programme d'interpolation
  \section Introduction
  \subsection sous-titre
  Je ne sais pas encore ce que fais ce programme...
  \n Donc je peu pas vous dire...
 */
#include "main.h"

/**
 * \fn int main ()
 * \brief Fonction principale du programme
 * 
 * 
 * \return 0 - Ce qui termine le programme
 */
int main()
{
  int x; /**< Description de x. */
  polynome *p1 = creePolynomedemande();
  polynome *p2 = creePolynomedemande();
  polynome *poly = multPolynome(p1, p2);
  affichepolynome(poly);
  return 0;
}
