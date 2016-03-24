#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "timer.h"

/*Programme principal -> D�claration des pointeurs*/
int main(int argc, char *argv[])
{
    /*Allocation de la m�moire pour chaque �l�ments SDL*/
        SDL_Surface *fenetre = NULL, *imagebg=NULL, *rectangle = NULL, *texte=NULL;

    /* Initialise SDL_Mixer */
        int flags=MIX_INIT_MP3;
        int initted=Mix_Init(flags);

        /* open 44.1KHz, signed 16bit, system byte order,stereo audio, using 1024 byte chunks */
        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);

        /* D�finit le nombre de channels � mixer */
        Mix_AllocateChannels(32);

        Mix_Music *musique=NULL;

        /* On lib�re la chanson pr�c�dente s'il y en a une */
         if ( musique != NULL )
         {
            Mix_HaltMusic();
            Mix_FreeMusic(musique);
         }

         /* On charge la nouvelle chanson */
         musique = Mix_LoadMUS( "mus.mp3" );

        /* On active la r�p�tition de la musique � l'infini */
        Mix_PlayMusic(musique, -1);

    /*Declaration de la variable d'�v�nements*/
        SDL_Event evenement;
        int boucle = 1;

    /*D�claration des styles pour le texte*/
        TTF_Font *police=NULL;
        SDL_Color couleurNoire = {0,0,0};

    /*Gestion du chronom�tre dans le jeu*/
        char temps[20];
        float seconde=60.0;
        float temps0=0.0;

    /*Initialisation de la position de chaque element*/
        SDL_Rect positionRect, positionFond, positionTexte;

    /*Pr�paration de la biblioth�que SDL avec son module audio et vid�o + texte*/
        SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_TIMER);
        TTF_Init();

    /*Titre du logiciel*/
        SDL_WM_SetCaption("Titre du projet", NULL);

    /*Icone du logiciel (doit se trouver avant la cr�ation de la fen�tre)*/
        SDL_WM_SetIcon(IMG_Load("qui.bmp"), NULL);

    //Pr�paration de l'�l�ment Background qui sera affich�
        fenetre = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE);

    //Chargement de la police
        police=TTF_OpenFont("police.ttf",65);
        TTF_SetFontStyle(police, TTF_STYLE_ITALIC | TTF_STYLE_UNDERLINE);
        texte = TTF_RenderText_Blended(police, "Test", couleurNoire);

    //Initialisation de l'emplacement de chaque �l�ment avant la boucle
        positionFond.x=0;
        positionFond.y=0;
        positionRect.x = 0;
        positionRect.y = 0;
        positionTexte.x=0;
        positionTexte.y=0;

float test=0.0;
test = timer(test);
    /*"Attente" des actions de l'utilisateur*/
        while(boucle){

            /*if(seconde !=-1.0){
                sprintf(temps, "%.1f", seconde);
                texte = TTF_RenderText_Blended(police, temps, couleurNoire); // R��criture de l'�l�ment texte
            }*/
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

                //Caract�ristiques du texte
                    SDL_BlitSurface(texte, NULL, fenetre, &positionTexte);

                /*Mise � jour de la fen�tre avec les �l�ments modifi�s*/
                    SDL_Flip(fenetre);
        }

    /*Lib�ration de la m�moire qui �tait allou�e � SDL*/
        Mix_FreeMusic(musique);
        Mix_CloseAudio();
        Mix_Quit();
        TTF_CloseFont(police);
        TTF_Quit();
        SDL_FreeSurface(texte);
        SDL_FreeSurface(imagebg);
        SDL_FreeSurface(rectangle);
        SDL_QUIT;
    return EXIT_SUCCESS; //Similaire � un renvoi OK pour tous les OS
}
