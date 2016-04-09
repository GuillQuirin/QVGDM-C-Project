#include "bibliotheque.h"
#include "fonctions.h"

int option(SDL_Surface *fenetre, SDL_Surface *imagebg, SDL_Rect positionFond, TTF_Font *police, int renvoi){

    SDL_Surface *txt_Titre=NULL, *txt_Mus=NULL, *txt_Partie=NULL, *txt_Menu=NULL;
    SDL_Surface *rect_Titre=NULL, *rect_Mus=NULL, *rect_Partie=NULL, *rect_Menu=NULL;

    SDL_Rect position_Titre, position_Mus, position_Partie, position_Menu;
    SDL_Rect positionTxt_Titre, positionTxt_Mus, positionTxt_Partie, positionTxt_Menu;

    SDL_Color couleurNoire = {0,0,0};

    /*Declaration de la variable d'évènements*/
    SDL_Event evenement;
    int boucle = 1;
    int Reclongueur=250, Rechauteur=60;

    //Chargement de la police

    TTF_SetFontStyle(police,TTF_STYLE_NORMAL);//, TTF_STYLE_ITALIC | TTF_STYLE_UNDERLINE);

    txt_Titre   = TTF_RenderText_Blended(police, "OPTIONS", couleurNoire);
    txt_Mus     = TTF_RenderText_Blended(police, "MUSIQUE", couleurNoire);
    txt_Partie  = TTF_RenderText_Blended(police, "REPRENDRE LA PARTIE", couleurNoire);
    txt_Menu    = TTF_RenderText_Blended(police, "RETOUR AU MENU", couleurNoire);

    position_Titre.x  = 200;
    position_Titre.y  = 0;

    position_Mus.x    = 50;
    position_Mus.y    = 100;

    position_Partie.x = 200;
    position_Partie.y = 300;

    position_Menu.x   = 200;
    position_Menu.y   = 400;

    positionTxt_Titre.x  =   position_Titre.x+(Reclongueur/3);
    positionTxt_Titre.y  =   position_Titre.y+(Rechauteur/4);

    positionTxt_Mus.x    =   position_Mus.x+(Reclongueur/4);
    positionTxt_Mus.y    =   position_Mus.y+(Rechauteur/4);

    positionTxt_Partie.x =   position_Partie.x+(Reclongueur/4);
    positionTxt_Partie.y =   position_Partie.y+(Rechauteur/4);

    positionTxt_Menu.x   =   position_Menu.x+(Reclongueur/4);
    positionTxt_Menu.y   =   position_Menu.y+(Rechauteur/4);

    //Caractéristiques des élèments "rectangles"

    rect_Titre  = SDL_CreateRGBSurface(SDL_HWSURFACE, Reclongueur, Rechauteur, 32, 0, 0, 0, 0);
    rect_Mus    = SDL_CreateRGBSurface(SDL_HWSURFACE, Reclongueur, Rechauteur, 32, 0, 0, 0, 0);
    rect_Partie = SDL_CreateRGBSurface(SDL_HWSURFACE, Reclongueur, Rechauteur, 32, 0, 0, 0, 0);
    rect_Menu   = SDL_CreateRGBSurface(SDL_HWSURFACE, Reclongueur, Rechauteur, 32, 0, 0, 0, 0);

     while(boucle){

        SDL_WaitEvent(&evenement); // Récupération de l'évènement
        switch(evenement.type){//Type d'évènement

            case SDL_QUIT: // Arrêt du programme
                boucle = 0;
                break;

            case SDL_MOUSEBUTTONUP: // Clic souris
                switch(evenement.button.button){ //Analyse de l'équipement de la souris
                    case SDL_BUTTON_LEFT:
                        if(renvoi!=5){
                            //Retour Partie
                            if(interieurClic(evenement, position_Partie, Reclongueur, Rechauteur)){
                                boucle=0;
                                renvoi=31;
                            }
                        }

                        //Retour Menu
                        if(interieurClic(evenement, position_Menu, Reclongueur, Rechauteur)){
                            boucle=0;
                            renvoi=1;
                        }
                        break;
                }
                break;

            case SDL_MOUSEMOTION:
                //Musique
                if(interieurMove(evenement, position_Mus, Reclongueur, Rechauteur)){
                    SDL_FillRect(rect_Mus, NULL, SDL_MapRGB(fenetre->format, 255, 206, 112));
                   }

                //Partie
                if(renvoi!=5){
                    if(interieurMove(evenement, position_Partie, Reclongueur, Rechauteur)){
                        SDL_FillRect(rect_Partie, NULL, SDL_MapRGB(fenetre->format, 255, 206, 112));
                       }
                }

                //Menu
                if(interieurMove(evenement, position_Menu, Reclongueur, Rechauteur)){
                    SDL_FillRect(rect_Menu, NULL, SDL_MapRGB(fenetre->format, 255, 206, 112));
                   }
                break;
        }

        /*Affichage des élèments + background à chaque tour de boucle*/

            //Coloration du fond

                SDL_FillRect(fenetre, NULL, SDL_MapRGB(fenetre->format, 255, 255, 112));
                SDL_BlitSurface(imagebg, NULL, fenetre, &positionFond);

                //Application de l'élèment sur le background

                SDL_BlitSurface(rect_Titre, NULL, fenetre, &position_Titre);
                SDL_BlitSurface(rect_Mus, NULL, fenetre, &position_Mus);
                if(renvoi!=5)
                    SDL_BlitSurface(rect_Partie, NULL, fenetre, &position_Partie);
                SDL_BlitSurface(rect_Menu, NULL, fenetre, &position_Menu);

                SDL_FillRect(rect_Titre, NULL, SDL_MapRGB(fenetre->format, 17, 206, 112));
                SDL_FillRect(rect_Mus, NULL, SDL_MapRGB(fenetre->format, 17, 206, 112));
                SDL_FillRect(rect_Partie, NULL, SDL_MapRGB(fenetre->format, 17, 206, 112));
                SDL_FillRect(rect_Menu, NULL, SDL_MapRGB(fenetre->format, 17, 206, 112));

            //Caractéristiques du texte
                SDL_BlitSurface(txt_Titre, NULL, fenetre, &positionTxt_Titre);
                SDL_BlitSurface(txt_Mus, NULL, fenetre, &positionTxt_Mus);
                if(renvoi!=5)
                    SDL_BlitSurface(txt_Partie, NULL, fenetre, &positionTxt_Partie);
                SDL_BlitSurface(txt_Menu, NULL, fenetre, &positionTxt_Menu);

            /*Mise à jour de la fenêtre avec les élèments modifiés*/
                SDL_Flip(fenetre);
    }
    SDL_FreeSurface(rect_Titre);
    SDL_FreeSurface(rect_Mus);
    SDL_FreeSurface(rect_Partie);
    SDL_FreeSurface(rect_Menu);
    SDL_FreeSurface(txt_Titre);
    SDL_FreeSurface(txt_Mus);
    SDL_FreeSurface(txt_Partie);
    SDL_FreeSurface(txt_Menu);

    return renvoi;
}
