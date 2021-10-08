/*!
 * \file lagrange.c
 * \brief Fichier contenant la résolution par la méthode de Lagrange.
 * \author Payard
 * \version pré-alpha
 * \date 8 Octobre 2021
 */
#include "lagrange.h"

polynome *calculLi(int nombredepoint, int numero, Liste points)
{
  /* point;  transfore liste en tab*/

  float **pointstab;

  pointstab = ListeToTabsPoints(points);

  int i;
  float resultat;
  polynome *Li = creePolynome(0);
  Li->p[0] = 1;
  polynome *x = creePolynome(1);
  x->p[1] = 1;
  for (i = 0; i < nombredepoint; ++i)
  {
    if (i == numero)
    {
      printf("Test boucle\n");
    }
    else
    {
      Li = multPolynome(Li, x);
      /* multPolynome(susPolynome(x, transformefloatenpoly(pointstab[0][i])), */
      /* transformefloatenpoly( */
      /* 1 / (pointstab[0][numero] - pointstab[0][i])))); */
    }
  }
  return Li;
}

polynome *calculLagrange(Liste points)
{
  int i;
  polynome *fonction = creePolynome(ListLenght(points));
  float **pointstab;
  pointstab = ListeToTabsPoints(points);

  for (i = 0; i < ListLenght(points); ++i)
  {
    fonction = addPolynome(
        fonction, multPolynome(transformefloatenpoly(pointstab[1][i]),
                               calculLi(ListLenght(points), i, points)));
  }
  return fonction;
}
