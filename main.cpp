#include "bibliotheque.h"
#include "screens.h"
#include "fonctions.h"

/*Programme principal -> Déclaration des pointeurs*/
int main(int argc, char *argv[])
{
    /*Allocation de la mémoire pour chaque élèments SDL*/
        SDL_Surface *fenetre = NULL, *imagebg=NULL;

    /* Initialisiation de la musique */
        int flags=MIX_INIT_MP3;
        Mix_Init(flags);
        //open 44.1KHz, signed 16bit, system byte order,stereo audio, using 1024 byte chunks
        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
        //Définit le nombre de channels à mixer
        Mix_AllocateChannels(32);
        Mix_Music *musique=NULL;
        //On libère la chanson précédente s'il y en a une */
         if ( musique != NULL )
         {
            Mix_HaltMusic();
            Mix_FreeMusic(musique);
         }
         // On charge la nouvelle chanson
         musique = Mix_LoadMUS( "mu.mp3" );
        //On active la répétition de la musique à l'infini
        Mix_PlayMusic(musique, -1);

    /*Gestion du chronomètre dans le jeu*/
        /*char temps[20];
        float seconde=60.0;
        float temps0=0.0;*/

    /*Préparation de la bibliothèque SDL avec son module audio et vidéo + texte*/
        SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_TIMER);
        SDL_putenv("SDL_VIDEO_CENTERED=center");
        TTF_Init();

    /*Titre et icone du logiciel (doit se trouver avant la création de la fenêtre)*/
        SDL_WM_SetCaption("Qui veut gagner du pognon", NULL);
        SDL_WM_SetIcon(IMG_Load("qui.bmp"), NULL);

    //Préparation de l'élèment Background qui sera affiché
        fenetre = SDL_SetVideoMode(SCREEN_WIDTH , SCREEN_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF );//| SDL_RESIZABLE);

    //Initialisation de l'emplacement du fond
        SDL_Rect positionFond;
        positionFond.x=0;
        positionFond.y=0;

    //Application d'une image en guise de background
    imagebg = IMG_Load("qui.jpg");
        //Si un fond BLEU est présent sur une image que l'on veut rendre transparente:
    SDL_SetColorKey(imagebg, SDL_SRCCOLORKEY, SDL_MapRGB(imagebg->format, 0, 0, 255));

    int retour =1;

    /*"Attente" des actions de l'utilisateur*/
        do{
            switch(retour){
                case 1:
                        retour = menu(fenetre,imagebg, positionFond);
                        break;
                case 2:
                        retour = difficulte(fenetre,imagebg, positionFond);
                        break;
                /*3 difficultés */
                case 21:
                case 22:
                case 23:
                /*3 sauvegardes*/
                case 31:
                case 32:
                case 33:
                        retour = partie(fenetre,imagebg, positionFond, retour);
                        break;
                case 4:
                        retour = sauvegarde(fenetre,imagebg, positionFond);
                        break;
                case 5:
                        retour = option(fenetre,imagebg, positionFond);
                        break;
                /*Stats de fin de parties*/
                case 61:
                case 62:
                case 63:
                        retour = stats(fenetre,imagebg, positionFond,retour);
                        break;

            }
        }
        while(retour!=0);

    /*Libération de la mémoire qui était allouée à SDL*/
        Mix_FreeMusic(musique);
        Mix_CloseAudio();
        Mix_Quit();
        TTF_Quit();
        SDL_FreeSurface(imagebg);
        SDL_Quit();
    return EXIT_SUCCESS; //Similaire à un renvoi OK pour tous les OS
}



