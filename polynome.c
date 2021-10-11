/*!
 * \file point.c
 * \brief Fichier contenant toute les opération utile sur les points.
 * \author Payard - Laurencot
 * \version pré-alpha
 * \date 8 Octobre 2021
 */
#include "polynome.h"

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

polynome *creePolynomedemande()
{
  int i;
  int deg;

  polynome *poly = (polynome *)malloc(sizeof(polynome));
  printf("Quel est le degrès de votre polynome ?\n");
  scanf("%d", &deg);

  poly->maxDeg = deg + 1;
  poly->p = (float *)malloc(sizeof(float) * (deg + 1));
  for (i = 0; i < poly->maxDeg; ++i)
  {
    printf("Quel est le coefficient pour x de degrès %d ?\n", i);
    scanf("%f", &poly->p[i]);
  }
  return poly;
}

void destroyPolynome(polynome *p)
{
  free(p->p);
  free(p);
}

void affichepolynome(polynome *p)
{
  int i;
  for (i = 0; i < p->maxDeg + 1; ++i)
  {
    if (i != 0)
    {
      printf("+ %6.2f*x^(%d)  ", p->p[i], i);
    }
    else
    { 
      printf("%6.2f ", p->p[i]);
    }
  }
  printf("\n");
}

polynome *addPolynome(polynome *p1, polynome *p2)
{
  int i;
  polynome *poly =
      creePolynome((p1->maxDeg > p2->maxDeg) ? p1->maxDeg : p2->maxDeg);

  for (i = 0; i < p1->maxDeg + 1; ++i)
  {
    /* printf("Degrèse de p1 %d \n", p1->maxDeg); */
    poly->p[i] = p1->p[i];
  }

  for (i = 0; i < p2->maxDeg + 1; ++i)
  {
    poly->p[i] += p2->p[i];
  }
  destroyPolynome(p1);
  destroyPolynome(p2);
  return poly;
}

polynome *transformefloatenpoly(float unfloat)
{
  polynome *poly = creePolynome(0);
  poly->p[0] = unfloat;
  return poly;
}

polynome *multPolynome(polynome *p1, polynome *p2)
{

  int i, j;
  polynome *poly = creePolynome(p1->maxDeg + p2->maxDeg);

  for (i = 0; i < p1->maxDeg + 1; ++i)
  {
    for (j = 0; j < p2->maxDeg + 1; ++j)
    {
      poly->p[i + j] += p1->p[i] * p2->p[j];
    }
  }
  destroyPolynome(p1);
  destroyPolynome(p2);
  return poly;
}

polynome *AdaptePoly(polynome *p){
  int x = p->maxDeg;
  //float precision = 0.01;
  //while(((p->p[x] - precision) < 0) && ((p->p[x] + precision) > 0) && (x > 0)){
  while((p->p[x] == 0) && (x > 0)){
    x--;
  }
  polynome *Sol = creePolynome(x);
  for(int i = 0; i < x+1; i++){
    Sol->p[i] = p->p[i];
  }
  destroyPolynome(p);
  return Sol;
}
