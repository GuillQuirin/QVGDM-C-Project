#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL_image.h>

/*Appels des fonctions*/
//void pause();

/*test*/
int test(int argc, char *argv[])
{

}
/*Programme principal*/
int main(int argc, char *argv[])
{
    /*Allocation de la m�moire pour chaque �l�ments SDL*/
        SDL_Surface *fenetre = NULL, *imagebg=NULL, *rectangle = NULL;

    /*Declaration de la variable d'�v�nements*/
        SDL_Event evenement;
        int boucle = 1;

    /*Gestion du chronom�tre dans le jeu*/
        float seconde=0.0;
        int temps0=0;
        int temps1=0;

    /*Initialisation de la position de chaque element*/
        SDL_Rect positionRect, positionFond;

    /*Pr�paration de la biblioth�que SDL avec son module audio et vid�o seulement*/
        SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_TIMER);

    /*Titre du logiciel*/
        SDL_WM_SetCaption("Titre du projet", NULL);

    /*Icone du logiciel (doit se trouver avant la cr�ation de la fen�tre)*/
        SDL_WM_SetIcon(IMG_Load("qui.bmp"), NULL);

    //Pr�paration de l'�l�ment Background qui sera affich�
        fenetre = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE);
            if (fenetre == NULL) // Si l'ouverture a �chou�, on le note et on arr�te
            {
                fprintf(stderr, "Impossible de charger le mode vid�o : %s\n", SDL_GetError());
                exit(EXIT_FAILURE);
            }
    //Initialisation de l'emplacement de chaque �l�ment avant la boucle
        positionFond.x=0;
        positionFond.y=0;
        positionRect.x = 0;
        positionRect.y = 0;

    /*"Attente" des actions de l'utilisateur*/
        while(boucle){

            temps1 = SDL_GetTicks(); // R�cup�re le nb de millisecondes depuis le lancement
            if(temps1-temps0 > 10)
            {
                seconde+=0.001;
                temps0=temps1;
            }
            else // On endort le programme le temps qu'il faut
            {
                SDL_Delay(10 - (temps1 - temps0));
            }

            SDL_PollEvent(&evenement); // R�cup�ration de l'�v�nement
            switch(evenement.type){//Type d'�v�nement
                case SDL_QUIT: // Arr�t du programme
                    boucle = 0;
                    break;
                case SDL_KEYDOWN: //Appui sur une touche
                    switch(evenement.key.keysym.sym){// Analyse de la touche
                        case SDLK_ESCAPE://Echap
                            boucle=0;
                            break;
                    }
                    break;
                case SDL_MOUSEBUTTONUP: // Clic souris
                    switch(evenement.button.button){ //Analyse de l'�quipement de la souris
                        case SDL_BUTTON_RIGHT:
                            positionRect.x=evenement.button.x;
                            positionRect.y=evenement.button.y;
                            break;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    positionRect.x = evenement.motion.x;
                    break;
                case SDL_VIDEORESIZE:
                    positionFond.x=evenement.resize.w/2 - imagebg->w / 2;
                    positionFond.y=evenement.resize.h/2 - imagebg->h / 2;
                    break;
            }

            /*Affichage des �l�ments + background � chaque tour de boucle*/
                //Coloration du fond
                    SDL_FillRect(fenetre, NULL, SDL_MapRGB(fenetre->format, 255, 255, 112));
                //Application d'une image en guise de background
                    imagebg = IMG_Load("qui.bmp");
                        //Si un fond BLEU est pr�sent sur une image que l'on veut rendre transparente:
                    SDL_SetColorKey(imagebg, SDL_SRCCOLORKEY, SDL_MapRGB(imagebg->format, 0, 0, 255));
                    SDL_BlitSurface(imagebg, NULL, fenetre, &positionFond);

                //Caract�ristiques de l'�l�ment "rectangle"
                    rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, 220, 180, 32, 0, 0, 0, 0);

                    SDL_FillRect(rectangle, NULL, SDL_MapRGB(fenetre->format, 17, 206, 112));
                    SDL_BlitSurface(rectangle, NULL, fenetre, &positionRect);//Application de l'�l�ment sur le background

                /*Mise � jour de la fen�tre avec les �l�ments modifi�s*/
                    SDL_Flip(fenetre);
        }

    /*Lib�ration de la m�moire qui �tait allou�e � SDL*/
        SDL_FreeSurface(imagebg);
        SDL_FreeSurface(rectangle);
        SDL_QUIT;
    return EXIT_SUCCESS; //Similaire � un renvoi OK pour tous les OS
}

