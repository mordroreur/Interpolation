/*!
 * \file main.c
 * \brief Fichier principale de notre programme d'interpolation
 * \author Payard - Laurencot
 * \version pré-alpha
 * \date 8 Octobre 2021
 *
 *
 */

/*!
  \mainpage Programme d'interpolation
  \section Introduction
  \subsection sous-titre
  Je ne sais pas encore ce que fais ce programme...
  \n Donc je peu pas vous dire...
 */
#include "main.h"
#include "polynome.h"

/**
 * \fn int main ()
 * \brief Fonction principale du programme
 *
 *
 * \return 0 - Ce qui termine le programme
 */
int main()
{
  //  srand(time(NULL)); // in case we need random


  polynome *Solution;
  Liste listePoints = creerListe();
  
  char choix = 'A';
  
  printf("Bonjours et bienvenue dans ce programme d'interpolation.\n");
  printf("Pour voire l'aide utiliser la lettre h.\n");
  while (choix != 'q')
  {
    printf("Que voulez vous faire ? ");
    scanf("%c", &choix);
    getchar();
    switch (choix)
    {
    case 'h':
      printf("    h : Afficher cette aide.\n    g : Ouvre une fenêtre graphique (TODO : all).\n    n : Applique l'interpolation de Newton.\n    l : applique l'interpolation de lagrange.\n    r : Permet de remplir des points.\n    a : affiche la liste des points actuelles.\n    q : Quitter.\n\n");
      break;
    case 'g':RenderingInterpolation(&listePoints);break;
    case 'n':Solution = ResolutionParNewton(listePoints); affichepolynome(Solution);break;
    case 'l':Solution = calculLagrange(listePoints); affichepolynome(Solution);break;
    case 'r':casRemplir(&listePoints);break;
    case 'a':afficheListePoints(listePoints);break;
    case 'q':printf("Au revoir!\n");break;
    default:
      printf("Toutes les lettres a rentrés sont "
             "en minuscule. Utiliser h pour savoir quels sont vos choix.\n\n");
      getchar();
      break;
    }
  }



  

  /* polynome *p1 = creePolynomedemande(); */
  /* polynome *p2 = creePolynome(0); */
  /* polynome *poly = multPolynome(p1, p2); */
  /* printf("Test\n"); */

  /* affichepolynome(poly); */

  /* Test des différentes fonctions : */
  //  float flo = 3.0;
  //  polynome *machin = transformefloatenpoly(flo);

  /* int a = 10; */
  /* printf("le truc polynome transformé est %f  d'indice %d \n", machin->p[a],
   * a); */
  /* int i = 1000; */
  /* while (machin->p[i] == 0) */
  /* { */
  /*   printf("le truc polynome transformé est %d \n", i); */
  /*   i++; */
  /* } */

  /*Liste l = creerListe();

  point p;
  p.x = 0;
  p.y = 0;
  point k;
  k.x = 2;
  k.y = 4;
  point e;
  e.x = 4;
  e.y = 0;
  point m;
  m.x = 6;
  m.y = 4;
  ajouteDebut(&l, m);
  ajouteDebut(&l, e);
  ajouteDebut(&l, k);
  ajouteDebut(&l, p);
  float **points;


   points = ListeToTabsPoints(l); */


  /* for (int i = 0; i < 4; i++) */
  /* { */
  /* printf("point : %f, %f\n", points[0][i], points[1][i]); */
  /* } */

  //  polynome *fonction = calculLagrange(l);

  //  affichepolynome(fonction);
  //  fonction = ResolutionParNewton(l);
  //  affichepolynome(fonction);

  //  for(int i = 0; i < 4; i++){
  //    printf("point : %f, %f\n", points[0][i], points[1][i]);
  //  }

  //  polynome *pute = ResolutionParNewton(l);
  //  affichepolynome(pute);printf("\n");

  //  int x; /**< Description de x. */

  return 0;
}

void casRemplir(Liste *l){
  char choix = 'A';
  char s[30];
  int quit = 0;
  int curseur = 0;
  point p;
  
  if(ListLenght(*l) != 0){
    afficheListePoints(*l);
    printf("Voulez vous vider la liste(n = non) ? ");
    scanf("%c", &choix);
    getchar();
    if(choix != 'n'){
      ViderListe(l);
    }
  }

  while(!quit){
    printf("Veuillez entrer le X(un caractère pour quitter) : ");
    scanf("%s", s);getchar();
    curseur = 0;
    while(s[curseur] != '\0'){
      if(s[curseur] == ',' || s[curseur] == '.'){
	s[curseur] = '.';
      }else if(!isdigit(s[curseur])  && s[curseur] != '-'){
	printf("%c\n", s[curseur]);
	quit = 1;
	break;
      }
      curseur++;
    }
    if(!quit){
      p.x = atof(s);
      printf("Veuillez entrer le Y(un caractère pour quitter) : ");
      scanf("%s", s);getchar();
      curseur = 0;
      while(s[curseur] != '\0'){
	if(s[curseur] == ',' || s[curseur] == '.'){
	  s[curseur] = '.';
	}else if(!isdigit(s[curseur]) && s[curseur] != '-'){
	  quit = 1;
	  break;
	}
	curseur++;
      }
      if(!quit){
	p.y = atof(s);
	ajouteFin(l, p);
      }
    }
  }  
}
