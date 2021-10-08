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

  polynome *p1 = creePolynomedemande();
  polynome *p2 = creePolynomedemande();
  polynome *poly = multPolynome(p1, p2);
  affichepolynome(poly);

  Liste l = creerListe();

  point p;
  p.x = 0;
  p.y = 0;
  point k;
  k.x = 2;
  k.y = 4;
  point e;
  e.x = 4;
  e.y = 0;
  point m;
  m.x = 6;
  m.y = 4;
  ajouteDebut(&l, p);
  ajouteDebut(&l, k);
  ajouteDebut(&l, e);
  ajouteDebut(&l, m);

  float **points;

  points = ListeToTabsPoints(l);

  for (int i = 0; i < 4; i++)
  {
    printf("point : %f, %f\n", points[0][i], points[1][i]);
  }

  /* polynome *fonction = calculLagrange(l); */
  /* affichepolynome(fonction); */

  //  int x; /**< Description de x. */

  return 0;
}
