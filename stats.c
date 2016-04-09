#include "bibliotheque.h"
#include "fonctions.h"

int stats(SDL_Surface *fenetre, SDL_Surface *imagebg, SDL_Rect positionFond, TTF_Font *police, int renvoi){
    SDL_Surface *texte1=NULL, *texte2=NULL, *texte3=NULL, *texte4=NULL;
    SDL_Surface *rectangle1=NULL, *rectangle2=NULL, *rectangle3=NULL, *rectangle4=NULL;

    SDL_Rect positionRect1,positionRect2,positionRect3,positionRect4;
    SDL_Rect positionTexte1, positionTexte2, positionTexte3, positionTexte4;

    SDL_Color couleurNoire = {0,0,0};

    /*Declaration de la variable d'évènements*/
    SDL_Event evenement;
    int boucle = 1;
    int Reclongueur=250, Rechauteur=60;

    //Chargement de la police
    TTF_SetFontStyle(police,TTF_STYLE_NORMAL);//, TTF_STYLE_ITALIC | TTF_STYLE_UNDERLINE);
    texte1 = TTF_RenderText_Blended(police, "RESULTAT", couleurNoire);
    texte2 = TTF_RenderText_Blended(police, "SCORE", couleurNoire);
    texte3 = TTF_RenderText_Blended(police, "SAVE & QUIT", couleurNoire);
    texte4 = TTF_RenderText_Blended(police, "RETOUR AU MENU", couleurNoire);

    positionRect1.x = 200;
    positionRect1.y = 0;

    positionRect2.x = 200;
    positionRect2.y = 100;

    positionRect3.x = 200;
    positionRect3.y = 300;

    positionRect4.x = 200;
    positionRect4.y = 400;

    positionTexte1.x=positionRect1.x+(Reclongueur/3);
    positionTexte1.y=positionRect1.y+(Rechauteur/4);

    positionTexte2.x=positionRect2.x+(Reclongueur/4);
    positionTexte2.y=positionRect2.y+(Rechauteur/4);

    positionTexte3.x=positionRect3.x+(Reclongueur/4);
    positionTexte3.y=positionRect3.y+(Rechauteur/4);

    positionTexte4.x=positionRect4.x+(Reclongueur/4);
    positionTexte4.y=positionRect4.y+(Rechauteur/4);

    //Caractéristiques des élèments "rectangles"
    rectangle1 = SDL_CreateRGBSurface(SDL_HWSURFACE, Reclongueur, Rechauteur, 32, 0, 0, 0, 0);
    rectangle2 = SDL_CreateRGBSurface(SDL_HWSURFACE, Reclongueur, Rechauteur, 32, 0, 0, 0, 0);
    rectangle3 = SDL_CreateRGBSurface(SDL_HWSURFACE, Reclongueur, Rechauteur, 32, 0, 0, 0, 0);
    rectangle4 = SDL_CreateRGBSurface(SDL_HWSURFACE, Reclongueur, Rechauteur, 32, 0, 0, 0, 0);

     while(boucle){

        SDL_WaitEvent(&evenement); // Récupération de l'évènement
        switch(evenement.type){//Type d'évènement
            case SDL_QUIT: // Arrêt du programme
                boucle = 0;
                break;
            case SDL_MOUSEBUTTONUP: // Clic souris
                switch(evenement.button.button){ //Analyse de l'équipement de la souris
                    case SDL_BUTTON_LEFT:
                        if(interieurClic(evenement,positionRect3, Reclongueur, Rechauteur)){
                            boucle=0;renvoi=0;
                        }
                        if(interieurClic(evenement,positionRect4, Reclongueur, Rechauteur)){
                            boucle=0;renvoi=1;
                        }
                        break;
                }
                break;
            case SDL_MOUSEMOTION:
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
    SDL_FreeSurface(rectangle1);
    SDL_FreeSurface(rectangle2);
    SDL_FreeSurface(rectangle3);
    SDL_FreeSurface(rectangle4);
    SDL_FreeSurface(texte1);
    SDL_FreeSurface(texte2);
    SDL_FreeSurface(texte3);
    SDL_FreeSurface(texte4);

    return renvoi;
}
