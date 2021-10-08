/*!
 * \file lagrange.c
 * \brief Fichier contenant la résolution par la méthode de Lagrange.
 * \author Payard
 * \version pré-alpha
 * \date 8 Octobre 2021
 */
#include "lagrange.h"

float calculLi(int nombredepoint, int numero, point *serie)
{
  int i;
  float resultat;
  float Li = 1;
  for (i = 0; i < nombredepoint; ++i)
  {
    if (i == numero)
    {
    }
    else
    {
      /* Li = Li * ...; */
    }
  }
}

float calculLagrange(int nombredepoint, point *serie)
{
  int i;
  float resultat;
  for (i = 0; i < nombredepoint; ++i)
  {
    resultat = resultat + serie[i].y * calculLi(nombredepoint, i, serie);
  }
}
