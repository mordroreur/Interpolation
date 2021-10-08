/*!
 * \file newton.c
 * \brief File containing all the newton resolution.
 * \author Laurencot
 * \version pré-alpha
 * \date 8 Octobre 2021
 */
#include "newton.h"

/**
 * \fn Liste ResolutionParNewton(Liste points)
 * \brief Function that resolve an interpolation with the Newton method.
 *
 *
 * \param points - points is a list of points 
 * \param nbMaillon - nbMaillon is the number of the maillon we want to destroy
 * \return void - l is a pointer, no need to return it
 */
polynome *ResolutionParNewton(Liste points){
  int pointNB = ListLenght(points);
  polynome *Solution = creePolynome(pointNB);
  float **f = (float **)malloc(sizeof(float *) * (pointNB-1));
  for(int i = 0; i < pointNB-1; i++){
    f[i] = (float *)malloc(sizeof(float) * (pointNB-1-i));
  }
  

  for(int i = 0; i < pointNB-1; i++){
    for(int j = 0; j < pointNB-1-i; j++){
      if(i == 0){

	
      }else{
	
      }
    }
  }

  

  return Solution;
}
