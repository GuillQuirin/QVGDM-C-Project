#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "timer.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int interieurClic(SDL_Event event, SDL_Rect zone, int longueur, int hauteur);
int interieurMove(SDL_Event event, SDL_Rect zone, int longueur, int hauteur);

/*Programme principal -> Déclaration des pointeurs*/
int main(int argc, char *argv[])
{
    int cpt=0;

    /*Allocation de la mémoire pour chaque élèments SDL*/
        SDL_Surface *fenetre = NULL, *imagebg=NULL;
        SDL_Surface *texte1=NULL, *texte2=NULL, *texte3=NULL, *texte4=NULL;
        SDL_Surface *rectangle1=NULL, *rectangle2=NULL, *rectangle3=NULL, *rectangle4=NULL;

        int Reclongueur=250, Rechauteur=60;

    /* Initialise SDL_Mixer */
        int flags=MIX_INIT_MP3;
        int initted=Mix_Init(flags);

        /* open 44.1KHz, signed 16bit, system byte order,stereo audio, using 1024 byte chunks */
        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);

        /* Définit le nombre de channels à mixer */
        Mix_AllocateChannels(32);

        Mix_Music *musique=NULL;

        /* On libère la chanson précédente s'il y en a une */
         if ( musique != NULL )
         {
            Mix_HaltMusic();
            Mix_FreeMusic(musique);
         }

         /* On charge la nouvelle chanson */
         musique = Mix_LoadMUS( "mu.mp3" );

        /* On active la répétition de la musique à l'infini */
        Mix_PlayMusic(musique, -1);

    /*Declaration de la variable d'évènements*/
        SDL_Event evenement;
        int boucle = 1;

    /*Déclaration des styles pour le texte*/
        TTF_Font *police=NULL;
        SDL_Color couleurNoire = {0,0,0};

    /*Gestion du chronomètre dans le jeu*/
        char temps[20];
        float seconde=60.0;
        float temps0=0.0;

    /*Initialisation de la position de chaque element*/
        SDL_Rect positionFond;
        SDL_Rect positionRect1,positionRect2,positionRect3,positionRect4;
        SDL_Rect positionTexte1, positionTexte2, positionTexte3, positionTexte4;

    /*Préparation de la bibliothèque SDL avec son module audio et vidéo + texte*/
        SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_TIMER);
        SDL_putenv("SDL_VIDEO_CENTERED=center");
        TTF_Init();

    /*Titre du logiciel*/
        SDL_WM_SetCaption("Titre du projet", NULL);

    /*Icone du logiciel (doit se trouver avant la création de la fenêtre)*/
        SDL_WM_SetIcon(IMG_Load("qui.bmp"), NULL);

    //Préparation de l'élèment Background qui sera affiché
        fenetre = SDL_SetVideoMode(SCREEN_WIDTH , SCREEN_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF );//| SDL_RESIZABLE);

    //Chargement de la police
        police=TTF_OpenFont("police.ttf",25);
        TTF_SetFontStyle(police,TTF_STYLE_NORMAL);//, TTF_STYLE_ITALIC | TTF_STYLE_UNDERLINE);
        texte1 = TTF_RenderText_Blended(police, "JOUER", couleurNoire);
        texte2 = TTF_RenderText_Blended(police, "SAUVEGARDE", couleurNoire);
        texte3 = TTF_RenderText_Blended(police, "OPTIONS", couleurNoire);
        texte4 = TTF_RenderText_Blended(police, "QUITTER", couleurNoire);

    //Initialisation de l'emplacement de chaque élèment avant la boucle
        positionFond.x=0;
        positionFond.y=0;

        positionRect1.x = 40;
        positionRect1.y = 300;

        positionRect2.x = 330;
        positionRect2.y = 300;

        positionRect3.x = 40;
        positionRect3.y = 400;

        positionRect4.x = 330;
        positionRect4.y = 400;

        positionTexte1.x=positionRect1.x+(Reclongueur/3);
        positionTexte1.y=positionRect1.y+(Rechauteur/4);

        positionTexte2.x=positionRect2.x+(Reclongueur/10);
        positionTexte2.y=positionRect2.y+(Rechauteur/4);

        positionTexte3.x=positionRect3.x+(Reclongueur/4);
        positionTexte3.y=positionRect3.y+(Rechauteur/4);

        positionTexte4.x=positionRect4.x+(Reclongueur/4);
        positionTexte4.y=positionRect4.y+(Rechauteur/4);

float test=0.0;
test = timer(test);

    //Application d'une image en guise de background
    imagebg = IMG_Load("qui.jpg");
        //Si un fond BLEU est présent sur une image que l'on veut rendre transparente:
    SDL_SetColorKey(imagebg, SDL_SRCCOLORKEY, SDL_MapRGB(imagebg->format, 0, 0, 255));

 //Caractéristiques des élèments "rectangles"
    rectangle1 = SDL_CreateRGBSurface(SDL_HWSURFACE, Reclongueur, Rechauteur, 32, 0, 0, 0, 0);
    rectangle2 = SDL_CreateRGBSurface(SDL_HWSURFACE, Reclongueur, Rechauteur, 32, 0, 0, 0, 0);
    rectangle3 = SDL_CreateRGBSurface(SDL_HWSURFACE, Reclongueur, Rechauteur, 32, 0, 0, 0, 0);
    rectangle4 = SDL_CreateRGBSurface(SDL_HWSURFACE, Reclongueur, Rechauteur, 32, 0, 0, 0, 0);

    /*"Attente" des actions de l'utilisateur*/
        while(boucle){

            /*if(seconde !=-1.0){
                sprintf(temps, "%.1f", seconde);
                texte = TTF_RenderText_Blended(police, temps, couleurNoire); // Réécriture de l'élèment texte
            }*/
            SDL_WaitEvent(&evenement); // Récupération de l'évènement
            switch(evenement.type){//Type d'évènement
                case SDL_QUIT: // Arrêt du programme
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
                    switch(evenement.button.button){ //Analyse de l'équipement de la souris
                        case SDL_BUTTON_LEFT:
                            if(interieurClic(evenement,positionRect4, Reclongueur, Rechauteur)){
                                boucle=0;
                            }
                            break;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    //Rectangle 1
                    if(interieurMove(evenement, positionRect1, Reclongueur, Rechauteur)){
                        SDL_FillRect(rectangle1, NULL, SDL_MapRGB(fenetre->format, 255, 206, 112));
                       }
                    //Rectangle 2
                    if(interieurMove(evenement, positionRect2, Reclongueur, Rechauteur)){
                        SDL_FillRect(rectangle2, NULL, SDL_MapRGB(fenetre->format, 255, 206, 112));
                       }
                    //Rectangle 3
                    if(interieurMove(evenement, positionRect3, Reclongueur, Rechauteur)){
                        SDL_FillRect(rectangle3, NULL, SDL_MapRGB(fenetre->format, 255, 206, 112));
                       }
                    //Rectangle 4
                    if(interieurMove(evenement, positionRect4, Reclongueur, Rechauteur)){
                        SDL_FillRect(rectangle4, NULL, SDL_MapRGB(fenetre->format, 255, 206, 112));
                       }
                    break;
                case SDL_VIDEORESIZE:
                    positionFond.x=evenement.resize.w/2 - imagebg->w / 2;
                    positionFond.y=evenement.resize.h/2 - imagebg->h / 2;
                    break;
            }



            /*Affichage des élèments + background à chaque tour de boucle*/
                //Coloration du fond

                    SDL_FillRect(fenetre, NULL, SDL_MapRGB(fenetre->format, 255, 255, 112));
                    SDL_BlitSurface(imagebg, NULL, fenetre, &positionFond);

                    //Application de l'élèment sur le background
                    SDL_BlitSurface(rectangle1, NULL, fenetre, &positionRect1);
                    SDL_BlitSurface(rectangle2, NULL, fenetre, &positionRect2);
                    SDL_BlitSurface(rectangle3, NULL, fenetre, &positionRect3);
                    SDL_BlitSurface(rectangle4, NULL, fenetre, &positionRect4);

                    SDL_FillRect(rectangle1, NULL, SDL_MapRGB(fenetre->format, 17, 206, 112));
                    SDL_FillRect(rectangle2, NULL, SDL_MapRGB(fenetre->format, 17, 206, 112));
                    SDL_FillRect(rectangle3, NULL, SDL_MapRGB(fenetre->format, 17, 206, 112));
                    SDL_FillRect(rectangle4, NULL, SDL_MapRGB(fenetre->format, 17, 206, 112));

                //Caractéristiques du texte
                    SDL_BlitSurface(texte1, NULL, fenetre, &positionTexte1);
                    SDL_BlitSurface(texte2, NULL, fenetre, &positionTexte2);
                    SDL_BlitSurface(texte3, NULL, fenetre, &positionTexte3);
                    SDL_BlitSurface(texte4, NULL, fenetre, &positionTexte4);

                /*Mise à jour de la fenêtre avec les élèments modifiés*/
                    SDL_Flip(fenetre);
        }

    /*Libération de la mémoire qui était allouée à SDL*/
        Mix_FreeMusic(musique);
        Mix_CloseAudio();
        Mix_Quit();
        TTF_CloseFont(police);
        TTF_Quit();
        SDL_FreeSurface(texte1);
        SDL_FreeSurface(texte2);
        SDL_FreeSurface(texte3);
        SDL_FreeSurface(texte4);
        SDL_FreeSurface(imagebg);
        SDL_FreeSurface(rectangle1);
        SDL_FreeSurface(rectangle2);
        SDL_FreeSurface(rectangle3);
        SDL_FreeSurface(rectangle4);
        SDL_QUIT;
    return EXIT_SUCCESS; //Similaire à un renvoi OK pour tous les OS
}

int interieurClic(SDL_Event event, SDL_Rect zone, int longueur, int hauteur)
{
    //Vérification si le clic est dans la zone ciblée

    if(event.button.x<(zone.x+longueur)
           && event.button.x>zone.x
           && event.button.y<(zone.y+hauteur)
           && event.button.y>zone.y)
        return 1;
    else
        return 0;
}

int interieurMove(SDL_Event event, SDL_Rect zone, int longueur, int hauteur){

    //Vérification si le curseur passe au dessus de la zone ciblée

    if(event.motion.x<(zone.x+longueur)
           && event.motion.x>zone.x
           && event.motion.y<(zone.y+hauteur)
           && event.motion.y>zone.y)
        return 1;
    else
        return 0;
}

float timer(float seconde){
    /*static float temps0=0.0;
    float temps1=0.0;

    temps1 = SDL_GetTicks(); // Récupère le nb de millisecondes depuis le lancement
    if(temps1-temps0 >= 100)
    {
        if(seconde>=1)
            seconde-=0.1;
        else
            seconde=0.0;
        temps0=temps1;
        return seconde;
    }
    else // On endort le programme le temps qu'il faut
    {
        SDL_Delay(100 - (temps1 - temps0));
        return -1.0;
    }*/
    return 1.1;
}
