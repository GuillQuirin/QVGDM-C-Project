#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#include "fonctions.c"
#include "menu.c"
#include "sauvegarde.c"
#include "difficulte.c"
#include "partie.c"
#include "stats.c"
#include "options.c"


int menu(SDL_Surface *fenetre, SDL_Surface *imagebg, SDL_Rect positionFond, TTF_Font police);
int difficulte(SDL_Surface *fenetre, SDL_Surface *imagebg, SDL_Rect positionFond,  TTF_Font police);
int partie(SDL_Surface *fenetre, SDL_Surface *imagebg, SDL_Rect positionFond,TTF_Font police, int type);
int sauvegarde(SDL_Surface *fenetre, SDL_Surface *imagebg, SDL_Rect positionFond, TTF_Font police);
int option(SDL_Surface *fenetre, SDL_Surface *imagebg, SDL_Rect positionFond,  TTF_Font police);
int stats(SDL_Surface *fenetre, SDL_Surface *imagebg, SDL_Rect positionFond, TTF_Font police, int type);
