#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL_image.h>

/*Appels des fonctions*/
void pause();

/*test*/
int test(int argc, char *argv[])
{

}
/*Programme principal*/
int main(int argc, char *argv[])
{
    /*Allocation de la mémoire pour chaque élèments SDL*/
        SDL_Surface *fenetre = NULL, *imagebg=NULL, *rectangle = NULL;

    /*Initialisation de la position de chaque element*/
        SDL_Rect positionRect, positionFond;

    /*Préparation de la bibliothèque SDL avec son module audio et vidéo seulement*/
        SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_TIMER);

    /*Titre du logiciel*/
        SDL_WM_SetCaption("Titre du projet", NULL);

    /*Icone du logiciel (doit se trouver avant la création de la fenêtre)*/
        SDL_WM_SetIcon(IMG_Load("qui.bmp"), NULL);

    //Préparation de l'élèment Background qui sera affiché
        fenetre = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
            if (fenetre == NULL) // Si l'ouverture a échoué, on le note et on arrête
            {
                fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
                exit(EXIT_FAILURE);
            }
        //Coloration du fond
            //SDL_FillRect(fenetre, NULL, SDL_MapRGB(fenetre->format, 17, 206, 112));
        //OU
        //Application d'une image en guise de background
            imagebg = IMG_Load("qui.bmp");
            positionFond.x=0;
            positionFond.y=0;
                //Si un fond BLEU est présent sur une image que l'on veut rendre transparente:
            SDL_SetColorKey(imagebg, SDL_SRCCOLORKEY, SDL_MapRGB(imagebg->format, 0, 0, 255));
            SDL_BlitSurface(imagebg, NULL, fenetre, &positionFond);

    //Caractéristiques de l'élèment "rectangle"
        rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, 220, 180, 32, 0, 0, 0, 0);
        positionRect.x = 0;
        positionRect.y = 0;
        SDL_FillRect(rectangle, NULL, SDL_MapRGB(fenetre->format, 17, 206, 112));
        SDL_BlitSurface(rectangle, NULL, fenetre, &positionRect);//Application de l'élèment sur le background

    /*Mise à jour de la fenêtre avec les élèments modifiés*/
        SDL_Flip(fenetre);

    //"Attente" des actions de l'utilisateur
        pause();

    /*Libération de la mémoire qui était allouée à SDL*/
        SDL_FreeSurface(imagebg);
        SDL_FreeSurface(rectangle);
        SDL_QUIT;
    return EXIT_SUCCESS; //Similaire à un renvoi OK pour tous les OS
}

/*Fonction d'attente des évènements*/
void pause()
{
    int continuer = 1;
    SDL_Event event;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
        }
    }
}
