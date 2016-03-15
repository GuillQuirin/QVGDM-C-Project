#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char *argv[])
{

    /* Initialisation simple */
    if(SDL_Init(SDL_INIT_VIDEO) != 0 ){
        fprintf(stdout,"�chec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return -1;
    }

    {
        /* Cr�ation de la fen�tre */
        SDL_Window* pWindow = NULL;
        pWindow = SDL_CreateWindow("Ma premi�re application SDL2",SDL_WINDOWPOS_CENTERED,
                                                                  SDL_WINDOWPOS_CENTERED,
                                                                  640,
                                                                  480,
                                                                  SDL_WINDOW_SHOWN);
        //CreateWindow : Nom � afficher / pos en X / pos en Y /Largeur / Hauteur / options
        SDL_Renderer *pRenderer = SDL_CreateRenderer(pWindow,-1,SDL_RENDERER_ACCELERATED); // Cr�ation d'un SDL_Renderer utilisant l'acc�l�ration mat�rielle

        /*Image de Background*/
        if(pRenderer)
        {
            SDL_Surface *pSprite = SDL_LoadBMP("qui.bmp");
            if(pSprite)
            {
                SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer,pSprite); // Pr�paration du sprite
                if(pTexture)
                {
                    SDL_Rect dest = { 640/2 - pSprite->w/2,480/2 - pSprite->h/2, pSprite->w, pSprite->h};
                    SDL_RenderCopy(pRenderer,pTexture,NULL,&dest); // Copie du sprite gr�ce au SDL_Renderer

                    SDL_RenderPresent(pRenderer); // Affichage
                    //SDL_Delay(1000); // Attendre trois secondes, que l'utilisateur voit la fen�tre

                    SDL_DestroyTexture(pTexture); // Lib�ration de la m�moire associ�e � la texture
                }
                else
                {
                    fprintf(stdout,"�chec de cr�ation de la texture (%s)\n",SDL_GetError());
                }

                SDL_FreeSurface(pSprite); // Lib�ration de la ressource occup�e par le sprite
            }
            else
            {
                fprintf(stdout,"�chec de chargement du sprite (%s)\n",SDL_GetError());
            }

            SDL_DestroyRenderer(pRenderer); // Lib�ration de la m�moire du SDL_Renderer
        }
        else
        {
            fprintf(stdout,"�chec de cr�ation du renderer (%s)\n",SDL_GetError());
        }

        /*Gestion de la fen�tre*/
        if( pWindow )
        {
            //SDL_Delay(3000); /* Attendre trois secondes, que l'utilisateur voie la fen�tre */
            char cont = 1; // D�termine si on continue la boucle principale
            SDL_Event event;

            while ( cont != 0 )
            {
                while ( SDL_PollEvent(&event) )
                {
                    // Traitement de l'�v�nement
                    switch (event.type) /* Quel �v�nement avons-nous ? */
                    {
                        case SDL_KEYDOWN:
                            fprintf(stdout, "Un appuie sur une touche :\n");
                            fprintf(stdout, "\tr�p�tition ? : %d\n",event.key.repeat);
                            fprintf(stdout, "\tscancode : %d\n",event.key.keysym.scancode);
                            fprintf(stdout, "\tkey : %d\n",event.key.keysym.sym);
                            if ( event.key.keysym.scancode == SDL_SCANCODE_ESCAPE )
                            {
                                cont = 0;
                            }
                            break;
                        case SDL_KEYUP:
                            fprintf(stdout, "Un relachement d'une touche :\n");
                            fprintf(stdout, "\tr�p�tition ? : %d\n",event.key.repeat);
                            fprintf(stdout, "\tscancode : %d\n",event.key.keysym.scancode);
                            fprintf(stdout, "\tkey : %d\n",event.key.keysym.sym);
                            break;

                        case SDL_MOUSEMOTION:
                            fprintf(stdout, "Un d�placement de la souris :\n");
                            fprintf(stdout, "\tfen�tre : %d\n",event.motion.windowID);
                            fprintf(stdout, "\tsouris : %d\n",event.motion.which);
                            fprintf(stdout, "\tposition : %d;%d\n",event.motion.x,event.motion.y);
                            fprintf(stdout, "\tdelta : %d;%d\n",event.motion.xrel,event.motion.yrel);
                            break;
                        case SDL_MOUSEBUTTONUP:
                            fprintf(stdout, "Un relachement d'un bouton de la souris :\n");
                            fprintf(stdout, "\tfen�tre : %d\n",event.button.windowID);
                            fprintf(stdout, "\tsouris : %d\n",event.button.which);
                            fprintf(stdout, "\tbouton : %d\n",event.button.button);
    #if SDL_VERSION_ATLEAST(2,0,2)
                            fprintf(stdout, "\tclics : %d\n",event.button.clicks);
    #endif
                            fprintf(stdout, "\tposition : %d;%d\n",event.button.x,event.button.y);
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            fprintf(stdout, "Un appuie sur un bouton de la souris :\n");
                            fprintf(stdout, "\tfen�tre : %d\n",event.button.windowID);
                            fprintf(stdout, "\tsouris : %d\n",event.button.which);
                            fprintf(stdout, "\tbouton : %d\n",event.button.button);
    #if SDL_VERSION_ATLEAST(2,0,2)
                            fprintf(stdout, "\tclics : %d\n",event.button.clicks);
    #endif
                            fprintf(stdout, "\tposition : %d;%d\n",event.button.x,event.button.y);
                            break;

                        case SDL_WINDOWEVENT:
                            fprintf(stdout, "Un �v�nement de fen�tre, sur la fen�tre : %d\n",event.window.windowID);
                            // En th�orie, ici, il faudrait faire un autre test ou switch pour chaque type de cet �v�nement
                            break;
                        default:
                            fprintf(stdout, "�v�nement non trait� : %d\n",event.type);
                    }

                    fprintf(stdout, "\n");
                }

                // On a trait� les �v�nements, on peut continuer le jeu
            }


            SDL_DestroyWindow(pWindow);
        }
        else
        {
            fprintf(stderr,"Erreur de cr�ation de la fen�tre: %s\n",SDL_GetError());
        }
    }

    SDL_Quit();
}
