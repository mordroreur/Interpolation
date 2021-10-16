/*!
 * \file lagrange.c
 * \brief Fichier contenant la résolution par la méthode de Lagrange.
 * \author Payard
 * \version pré-alpha
 * \date 8 Octobre 2021
 */

#include "lagrange.h"

/**
 * \fn Liste calculLi(int numero,Liste points)
 * \brief Function that find Li to resolve an interpolation with the Lagrange
 * method.
 *
 *
 * \param numero - which is the number i of Li
 * \param points - points is a list of points
 * \param nbMaillon - nbMaillon is the number of the maillon we want to destroy
 * \return *polynome - Because we want Li
 */

float **untableaudepoint(int taille)
{
  int i, j;
  float **res = (float **)malloc(2 * sizeof(float *));
  res[0] = (float *)malloc(taille * sizeof(float));
  res[1] = (float *)malloc(taille * sizeof(float));

  for (i = 0; i < taille; ++i)
  {
    res[0][i] = i;
    res[1][i] = i;
  }
  return res;
}

polynome *calculLi(int numero, Liste points)
{

  /* Initialisation d'un tableau à partir d'une liste (accéder au
     valeur plus facilement) */
  float **pointstab = ListeToTabsPoints(points);
  int i;

  /* initiation du polynôme Li avec 1, car multiplication (si 0 alors
     résultat = 0) */
  polynome *Li = creePolynome(1);
  Li->p[0] = 1;

  /* initialisation de la variable temporaire pour la boucle */
  polynome *tp = creePolynome(0);
  tp->p[0] = 1;

  for (i = 0; i < ListLenght(points); ++i)
  {
    if (i == numero)
    {
      /* si i = numero, alors il y aurait une division par 0. On ne
         fait donc rien */
    }
    else
    {
      /* Création du polynôme pour les calculs */
      polynome *x = creePolynome(1);
      x->p[1] = 1;

      /* Calcul de la première différence */
      polynome *y = addPolynome(x, transformefloatenpoly(-pointstab[0][i]));

      /* calcul de la multiplication par l'inverse de xnum - xi */
      polynome *tmp = multPolynome(
          y,
          transformefloatenpoly(1 / (pointstab[0][numero] - pointstab[0][i])));

      /* multiplication par le polynôme précédemment calculé */
      Li = multPolynome(Li, tmp);
    }
  }
  return Li;
}

polynome *calculLagrange(Liste points)
{
  int i;

  /* création du polynôme du résultatde l'interpolation  */
  polynome *fonction = creePolynome(ListLenght(points));

  /* Initialisation d'un tableau à partir d'une liste (accéder au
     valeur plus facilement) */
  float **pointstab;
  pointstab = ListeToTabsPoints(points);

  /* boucle for pour multiplier par yi les Li calculer dans la
     fonction calculLi */
  for (i = 0; i < ListLenght(points); ++i)
  {
    fonction = addPolynome(fonction,
                           multPolynome(transformefloatenpoly(pointstab[1][i]),
                                        calculLi(i, points)));
  }

  /* ViderPoly(fonction); */
  return fonction;
}
