
/*!
 * \file point.h
 * \brief Header du point.c
 * \author Payard - Laurencot
 * \version pré-alpha
 * \date 8 Octobre 2021
 */
#ifndef POINT_HEADER_
#define POINT_HEADER_

#include <stdio.h>


/**
 * \brief Structure correspondante à un point.
 *
 * Cette structure est un point, donc elle contient :
 * - x : La coordonnée en x du point.
 * - y : La coordonnée en y du point.
 */
typedef struct point{
  float x;
  float y;
} point;

typedef struct Polynome{
  float *p;
  int maxDeg;
}polynome;


polynome creePolynome(int maxDeg);
void destroyPolynome(polynome *p);
Polynome *addPolynome(polynome *p1, polynome *p2);
Polynome *susPolynome(polynome *p1, polynome *p2);
Polynome *multPolynome(polynome *p1, polynome *p2);

#endif
