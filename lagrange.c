/*!
 * \file lagrange.c
 * \brief Fichier contenant la résolution par la méthode de Lagrange.
 * \author Payard
 * \version pré-alpha
 * \date 8 Octobre 2021
 */
#include "lagrange.h"

void affichetab(float **tab, int taille)
{
  int i, j;
  for (i = 0; i < 2; ++i)
  {
    for (j = 0; j < taille; ++j)
    {
      printf("%f  ", tab[i][j]);
    }
    printf("\n");
  };
}

polynome *calculLi(int numero, Liste points)
{
  /* point;  transfore liste en tab*/

  float **pointstab = ListeToTabsPoints(points);

  affichetab(pointstab, ListLenght(points));
  int i;
  float resultat;
  polynome *Li = creePolynome(0);
  Li->p[0] = 1;

  polynome *tp = creePolynome(0);
  tp->p[0] = 1;

  for (i = 0; i < ListLenght(points); ++i)
  {
    if (i == numero)
    {
      printf("Test boucle\n");
    }
    else
    {
      polynome *x = creePolynome(1);
      x->p[1] = 1;

      polynome *y = creePolynome(1);
      y->p[1] = 4;

      tp = susPolynome(x, y);
      Li = tp;

      printf("degrès max de mon poly est :%d\n", Li->maxDeg);

      /* ça c'est bon */
      /* printf("poour i = %d, on à le x qui vaut est :%f\n", i,
       * pointstab[0][i]); */

      /* Li = multPolynome(Li, x); */
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

  /* for (i = 0; i < ListLenght(points); ++i) */
  /* { */

  fonction = calculLi(i, points);
  /* fonction = addPolynome( */
  /* fonction, multPolynome(transformefloatenpoly(pointstab[1][i]), */
  /* calculLi(ListLenght(points), i, points))); */
  /* } */
  /* printf("taille fonction = %d\n", fonction->maxDeg); */

  return fonction;
}
