/*!
 * \file lagrange.c
 * \brief Fichier contenant la résolution par la méthode de Lagrange.
 * \author Payard
 * \version pré-alpha
 * \date 8 Octobre 2021
 */
#include "lagrange.h"

float calculLi(int nombredepoint, int numero, Liste points)
{
  /* point;  transfore liste en tab*/
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
    }
    else
    {
      /* Li = multPolynome(Li, */
      /* (susPolynome(x, transformefloatenpoly(float unfloat)))); */
    }
  }
}

float calculLagrange(int nombredepoint, point *serie)
{
  int i;
  float resultat;
  for (i = 0; i < nombredepoint; ++i)
  {
    /* resultat = resultat + serie[i].y * calculLi(nombredepoint, i, serie); */
  }
}
