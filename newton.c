/*!
 * \file newton.c
 * \brief File containing all the newton resolution.
 * \author Laurencot
 * \version pré-alpha
 * \date 8 Octobre 2021
 */
#include "newton.h"
#include "polynome.h"



/**
 * \fn Liste ResolutionParNewton(Liste points)
 * \brief Function that resolve an interpolation with the Newton method.
 *
 *
 * \param points - points is a list of points 
 * \param nbMaillon - nbMaillon is the number of the maillon we want to destroy
 * \return void - l is a pointer, no need to return it
 */
polynome *ResolutionParNewton(Liste lstpoints)
{
  int pointNB = ListLenght(lstpoints);
  float **Points = ListeToTabsPoints(lstpoints);
  polynome *Solution = creePolynome(1);
  polynome *tmp;
  long double **triangle =
      (long double **)malloc(sizeof(long double *) * (pointNB));
  for (int i = 0; i < pointNB; i++)
  {
    triangle[i] = (long double *)malloc(sizeof(long double) * (pointNB - i));
  }

  for (int i = 0; i < pointNB; i++)
  {
    triangle[0][i] = Points[1][i];
  }

  for (int i = 1; i < pointNB; i++)
  {
    for (int j = 0; j < pointNB - i; j++)
    {
      triangle[i][j] = (triangle[i - 1][j + 1] - triangle[i - 1][0]) /
                       (Points[0][i + j] - Points[0][i - 1]);
    }
  }

  if (pointNB != 0)
  {
    Solution->p[0] = triangle[pointNB - 1][0];
  }
  for (int i = 0; i < pointNB - 1; i++)
  {
    /* créer le polynome constant */
    tmp = creePolynome(2);
    tmp->p[1] = 1;

    /* résolution de la méthode */
    tmp->p[0] = -Points[0][pointNB - 2 - i];
    Solution = multPolynome(Solution, tmp);
    Solution->p[0] += triangle[pointNB - i - 2][0];
  }
  Solution = AdaptePoly(Solution);
  return Solution;
}
