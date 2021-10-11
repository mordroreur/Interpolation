#include "render.h"
#include "lagrange.h"
#include "listePoint.h"

/**
 * \fn int main (int argc, char **argv)
 * \brief Fonction principale du programme contenant la bouclle principale
 *
 * \param argc nombre d'argument entré lors de l'appelle du programme
 * \param argv argumentss entrés lors de l'appelle du programme
 * \return 0 - Si tout c'est bien passé
 */
Liste *RenderingInterpolation(Liste *l) {

  SDL_Window *window = NULL; /*!< Adresse de la fenêtre que l'on va créer. */

  int Stape = 10; /*!< Etat actuelle du jeu. */
  int SizeX = 1200; /*!< Taille de l'écran en largeur. */
  int SizeY = 750; /*!< Taille de l'écran en longueur. */

  polynome *newt = ResolutionParNewton(*l);
  polynome *lagr = calculLagrange(*l);

  Liste pointNewt = creerListe();
  Liste pointLagr = creerListe();
  long int LastFrame;
  long int TimeCount;
  long int NowTime;
  long int timeForNewFrame = 1000000/FPS_TO_GET;
  
  int fpsCount = 0;

  long int LastTick;
  long int timeForNewTick = 1000000/TICK_TO_GET;
  
  int tickCount = 0;
  
  


  int tmpCount = 0;

  SDL_Event event;
  SDL_Renderer *renderer = NULL;


  
  create_Win(&renderer, window, &SizeX, &SizeY);
  
  /************Initialisation des variables de temps**************/
  LastFrame = getTime();
  LastTick = getTime();
  TimeCount = getTime();
  NowTime = getTime();

  
  /************Début de la boucle principale**********************/
  while(Stape){
    NowTime = getTime();

    if(NowTime - LastFrame > timeForNewFrame){

      draw(renderer, SizeX, SizeY, newt, lagr, pointNewt, pointLagr, *l);


    
      SDL_RenderPresent(renderer);

      LastFrame += timeForNewFrame;
      fpsCount++;
    }else if(NowTime - LastTick > timeForNewTick){

      
      LastTick += timeForNewTick;
      tickCount++;
    }else{
      NowTime = getTime();
      long SleepForCPU = 0;
      if((timeForNewTick - (NowTime-LastFrame)) < (timeForNewTick - (NowTime-LastTick)) && (timeForNewTick - (NowTime-LastFrame)) > 0) {
	SleepForCPU = (long)(timeForNewFrame - (NowTime-LastFrame))/300;
      }else if((timeForNewTick - (NowTime-LastTick)) > 0){
	SleepForCPU = (long)(timeForNewTick - (NowTime-LastTick))/300;
      }
      SDL_Delay(SleepForCPU);
      
      
    }
  

    
    /* Gestion des imputs clavier */
    while(SDL_PollEvent(&event)){
      switch(event.type){
      case SDL_KEYDOWN:break;//KeyDown(&event.key);break;
      case SDL_KEYUP:keyUp(&event.key, &Stape);break;
	//case SDL_MOUSEBUTTONDOWN:mousePress(&event.button);break;
      case SDL_QUIT:Stape = 0;break;
      default:break;
      }  
    }


    
    
    if(NowTime > TimeCount){
      TimeCount+=1000000;
      //printf("%d images cette seconde\n", fpsCount);
      fpsCount = 0;
      tmpCount++;
    }

    
  }

    
  /* on referme proprement */
  end_sdl(1,"Normal ending",renderer, window);
  

  return l;
}























/**
 * \fn void end_sdl(char ok, char const * msg, SDL_Window *window, SDL_Renderer
 * *renderer) \brief Fonction de destruction d'une fenetre
 *
 * \param ok information sur si la fenetre est détruite à cause d'une erreur ou
 * de facon voulut \param *msg message à afficher à l'utilisateur notament en
 * cas de bug \param *window l'adresse de la fenetre à détruire \param *renderer
 * l'adresse de laffichage dans la fenêtre à détruire \return void
 */
void end_sdl(char ok, char const * msg, SDL_Renderer *renderer, SDL_Window *window){
  char msg_formated[255];
  int l;

  if (!ok){
    strncpy(msg_formated, msg, 250);
    l = strlen(msg_formated);
    strcpy(msg_formated+l, " : %s\n");

    SDL_Log(msg_formated, SDL_GetError());
  }

  if(renderer != NULL){
    SDL_DestroyRenderer(renderer);
  }
  if(window != NULL){
    SDL_DestroyWindow(window);
  }
  SDL_Quit();

  if (!ok) {exit(EXIT_FAILURE);}
}


/**
 * \fn void create_Win(SDL_Renderer **renderer)
 * \brief Fonction de création d'une fenetre
 *
 * \param **renderer l'adresse de laffichage dans la fenêtre
 * \return void
 */
void create_Win(SDL_Renderer **renderer, SDL_Window *window, int *SX, int *SY){
  SDL_DisplayMode screen_dimension;

  /* Initialisation de la SDL  + gestion de l'échec possible */
  if (SDL_Init(SDL_INIT_VIDEO) != 0) end_sdl(0,"ERROR SDL INIT", *renderer, window);


  SDL_GetCurrentDisplayMode(0, &screen_dimension);
    //    printf("Taille de l'écran\n\tw : %d\n\th : %d\n", screen_dimension.w, screen_dimension.h);


    /* Création de la fenêtre */
  window = SDL_CreateWindow("Interpolation",
                            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                            screen_dimension.w,screen_dimension.h,
                            SDL_WINDOW_FULLSCREEN);
  if (window == NULL) end_sdl(0,"ERROR WINDOW CREATION", *renderer, window);

  /* Création du renderer */ 
  *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (*renderer == NULL) end_sdl(0,"ERROR RENDERER CREATION", *renderer, window);

  if(TTF_Init()==-1) {
    printf("TTF_Init: %s\n", TTF_GetError());
    exit(2);
  }


  SDL_GetWindowSize(window, SX, SY);

}

/**
 * \fn long int getTime()
 * \brief Fonction qui retourne le temps en microsecondes
 *
 * \return un entier correspondant au temps
 */
long int getTime(){
  struct timespec tms;
  if (clock_gettime(CLOCK_REALTIME,&tms)) {
        return -1;
    }
  return ((tms.tv_sec*1000000) + (tms.tv_nsec/1000));
}

/**
 * \fn void keyUp(SDL_KeyboardEvent *key)
 * \brief Fonction de gestion du cas ou l'on arrete d'appuyer sur une touche
 *
 * \param *key la touche sur laquelle on arrête d'appuyer
 * \return void
 */
void keyUp(SDL_KeyboardEvent *key, int *Stape){
  //printf("%d\n", key->keysym.sym);
  switch(key->keysym.sym){
  case SDLK_ESCAPE:*Stape = 0;break;
    // case SDLK_SPACE:if(Stape == 5){Stape = 15;}else if(Stape == 15){Stape = 5;}break;
  default:break;
  }
}

/**
 * \fn void draw(SDL_Renderer *renderer)
 * \brief Dessin de l'écran de bug dans la fenetre
 *
 * \param *renderer l'adresse de l'intérieur de la fenetre que l'on veut
 * redessiner \return void
 */
void draw(SDL_Renderer *renderer, int SX, int SY, polynome *newt, polynome *lagr, Liste pointNewt, Liste pointLagr, Liste l){
  SDL_Rect rectangle;

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  rectangle.x = 0;
  rectangle.y = 0;
  rectangle.w = SX;
  rectangle.h = SY;
  SDL_RenderFillRect(renderer, &rectangle);


  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderDrawLine(renderer, 0, (7*SY)/8, SX, (7*SY)/8);







  TTF_Font* Sans = TTF_OpenFont("Res/Quicksilver.ttf", 24);

  
// this is the color in rgb format,
// maxing out all would give you the color white,
// and it will be your text's color
SDL_Color Dark = {0, 0, 0};

// as TTF_RenderText_Solid could only be used on
// SDL_Surface then you have to create the surface first
SDL_Surface* surfaceMessage =
      TTF_RenderText_Solid(Sans, "Testpons ?", Dark); 

// now you can convert it into a texture
SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

SDL_Rect Message_rect; //create a rect
Message_rect.x = 0;  //controls the rect's x coordinate 
Message_rect.y = 0; // controls the rect's y coordinte
Message_rect.w = 100; // controls the width of the rect
Message_rect.h = 100; // controls the height of the rect

// (0,0) is on the top left of the window/screen,
// think a rect as the text's box,
// that way it would be very simple to understand

// Now since it's a texture, you have to put RenderCopy
// in your game loop area, the area where the whole code executes

// you put the renderer's name first, the Message,
// the crop size (you can ignore this if you don't want
// to dabble with cropping), and the rect which is the size
// and coordinate of your texture
SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

// Don't forget to free your surface and texture
SDL_FreeSurface(surfaceMessage);
SDL_DestroyTexture(Message);

  
  /*
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderDrawLine(renderer,0,0,400, 400);
  SDL_RenderDrawLine(renderer,400,0,0, 400);


  for(float angle = 0 ; angle<2*3.1416 ; angle+=3.1416/20){
    SDL_SetRenderDrawColor(renderer,
                           (cos(angle*2)+1)*255/2,
                           (cos(angle*5)+1)*255/2,
                           (cos(angle)+1)*255/2,
                           255);
    SDL_RenderDrawPoint(renderer, 200 + 100 * cos(angle), 200 + 150 *sin(angle));
    }*/
}




































/**
 * \fn void mousePress(SDL_MouseButtonEvent *button)
 * \brief Fonction de gestion de la souris
 *
 * \param *button le click sur lequel on appuie
 * \return void
 *//*
void mousePress(SDL_MouseButtonEvent *button){

  int x;
  int y;
  if(Stape == 10){
    if(button->button == SDL_BUTTON_LEFT){
      SDL_GetMouseState(&x, &y);
      if((x > SizeX/2 - SizeX/6) && (x < SizeX/2 + SizeX/6) && (y > SizeY/2 - SizeY/8) && (y < SizeY/2 + SizeY/8)){
	tab = (int**)malloc(tailleX*sizeof(int*));
	for(int i = 0; i < tailleX; i++){
	  tab[i] = (int*)malloc(tailleY*sizeof(int));
	  for(int j = 0; j < tailleY; j++){
	    tab[i][j] = 0;
	  }
	}
	Stape = 5;
      }
    }
  }else if(Stape == 5){
     if(button->button == SDL_BUTTON_LEFT){
       SDL_GetMouseState(&x, &y);
       if((x/(SizeX/tailleX) < tailleX) && (x/(SizeX/tailleX) > -1) && (y/(SizeY/tailleY) < tailleY) && (y/(SizeY/tailleY) > 0)){
	 tab[x/(SizeX/tailleX)][y/(SizeY/tailleY)] = 1;
       }
     }else if(button->button == SDL_BUTTON_RIGHT){
       SDL_GetMouseState(&x, &y);
       if((x/(SizeX/tailleX) < tailleX) && (x/(SizeX/tailleX) > -1) && (y/(SizeY/tailleY) < tailleY) && (y/(SizeY/tailleY) > 0)){
	 tab[x/(SizeX/tailleX)][y/(SizeY/tailleY)] = 0;
       }
     }
  }
  
  }*/


