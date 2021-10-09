/*!
 * \file lagrange.h
 * \brief Header du lagrange.c
 * \author Payard
 * \version pré-alpha
 * \date 8 Octobre 2021
 */
#ifndef LAGRANGE_HEADER_
#define LAGRANGE_HEADER_

#include "listePoint.h"
#include <stdio.h>

#include "polynome.h"

polynome *calculLi(int numero, Liste points);
polynome *calculLagrange(Liste points);

#endif /* LAGRANGE_HEADER_ */
