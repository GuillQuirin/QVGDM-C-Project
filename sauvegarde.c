#include "bibliotheque.h"
#include "fonctions.h"

/*CHARGEMENT D'UNE PARTIE*/

int sauvegarde(SDL_Surface *fenetre, SDL_Surface *imagebg, SDL_Rect positionFond,  TTF_Font *police){

    SDL_Surface *txt_titre=NULL, *txt_sv1=NULL, *txt_sv2=NULL, *txt_sv3=NULL, *txt_back=NULL;
    SDL_Surface *rect_titre=NULL, *rect_sv1=NULL, *rect_sv2=NULL, *rect_sv3=NULL, *rect_back=NULL;

    SDL_Rect positionRect_Titre,positionRect_SV1,positionRect_SV2,positionRect_SV3, positionRect_Back;
    SDL_Rect positionTxt_Titre, positionTxt_SV1, positionTxt_SV2, positionTxt_SV3, positionTxt_Back;

    SDL_Color couleurNoire = {0,0,0};

    /*Declaration de la variable d'évènements*/
    SDL_Event evenement;
    int boucle  = 1;
    int renvoi  = 1;
    int Reclongueur=300, Rechauteur=60;

    //Chargement de la police
    TTF_SetFontStyle(police,TTF_STYLE_NORMAL);//, TTF_STYLE_ITALIC | TTF_STYLE_UNDERLINE);

    txt_titre   = TTF_RenderText_Blended(police, "STATISTIQUES", couleurNoire);
    txt_sv1     = TTF_RenderText_Blended(police, "SAUVEGARDE 1", couleurNoire);
    txt_sv2     = TTF_RenderText_Blended(police, "SAUVEGARDE 2", couleurNoire);
    txt_sv3     = TTF_RenderText_Blended(police, "SAUVEGARDE 3", couleurNoire);
    txt_back    = TTF_RenderText_Blended(police, "RETOUR AU MENU", couleurNoire);

    positionRect_Titre.x = 150;
    positionRect_Titre.y = 0;

    positionRect_SV1.x = 200;
    positionRect_SV1.y = 100;

    positionRect_SV2.x = 200;
    positionRect_SV2.y = 200;

    positionRect_SV3.x = 200;
    positionRect_SV3.y = 300;

    positionRect_Back.x = 200;
    positionRect_Back.y = 400;

    positionTxt_Titre.x =   positionRect_Titre.x+(Reclongueur/3);
    positionTxt_Titre.y =   positionRect_Titre.y+(Rechauteur/4);

    positionTxt_SV1.x   =   positionRect_SV1.x+(Reclongueur/4);
    positionTxt_SV1.y   =   positionRect_SV1.y+(Rechauteur/4);

    positionTxt_SV2.x   =   positionRect_SV2.x+(Reclongueur/4);
    positionTxt_SV2.y   =   positionRect_SV2.y+(Rechauteur/4);

    positionTxt_SV3.x   =   positionRect_SV3.x+(Reclongueur/4);
    positionTxt_SV3.y   =   positionRect_SV3.y+(Rechauteur/4);

    positionTxt_Back.x  =   positionRect_Back.x+(Reclongueur/5);
    positionTxt_Back.y  =   positionRect_Back.y+(Rechauteur/4);

    //Caractéristiques des élèments "rectangles"

    rect_titre  =   SDL_CreateRGBSurface(SDL_HWSURFACE, Reclongueur+(Reclongueur/4), Rechauteur, 32, 0, 0, 0, 0);
    rect_sv1    =   SDL_CreateRGBSurface(SDL_HWSURFACE, Reclongueur, Rechauteur, 32, 0, 0, 0, 0);
    rect_sv2    =   SDL_CreateRGBSurface(SDL_HWSURFACE, Reclongueur, Rechauteur, 32, 0, 0, 0, 0);
    rect_sv3    =   SDL_CreateRGBSurface(SDL_HWSURFACE, Reclongueur, Rechauteur, 32, 0, 0, 0, 0);
    rect_back   =   SDL_CreateRGBSurface(SDL_HWSURFACE, Reclongueur, Rechauteur, 32, 0, 0, 0, 0);

     while(boucle){

        SDL_WaitEvent(&evenement); // Récupération de l'évènement
        switch(evenement.type){//Type d'évènement

            case SDL_QUIT: // Arrêt du programme
                boucle = 0;
                break;

            case SDL_MOUSEBUTTONUP: // Clic souris
                switch(evenement.button.button){ //Analyse de l'équipement de la souris
                    case SDL_BUTTON_LEFT:
                        /*SAVE 1*/
                        if(interieurClic(evenement,positionRect_SV1, Reclongueur, Rechauteur)){
                            boucle=0;
                            renvoi=31;
                        }

                        /*SAVE 2*/
                        if(interieurClic(evenement,positionRect_SV2, Reclongueur, Rechauteur)){
                            boucle=0;
                            renvoi=32;
                        }

                        /*SAVE 3*/
                        if(interieurClic(evenement,positionRect_SV3, Reclongueur, Rechauteur)){
                            boucle=0;
                            renvoi=33;
                        }

                        /*RETOUR MENU*/
                        if(interieurClic(evenement,positionRect_Back, Reclongueur, Rechauteur)){
                            boucle=0;
                            renvoi=1;
                        }

                        break;
                }
                break;
            case SDL_MOUSEMOTION:
                //Save1
                if(interieurMove(evenement, positionRect_SV1, Reclongueur, Rechauteur)){
                    SDL_FillRect(rect_sv1, NULL, SDL_MapRGB(fenetre->format, 255, 206, 112));
                   }

                //Save 2
                if(interieurMove(evenement, positionRect_SV2, Reclongueur, Rechauteur)){
                    SDL_FillRect(rect_sv2, NULL, SDL_MapRGB(fenetre->format, 255, 206, 112));
                   }

                //Save 3
                if(interieurMove(evenement, positionRect_SV3, Reclongueur, Rechauteur)){
                    SDL_FillRect(rect_sv3, NULL, SDL_MapRGB(fenetre->format, 255, 206, 112));
                   }

                //Retour menu
                if(interieurMove(evenement, positionRect_Back, Reclongueur, Rechauteur)){
                    SDL_FillRect(rect_back, NULL, SDL_MapRGB(fenetre->format, 255, 206, 112));
                   }
                break;
        }

        /*Affichage des élèments + background à chaque tour de boucle*/
            //Coloration du fond

                SDL_FillRect(fenetre, NULL, SDL_MapRGB(fenetre->format, 0, 0, 0));
                SDL_BlitSurface(imagebg, NULL, fenetre, &positionFond);

                //Application de l'élèment sur le background

                SDL_BlitSurface(rect_titre, NULL, fenetre, &positionRect_Titre);
                SDL_BlitSurface(rect_sv1, NULL, fenetre, &positionRect_SV1);
                SDL_BlitSurface(rect_sv2, NULL, fenetre, &positionRect_SV2);
                SDL_BlitSurface(rect_sv3, NULL, fenetre, &positionRect_SV3);
                SDL_BlitSurface(rect_back, NULL, fenetre, &positionRect_Back);

                SDL_FillRect(rect_titre, NULL, SDL_MapRGB(fenetre->format, 17, 206, 112));
                SDL_FillRect(rect_sv1, NULL, SDL_MapRGB(fenetre->format, 17, 206, 112));
                SDL_FillRect(rect_sv2, NULL, SDL_MapRGB(fenetre->format, 17, 206, 112));
                SDL_FillRect(rect_sv3, NULL, SDL_MapRGB(fenetre->format, 17, 206, 112));
                SDL_FillRect(rect_back, NULL, SDL_MapRGB(fenetre->format, 17, 206, 112));

            //Caractéristiques du texte

                SDL_BlitSurface(txt_titre, NULL, fenetre, &positionTxt_Titre);
                SDL_BlitSurface(txt_sv1, NULL, fenetre, &positionTxt_SV1);
                SDL_BlitSurface(txt_sv2, NULL, fenetre, &positionTxt_SV2);
                SDL_BlitSurface(txt_sv3, NULL, fenetre, &positionTxt_SV3);
                SDL_BlitSurface(txt_back, NULL, fenetre, &positionTxt_Back);

            /*Mise à jour de la fenêtre avec les élèments modifiés*/
                SDL_Flip(fenetre);
    }
    SDL_FreeSurface(rect_titre);
    SDL_FreeSurface(rect_sv1);
    SDL_FreeSurface(rect_sv2);
    SDL_FreeSurface(rect_sv3);
    SDL_FreeSurface(rect_back);

    SDL_FreeSurface(txt_titre);
    SDL_FreeSurface(txt_sv1);
    SDL_FreeSurface(txt_sv2);
    SDL_FreeSurface(txt_sv3);
    SDL_FreeSurface(txt_back);

    return renvoi;
}
