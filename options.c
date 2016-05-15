#include "bibliotheque.h"
#include "fonctions.h"

int option(SDL_Surface *fenetre, SDL_Surface *imagebg, SDL_Rect positionFond, TTF_Font *police, int renvoi){

    SDL_Surface *txt_Titre=NULL, *txt_Mus=NULL, *txt_Menu=NULL, *txt_plus = NULL, *txt_moins = NULL, *txt_chiffre=NULL;
    SDL_Surface *rect_Titre=NULL, *rect_Mus=NULL, *rect_Menu=NULL, *rect_plus = NULL, *rect_moins = NULL, *rect_chiffre;

    SDL_Rect position_Titre, position_Mus, position_Menu, position_plus, position_moins, position_chiffre;
    SDL_Rect positionTxt_Titre, positionTxt_Mus, positionTxt_Menu, positionTxt_plus, positionTxt_moins, positionTxt_chiffre;

    SDL_Color couleurNoire = {0,0,0};

    /*Declaration de la variable d'évènements*/
    SDL_Event evenement;
    int boucle = 1;
    int Reclongueur=250, Rechauteur=60;

    //Volume de la musique
    int volume = Mix_VolumeMusic(-1);
    int modification=volume;
    char *chiffre =NULL;
    chiffre = (char *)malloc(2 * sizeof(char));
    //Chargement de la police
    TTF_SetFontStyle(police,TTF_STYLE_NORMAL);//, TTF_STYLE_ITALIC | TTF_STYLE_UNDERLINE);

    txt_Titre   = TTF_RenderText_Blended(police, "OPTIONS", couleurNoire);
    txt_Mus     = TTF_RenderText_Blended(police, "MUSIQUE", couleurNoire);
    txt_moins   = TTF_RenderText_Blended(police, "-", couleurNoire);
    txt_plus    = TTF_RenderText_Blended(police, "+", couleurNoire);
        sprintf(chiffre,"%d",volume);
    txt_chiffre = TTF_RenderText_Blended(police, chiffre, couleurNoire);
    txt_Menu    = TTF_RenderText_Blended(police, "RETOUR AU MENU", couleurNoire);

    position_Titre.x  = 200;
    position_Titre.y  = 0;

    position_Mus.x    = 50;
    position_Mus.y    = 100;

    position_moins.x = position_Mus.x + Reclongueur +10;
    position_moins.y = position_Mus.y;

    position_plus.x = position_moins.x + Reclongueur + 40;
    position_plus.y = position_Mus.y;

    position_chiffre.x = position_moins.x + (Reclongueur/2) ;
    position_chiffre.y = position_Mus.y;

    position_Menu.x   = 200;
    position_Menu.y   = 400;

    positionTxt_moins.x = position_moins.x +10;
    positionTxt_moins.y = position_moins.y;

    positionTxt_plus.x = position_plus.x + 10;
    positionTxt_plus.y = position_plus.y;

    positionTxt_chiffre.x = position_chiffre.x + 10;
    positionTxt_chiffre.y =  position_chiffre.y;

    positionTxt_Titre.x  =   position_Titre.x+(Reclongueur/3);
    positionTxt_Titre.y  =   position_Titre.y+(Rechauteur/4);

    positionTxt_Mus.x    =   position_Mus.x+(Reclongueur/4);
    positionTxt_Mus.y    =   position_Mus.y+(Rechauteur/4);

    positionTxt_Menu.x   =   position_Menu.x+(Reclongueur/10);
    positionTxt_Menu.y   =   position_Menu.y+(Rechauteur/4);

    //Caractéristiques des élèments "rectangles"

    rect_Titre  = SDL_CreateRGBSurface(SDL_HWSURFACE, Reclongueur, Rechauteur, 32, 0, 0, 0, 0);
    rect_Mus    = SDL_CreateRGBSurface(SDL_HWSURFACE, Reclongueur, Rechauteur, 32, 0, 0, 0, 0);
    rect_moins  = SDL_CreateRGBSurface(SDL_HWSURFACE, (Reclongueur/8), Rechauteur, 32, 0, 0, 0, 0);
    rect_plus   = SDL_CreateRGBSurface(SDL_HWSURFACE, (Reclongueur/8), Rechauteur, 32, 0, 0, 0, 0);
    rect_chiffre= SDL_CreateRGBSurface(SDL_HWSURFACE, (Reclongueur/4), Rechauteur, 32, 0, 0, 0, 0);
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
                        //Retour Menu
                        if(interieurClic(evenement, position_Menu, Reclongueur, Rechauteur)){
                            boucle=0;
                            renvoi=1;
                        }
                        //PLUS
                        if(interieurClic(evenement, position_plus, (Reclongueur/8), Rechauteur)){
                            volume+=10;
                            modification=Mix_VolumeMusic(volume);
                            volume=Mix_VolumeMusic(-1);
                            sprintf(chiffre,"%d",volume);
                            txt_chiffre = TTF_RenderText_Blended(police, chiffre, couleurNoire);
                        }
                        //MOINS
                        if(interieurClic(evenement, position_moins, (Reclongueur/8), Rechauteur)){
                            volume-=10;
                            modification=Mix_VolumeMusic(volume);
                            volume=Mix_VolumeMusic(-1);
                            sprintf(chiffre,"%d",volume);
                            txt_chiffre = TTF_RenderText_Blended(police, chiffre, couleurNoire);
                        }
                        break;
                }
                break;

            case SDL_MOUSEMOTION:
                //Menu
                if(interieurMove(evenement, position_Menu, Reclongueur, Rechauteur)){
                    SDL_FillRect(rect_Menu, NULL, SDL_MapRGB(fenetre->format, 255, 206, 112));
                }

                //PLUS
                if(interieurMove(evenement, position_plus, (Reclongueur/8), Rechauteur)){
                    SDL_FillRect(rect_plus, NULL, SDL_MapRGB(fenetre->format, 255, 206, 112));
                }

                //MOINS
                if(interieurMove(evenement, position_moins, (Reclongueur/8), Rechauteur)){
                    SDL_FillRect(rect_moins, NULL, SDL_MapRGB(fenetre->format, 255, 206, 112));
                }
                break;
        }

        /*Affichage des élèments + background à chaque tour de boucle*/

            //Coloration du fond

                SDL_FillRect(fenetre, NULL, SDL_MapRGB(fenetre->format, 0, 0, 0));
                SDL_BlitSurface(imagebg, NULL, fenetre, &positionFond);

                //Application de l'élèment sur le background

                SDL_BlitSurface(rect_Titre, NULL, fenetre, &position_Titre);
                SDL_BlitSurface(rect_Mus, NULL, fenetre, &position_Mus);
                SDL_BlitSurface(rect_moins, NULL, fenetre, &position_moins);
                SDL_BlitSurface(rect_plus, NULL, fenetre, &position_plus);
                SDL_BlitSurface(rect_chiffre, NULL, fenetre, &position_chiffre);
                SDL_BlitSurface(rect_Menu, NULL, fenetre, &position_Menu);

                SDL_FillRect(rect_Titre, NULL, SDL_MapRGB(fenetre->format, 17, 206, 112));
                SDL_FillRect(rect_Mus, NULL, SDL_MapRGB(fenetre->format, 17, 206, 112));
                SDL_FillRect(rect_moins, NULL, SDL_MapRGB(fenetre->format, 17, 206, 112));
                SDL_FillRect(rect_plus, NULL, SDL_MapRGB(fenetre->format, 17, 206, 112));
                SDL_FillRect(rect_chiffre, NULL, SDL_MapRGB(fenetre->format, 17, 206, 112));
                SDL_FillRect(rect_Menu, NULL, SDL_MapRGB(fenetre->format, 17, 206, 112));

            //Caractéristiques du texte
                SDL_BlitSurface(txt_Titre, NULL, fenetre, &positionTxt_Titre);
                SDL_BlitSurface(txt_Mus, NULL, fenetre, &positionTxt_Mus);
                SDL_BlitSurface(txt_moins, NULL, fenetre, &positionTxt_moins);
                SDL_BlitSurface(txt_plus, NULL, fenetre, &positionTxt_plus);
                SDL_BlitSurface(txt_chiffre, NULL, fenetre, &positionTxt_chiffre);
                SDL_BlitSurface(txt_Menu, NULL, fenetre, &positionTxt_Menu);

            /*Mise à jour de la fenêtre avec les élèments modifiés*/
                SDL_Flip(fenetre);
    }
    free(chiffre);

    SDL_FreeSurface(rect_Titre);
    SDL_FreeSurface(rect_Mus);
    SDL_FreeSurface(rect_moins);
    SDL_FreeSurface(rect_plus);
    SDL_FreeSurface(rect_chiffre);
    SDL_FreeSurface(rect_Menu);

    SDL_FreeSurface(txt_Titre);
    SDL_FreeSurface(txt_Mus);
    SDL_FreeSurface(txt_moins);
    SDL_FreeSurface(txt_plus);
    SDL_FreeSurface(txt_chiffre);
    SDL_FreeSurface(txt_Menu);

    return renvoi;
}
