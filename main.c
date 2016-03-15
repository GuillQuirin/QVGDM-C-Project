#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char *argv[])
{

    /* Initialisation simple */
    if(SDL_Init(SDL_INIT_VIDEO) != 0 ){
        fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return -1;
    }

    {
        /* Création de la fenêtre */
        SDL_Window* pWindow = NULL;
        pWindow = SDL_CreateWindow("Ma première application SDL2",SDL_WINDOWPOS_CENTERED,
                                                                  SDL_WINDOWPOS_CENTERED,
                                                                  640,
                                                                  480,
                                                                  SDL_WINDOW_SHOWN);
        //CreateWindow : Nom à afficher / pos en X / pos en Y /Largeur / Hauteur / options
        SDL_Renderer *pRenderer = SDL_CreateRenderer(pWindow,-1,SDL_RENDERER_ACCELERATED); // Création d'un SDL_Renderer utilisant l'accélération matérielle

        /*Image de Background*/
        if(pRenderer)
        {
            SDL_Surface *pSprite = SDL_LoadBMP("qui.bmp");
            if(pSprite)
            {
                SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer,pSprite); // Préparation du sprite
                if(pTexture)
                {
                    SDL_Rect dest = { 640/2 - pSprite->w/2,480/2 - pSprite->h/2, pSprite->w, pSprite->h};
                    SDL_RenderCopy(pRenderer,pTexture,NULL,&dest); // Copie du sprite grâce au SDL_Renderer

                    SDL_RenderPresent(pRenderer); // Affichage
                    //SDL_Delay(1000); // Attendre trois secondes, que l'utilisateur voit la fenêtre

                    SDL_DestroyTexture(pTexture); // Libération de la mémoire associée à la texture
                }
                else
                {
                    fprintf(stdout,"Échec de création de la texture (%s)\n",SDL_GetError());
                }

                SDL_FreeSurface(pSprite); // Libération de la ressource occupée par le sprite
            }
            else
            {
                fprintf(stdout,"Échec de chargement du sprite (%s)\n",SDL_GetError());
            }

            SDL_DestroyRenderer(pRenderer); // Libération de la mémoire du SDL_Renderer
        }
        else
        {
            fprintf(stdout,"Échec de création du renderer (%s)\n",SDL_GetError());
        }

        /*Gestion de la fenêtre*/
        if( pWindow )
        {
            //SDL_Delay(3000); /* Attendre trois secondes, que l'utilisateur voie la fenêtre */
            char cont = 1; // Détermine si on continue la boucle principale
            SDL_Event event;

            while ( cont != 0 )
            {
                while ( SDL_PollEvent(&event) )
                {
                    // Traitement de l'événement
                    switch (event.type) /* Quel événement avons-nous ? */
                    {
                        case SDL_KEYDOWN:
                            fprintf(stdout, "Un appuie sur une touche :\n");
                            fprintf(stdout, "\trépétition ? : %d\n",event.key.repeat);
                            fprintf(stdout, "\tscancode : %d\n",event.key.keysym.scancode);
                            fprintf(stdout, "\tkey : %d\n",event.key.keysym.sym);
                            if ( event.key.keysym.scancode == SDL_SCANCODE_ESCAPE )
                            {
                                cont = 0;
                            }
                            break;
                        case SDL_KEYUP:
                            fprintf(stdout, "Un relachement d'une touche :\n");
                            fprintf(stdout, "\trépétition ? : %d\n",event.key.repeat);
                            fprintf(stdout, "\tscancode : %d\n",event.key.keysym.scancode);
                            fprintf(stdout, "\tkey : %d\n",event.key.keysym.sym);
                            break;

                        case SDL_MOUSEMOTION:
                            fprintf(stdout, "Un déplacement de la souris :\n");
                            fprintf(stdout, "\tfenêtre : %d\n",event.motion.windowID);
                            fprintf(stdout, "\tsouris : %d\n",event.motion.which);
                            fprintf(stdout, "\tposition : %d;%d\n",event.motion.x,event.motion.y);
                            fprintf(stdout, "\tdelta : %d;%d\n",event.motion.xrel,event.motion.yrel);
                            break;
                        case SDL_MOUSEBUTTONUP:
                            fprintf(stdout, "Un relachement d'un bouton de la souris :\n");
                            fprintf(stdout, "\tfenêtre : %d\n",event.button.windowID);
                            fprintf(stdout, "\tsouris : %d\n",event.button.which);
                            fprintf(stdout, "\tbouton : %d\n",event.button.button);
    #if SDL_VERSION_ATLEAST(2,0,2)
                            fprintf(stdout, "\tclics : %d\n",event.button.clicks);
    #endif
                            fprintf(stdout, "\tposition : %d;%d\n",event.button.x,event.button.y);
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            fprintf(stdout, "Un appuie sur un bouton de la souris :\n");
                            fprintf(stdout, "\tfenêtre : %d\n",event.button.windowID);
                            fprintf(stdout, "\tsouris : %d\n",event.button.which);
                            fprintf(stdout, "\tbouton : %d\n",event.button.button);
    #if SDL_VERSION_ATLEAST(2,0,2)
                            fprintf(stdout, "\tclics : %d\n",event.button.clicks);
    #endif
                            fprintf(stdout, "\tposition : %d;%d\n",event.button.x,event.button.y);
                            break;

                        case SDL_WINDOWEVENT:
                            fprintf(stdout, "Un événement de fenêtre, sur la fenêtre : %d\n",event.window.windowID);
                            // En théorie, ici, il faudrait faire un autre test ou switch pour chaque type de cet événement
                            break;
                        default:
                            fprintf(stdout, "Événement non traité : %d\n",event.type);
                    }

                    fprintf(stdout, "\n");
                }

                // On a traité les événements, on peut continuer le jeu
            }


            SDL_DestroyWindow(pWindow);
        }
        else
        {
            fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
        }
    }

    SDL_Quit();
}
