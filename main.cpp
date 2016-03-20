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
    /*Allocation de la m�moire pour chaque �l�ments SDL*/
        SDL_Surface *fenetre = NULL, *imagebg=NULL, *rectangle = NULL;

    /*Initialisation de la position de chaque element*/
        SDL_Rect positionRect, positionFond;

    /*Pr�paration de la biblioth�que SDL avec son module audio et vid�o seulement*/
        SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_TIMER);

    /*Titre du logiciel*/
        SDL_WM_SetCaption("Titre du projet", NULL);

    /*Icone du logiciel (doit se trouver avant la cr�ation de la fen�tre)*/
        SDL_WM_SetIcon(IMG_Load("qui.bmp"), NULL);

    //Pr�paration de l'�l�ment Background qui sera affich�
        fenetre = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
            if (fenetre == NULL) // Si l'ouverture a �chou�, on le note et on arr�te
            {
                fprintf(stderr, "Impossible de charger le mode vid�o : %s\n", SDL_GetError());
                exit(EXIT_FAILURE);
            }
        //Coloration du fond
            //SDL_FillRect(fenetre, NULL, SDL_MapRGB(fenetre->format, 17, 206, 112));
        //OU
        //Application d'une image en guise de background
            imagebg = IMG_Load("qui.bmp");
            positionFond.x=0;
            positionFond.y=0;
                //Si un fond BLEU est pr�sent sur une image que l'on veut rendre transparente:
            SDL_SetColorKey(imagebg, SDL_SRCCOLORKEY, SDL_MapRGB(imagebg->format, 0, 0, 255));
            SDL_BlitSurface(imagebg, NULL, fenetre, &positionFond);

    //Caract�ristiques de l'�l�ment "rectangle"
        rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, 220, 180, 32, 0, 0, 0, 0);
        positionRect.x = 0;
        positionRect.y = 0;
        SDL_FillRect(rectangle, NULL, SDL_MapRGB(fenetre->format, 17, 206, 112));
        SDL_BlitSurface(rectangle, NULL, fenetre, &positionRect);//Application de l'�l�ment sur le background

    /*Mise � jour de la fen�tre avec les �l�ments modifi�s*/
        SDL_Flip(fenetre);

    //"Attente" des actions de l'utilisateur
        pause();

    /*Lib�ration de la m�moire qui �tait allou�e � SDL*/
        SDL_FreeSurface(imagebg);
        SDL_FreeSurface(rectangle);
        SDL_QUIT;
    return EXIT_SUCCESS; //Similaire � un renvoi OK pour tous les OS
}

/*Fonction d'attente des �v�nements*/
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
