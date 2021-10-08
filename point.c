/*!
 * \file point.c
 * \brief Fichier contenant toute les opération utile sur les points.
 * \author Payard - Laurencot
 * \version pré-alpha
 * \date 8 Octobre 2021
 */
#include "point.h"

polynome *creePolynome(int maxDeg)
{
  int i;
  polynome *poly = (polynome *)malloc(sizeof(polynome));

  poly->maxDeg = maxDeg;
  poly->p = (float *)malloc(sizeof(float) * (maxDeg + 1));
  for (i = 0; i < maxDeg; ++i)
  {
    poly->p[i] = 0;
  }
  return poly;
}

void destroyPolynome(polynome *p)
{
  free(p->p);
  free(p);
}

polynome *addPolynome(polynome *p1, polynome *p2)
{
  int i;
  polynome *poly =
      creePolynome((p1->maxDeg > p2->maxDeg) ? p1->maxDeg : p2->maxDeg);
  for (i = 0; i < p1->maxDeg; ++i)
  {
    poly->p[i] = p1->p[i];
  }
  for (i = 0; i < p2->maxDeg; ++i)
  {
    poly->p[i] += p2->p[i];
  }
  destroyPolynome(p1);
  destroyPolynome(p2);
  return poly;
}

polynome *susPolynome(polynome *p1, polynome *p2)
{
  int i;
  polynome *poly =
      creePolynome((p1->maxDeg > p2->maxDeg) ? p1->maxDeg : p2->maxDeg);
  for (i = 0; i < p1->maxDeg; ++i)
  {
    poly->p[i] = p1->p[i];
  }
  for (i = 0; i < p2->maxDeg; ++i)
  {
    poly->p[i] -= p2->p[i];
  }
  destroyPolynome(p1);
  destroyPolynome(p2);
  return poly;
}

polynome *multPolynome(polynome *p1, polynome *p2)
{
  int i;
  polynome *poly = creePolynome(p1->maxDeg + p2->maxDeg);
  for (i = 0; i < p1->maxDeg + p2->maxDeg; ++i)
  {
    /* for (j = 0; i < ; ++i) */
    /* { */
    /* } */
    if (p1->p[i] == 0)
    {
      poly->p[i] = p2->p[i];
    }
    else if (p2->p[i] == 0)
    {
      poly->p[i] = p1->p[i];
    }
    else
    {
      poly->p[2 * i] = p1->p[i] * p2->p[i];
    }
  }
  destroyPolynome(p1);
  destroyPolynome(p2);
  return poly;
}
