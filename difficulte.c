#include "bibliotheque.h"
#include "fonctions.h"

/*CHOIX DE LA DIFFICULTE*/

int difficulte(SDL_Surface *fenetre, SDL_Surface *imagebg, SDL_Rect positionFond, TTF_Font *police){

    SDL_Surface *txt_Titre=NULL, *txt_Fac=NULL, *txt_Moy=NULL, *txt_Diff=NULL,  *txt_Menu=NULL, *txt_Multi;
    SDL_Surface *rect_Titre=NULL, *rect_Fac=NULL, *rect_Moy=NULL, *rect_Diff=NULL, *rect_Menu=NULL, *rect_Multi;

    SDL_Rect positionRec_Titre, positionRec_Fac, positionRec_Moy, positionRec_Diff, positionRec_Menu, positionRec_Multi;
    SDL_Rect positionTxt_Titre, positionTxt_Fac, positionTxt_Moy, positionTxt_Diff, positionTxt_Menu, positionTxt_Multi;

    SDL_Color couleurNoire = {0,0,0};

    /*Declaration de la variable d'évènements*/
    SDL_Event evenement;
    int boucle  =1;
    int renvoi  =1;
    int Reclongueur =250;
    int Rechauteur  =60;

    //Chargement de la police
    TTF_SetFontStyle(police,TTF_STYLE_NORMAL);//, TTF_STYLE_ITALIC | TTF_STYLE_UNDERLINE);

    txt_Titre   = TTF_RenderText_Blended(police, "DIFFICULTE", couleurNoire);
    txt_Fac     = TTF_RenderText_Blended(police, "FACILE", couleurNoire);
    txt_Moy     = TTF_RenderText_Blended(police, "NORMAL", couleurNoire);
    txt_Diff    = TTF_RenderText_Blended(police, "DIFFICILE", couleurNoire);
    txt_Multi   = TTF_RenderText_Blended(police, "Multijoueur", couleurNoire);
    txt_Menu    = TTF_RenderText_Blended(police, "RETOUR AU MENU", couleurNoire);

    positionRec_Titre.x = 200;
    positionRec_Titre.y = 0;

    positionRec_Fac.x   = 200;
    positionRec_Fac.y   = 100;

    positionRec_Moy.x   = 200;
    positionRec_Moy.y   = 200;

    positionRec_Diff.x  = 200;
    positionRec_Diff.y  = 300;

    positionRec_Multi.x  = 350;
    positionRec_Multi.y  = 400;

    positionRec_Menu.x  = 50;
    positionRec_Menu.y  = 400;


    positionTxt_Titre.x = positionRec_Titre.x+(Reclongueur/5);
    positionTxt_Titre.y = positionRec_Titre.y+(Rechauteur/4);

    positionTxt_Fac.x   = positionRec_Fac.x+(Reclongueur/4);
    positionTxt_Fac.y   = positionRec_Fac.y+(Rechauteur/4);

    positionTxt_Moy.x   = positionRec_Moy.x+(Reclongueur/4);
    positionTxt_Moy.y   = positionRec_Moy.y+(Rechauteur/4);

    positionTxt_Diff.x  = positionRec_Diff.x+(Reclongueur/4);
    positionTxt_Diff.y  = positionRec_Diff.y+(Rechauteur/4);

    positionTxt_Multi.x  = positionRec_Multi.x+(Reclongueur/4);
    positionTxt_Multi.y  = positionRec_Multi.y+(Rechauteur/4);

    positionTxt_Menu.x  = positionRec_Menu.x+(Reclongueur/10);
    positionTxt_Menu.y  = positionRec_Menu.y+(Rechauteur/4);


    //Caractéristiques des élèments "rectangles"
    rect_Titre  = SDL_CreateRGBSurface(SDL_HWSURFACE, Reclongueur, Rechauteur, 32, 0, 0, 0, 0);
    rect_Fac    = SDL_CreateRGBSurface(SDL_HWSURFACE, Reclongueur, Rechauteur, 32, 0, 0, 0, 0);
    rect_Moy    = SDL_CreateRGBSurface(SDL_HWSURFACE, Reclongueur, Rechauteur, 32, 0, 0, 0, 0);
    rect_Diff   = SDL_CreateRGBSurface(SDL_HWSURFACE, Reclongueur, Rechauteur, 32, 0, 0, 0, 0);
    rect_Multi  = SDL_CreateRGBSurface(SDL_HWSURFACE, Reclongueur, Rechauteur, 32, 0, 0, 0, 0);
    rect_Menu   = SDL_CreateRGBSurface(SDL_HWSURFACE, Reclongueur, Rechauteur, 32, 0, 0, 0, 0);


     while(boucle){

        SDL_WaitEvent(&evenement); // Récupération de l'évènement
        switch(evenement.type){//Type d'évènement

            case SDL_QUIT: // Arrêt du programme
                return EXIT_SUCCESS;
                break;

            case SDL_MOUSEBUTTONUP: // Clic souris
                switch(evenement.button.button){ //Analyse de l'équipement de la souris

                    case SDL_BUTTON_LEFT:
                        if(interieurClic(evenement,positionRec_Fac, Reclongueur, Rechauteur)){
                            boucle=0;
                            renvoi=21;
                        }
                        if(interieurClic(evenement,positionRec_Moy, Reclongueur, Rechauteur)){
                            boucle=0;
                            renvoi=22;
                        }
                        if(interieurClic(evenement,positionRec_Diff, Reclongueur, Rechauteur)){
                            boucle=0;
                            renvoi=23;
                        }
                        if(interieurClic(evenement,positionRec_Multi, Reclongueur, Rechauteur)){
                            boucle=0;
                            renvoi=24;
                        }
                        if(interieurClic(evenement,positionRec_Menu, Reclongueur, Rechauteur)){
                            boucle=0;
                            renvoi=1;
                        }
                        break;
                }
                break;

            case SDL_MOUSEMOTION:
                //Facile
                if(interieurMove(evenement, positionRec_Fac, Reclongueur, Rechauteur)){
                    SDL_FillRect(rect_Fac, NULL, SDL_MapRGB(fenetre->format, 255, 255,255));
                   }

                //Moyen
                if(interieurMove(evenement, positionRec_Moy, Reclongueur, Rechauteur)){
                    SDL_FillRect(rect_Moy, NULL, SDL_MapRGB(fenetre->format, 255, 255,255));
                   }

                //Difficile
                if(interieurMove(evenement, positionRec_Diff, Reclongueur, Rechauteur)){
                    SDL_FillRect(rect_Diff, NULL, SDL_MapRGB(fenetre->format, 255, 255,255));
                   }

                //Multijoueur
                if(interieurMove(evenement, positionRec_Multi, Reclongueur, Rechauteur)){
                    SDL_FillRect(rect_Multi, NULL, SDL_MapRGB(fenetre->format, 255, 255,255));
                   }

                //Menu
                if(interieurMove(evenement, positionRec_Menu, Reclongueur, Rechauteur)){
                    SDL_FillRect(rect_Menu, NULL, SDL_MapRGB(fenetre->format, 255, 255, 255));
                   }

                break;
        }

        /*Affichage des élèments + background à chaque tour de boucle*/
            //Coloration du fond

                SDL_FillRect(fenetre, NULL, SDL_MapRGB(fenetre->format, 0, 0, 0));
                SDL_BlitSurface(imagebg, NULL, fenetre, &positionFond);

                //Application de l'élèment sur le background

                SDL_BlitSurface(rect_Titre, NULL, fenetre, &positionRec_Titre);
                SDL_BlitSurface(rect_Fac, NULL, fenetre, &positionRec_Fac);
                SDL_BlitSurface(rect_Moy, NULL, fenetre, &positionRec_Moy);
                SDL_BlitSurface(rect_Multi, NULL, fenetre, &positionRec_Multi);
                SDL_BlitSurface(rect_Diff, NULL, fenetre, &positionRec_Diff);
                SDL_BlitSurface(rect_Menu, NULL, fenetre, &positionRec_Menu);

                SDL_FillRect(rect_Titre, NULL, SDL_MapRGB(fenetre->format, 102, 204, 255));
                SDL_FillRect(rect_Fac, NULL, SDL_MapRGB(fenetre->format, 17, 206, 112));
                SDL_FillRect(rect_Moy, NULL, SDL_MapRGB(fenetre->format, 255, 153, 0));
                SDL_FillRect(rect_Diff, NULL, SDL_MapRGB(fenetre->format, 255, 0, 0));
                SDL_FillRect(rect_Multi, NULL, SDL_MapRGB(fenetre->format, 255, 255, 0));
                SDL_FillRect(rect_Menu, NULL, SDL_MapRGB(fenetre->format, 102, 204, 255));

            //Caractéristiques du texte
                SDL_BlitSurface(txt_Titre, NULL, fenetre, &positionTxt_Titre);
                SDL_BlitSurface(txt_Fac, NULL, fenetre, &positionTxt_Fac);
                SDL_BlitSurface(txt_Moy, NULL, fenetre, &positionTxt_Moy);
                SDL_BlitSurface(txt_Diff, NULL, fenetre, &positionTxt_Diff);
                SDL_BlitSurface(txt_Multi, NULL, fenetre, &positionTxt_Multi);
                SDL_BlitSurface(txt_Menu, NULL, fenetre, &positionTxt_Menu);

            /*Mise à jour de la fenêtre avec les élèments modifiés*/
                SDL_Flip(fenetre);
    }
    SDL_FreeSurface(rect_Titre);
    SDL_FreeSurface(rect_Fac);
    SDL_FreeSurface(rect_Moy);
    SDL_FreeSurface(rect_Diff);
    SDL_FreeSurface(rect_Menu);
    SDL_FreeSurface(rect_Multi);
    SDL_FreeSurface(txt_Titre);
    SDL_FreeSurface(txt_Fac);
    SDL_FreeSurface(txt_Moy);
    SDL_FreeSurface(txt_Diff);
    SDL_FreeSurface(txt_Multi);
    SDL_FreeSurface(txt_Menu);

    return renvoi;
}
