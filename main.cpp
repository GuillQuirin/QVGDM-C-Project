#include "bibliotheque.h"
#include "screens.h"
#include "fonctions.h"

/*Programme principal -> D�claration des pointeurs*/
int main(int argc, char *argv[])
{
    /*Allocation de la m�moire pour chaque �l�ments SDL*/
        SDL_Surface *fenetre = NULL, *imagebg=NULL;

    /* Initialisiation de la musique */
        int flags=MIX_INIT_MP3;
        Mix_Init(flags);
        //open 44.1KHz, signed 16bit, system byte order,stereo audio, using 1024 byte chunks
        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
        //D�finit le nombre de channels � mixer
        Mix_AllocateChannels(32);
        Mix_Music *musique=NULL;
        //On lib�re la chanson pr�c�dente s'il y en a une */
         if ( musique != NULL )
         {
            Mix_HaltMusic();
            Mix_FreeMusic(musique);
         }
         // On charge la nouvelle chanson
         musique = Mix_LoadMUS( "mu.mp3" );
        //On active la r�p�tition de la musique � l'infini
        Mix_PlayMusic(musique, -1);

        //Pr�paration de la biblioth�que SDL avec son module audio et vid�o + texte*/
        SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_TIMER);
        SDL_putenv("SDL_VIDEO_CENTERED=center");
        TTF_Init();

    /*Police*/
        TTF_Font *police=NULL;
        police=TTF_OpenFont("times.ttf",25);

    /*Titre et icone du logiciel (doit se trouver avant la cr�ation de la fen�tre)*/
        SDL_WM_SetCaption("Qui veut gagner du pognon", NULL);
        SDL_WM_SetIcon(IMG_Load("qui.bmp"), NULL);

    //Pr�paration de l'�l�ment Background qui sera affich�
        fenetre = SDL_SetVideoMode(SCREEN_WIDTH , SCREEN_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF );
        //| SDL_RESIZABLE);

    //Initialisation de l'emplacement du fond
        SDL_Rect positionFond;
        positionFond.x=0;
        positionFond.y=0;

    //Application d'une image en guise de background
    imagebg = IMG_Load("qui.jpg");
        //Si un fond BLEU est pr�sent sur une image que l'on veut rendre transparente:
    SDL_SetColorKey(imagebg, SDL_SRCCOLORKEY, SDL_MapRGB(imagebg->format, 255, 255, 255));

    int retour = 1;

    /*"Attente" des actions de l'utilisateur*/
        do{
           switch(retour){
                case 1:
                        retour = menu(fenetre,imagebg, positionFond, police);
                        break;
                case 2:
                        retour = difficulte(fenetre,imagebg, positionFond, police);
                        break;
                /*3 difficult�s */
                case 21:
                case 22:
                case 23:
                        retour = partie(fenetre,imagebg, positionFond,police, retour);
                        break;
                /*Liste des sauvegardes*/
                case 4:
                        retour = sauvegarde(fenetre,imagebg, positionFond, police);
                        break;
                /*Options*/
                case 5://Options depuis menu
                //case 51://Options depuis game
                        retour = option(fenetre,imagebg, positionFond,police, retour);
                        break;
                /*Stats de fin de parties*/
                case 61:
                case 62:
                case 63:
                        retour = stats(fenetre,imagebg, positionFond,police, retour);
                        break;

            }
        }
        while(retour!=0);

    /*Lib�ration de la m�moire qui �tait allou�e � SDL*/
        Mix_FreeMusic(musique);
        Mix_CloseAudio();
        Mix_Quit();
        TTF_Quit();
        SDL_FreeSurface(imagebg);
        TTF_CloseFont(police);
        SDL_Quit();
    return EXIT_SUCCESS; //Similaire � un renvoi OK pour tous les OS
}
