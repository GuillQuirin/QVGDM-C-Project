#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#include "fonctions.c"
#include "menu.c"
#include "gestion_save.c"
#include "partie.c"
#include "stats.c"
#include "options.c"

int menu(SDL_Surface *fenetre, SDL_Surface *imagebg, SDL_Rect positionFond);
int difficulte(SDL_Surface *fenetre, SDL_Surface *imagebg, SDL_Rect positionFond);
int partie(SDL_Surface *fenetre, SDL_Surface *imagebg, SDL_Rect positionFond, int type);
int sauvegarde(SDL_Surface *fenetre, SDL_Surface *imagebg, SDL_Rect positionFond);
int option(SDL_Surface *fenetre, SDL_Surface *imagebg, SDL_Rect positionFond);
int stats(SDL_Surface *fenetre, SDL_Surface *imagebg, SDL_Rect positionFond, int type);
