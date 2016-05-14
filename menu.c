#include "bibliotheque.h"
#include "fonctions.h"

int menu(SDL_Surface *fenetre, SDL_Surface *imagebg, SDL_Rect positionFond,  TTF_Font *police){

        SDL_Surface *txt_Jouer=NULL, *txt_Stats=NULL, *txt_Opt=NULL, *txt_Quit=NULL;
        SDL_Surface *rect_Jouer=NULL, *rect_Stats=NULL, *rect_Opt=NULL, *rect_Quit=NULL;

        SDL_Rect positionRect_Jouer,positionRect_Stats,positionRect_Opt,positionRect_Quit;
        SDL_Rect positionTxt_Jouer, positionTxt_Stats, positionTxt_Opt, positionTxt_Quit;

        SDL_Color couleurNoire = {0,0,0};

        /*Declaration de la variable d'évènements*/
        SDL_Event evenement;
        int boucle = 1;
        int renvoi=1;
        int Reclongueur=250, Rechauteur=60;

        //Chargement de la police
        TTF_SetFontStyle(police,TTF_STYLE_NORMAL);//, TTF_STYLE_ITALIC | TTF_STYLE_UNDERLINE);

        txt_Jouer   = TTF_RenderText_Blended(police, "JOUER", couleurNoire);
        txt_Stats    = TTF_RenderText_Blended(police, "STATISTIQUES", couleurNoire);
        txt_Opt     = TTF_RenderText_Blended(police, "OPTIONS", couleurNoire);
        txt_Quit    = TTF_RenderText_Blended(police, "QUITTER", couleurNoire);

        positionRect_Jouer.x = 40;
        positionRect_Jouer.y = 300;

        positionRect_Stats.x  = 330;
        positionRect_Stats.y  = 300;

        positionRect_Opt.x   = 40;
        positionRect_Opt.y   = 400;

        positionRect_Quit.x  = 330;
        positionRect_Quit.y  = 400;

        positionTxt_Jouer.x = positionRect_Jouer.x+(Reclongueur/3);
        positionTxt_Jouer.y = positionRect_Jouer.y+(Rechauteur/4);

        positionTxt_Stats.x  = positionRect_Stats.x+(Reclongueur/5);
        positionTxt_Stats.y  = positionRect_Stats.y+(Rechauteur/4);

        positionTxt_Opt.x   = positionRect_Opt.x+(Reclongueur/4);
        positionTxt_Opt.y   = positionRect_Opt.y+(Rechauteur/4);

        positionTxt_Quit.x  = positionRect_Quit.x+(Reclongueur/4);
        positionTxt_Quit.y  = positionRect_Quit.y+(Rechauteur/4);

        //Caractéristiques des élèments

        rect_Jouer = SDL_CreateRGBSurface(SDL_HWSURFACE, Reclongueur, Rechauteur, 32, 0, 0, 0, 0);
        rect_Stats  = SDL_CreateRGBSurface(SDL_HWSURFACE, Reclongueur, Rechauteur, 32, 0, 0, 0, 0);
        rect_Opt   = SDL_CreateRGBSurface(SDL_HWSURFACE, Reclongueur, Rechauteur, 32, 0, 0, 0, 0);
        rect_Quit  = SDL_CreateRGBSurface(SDL_HWSURFACE, Reclongueur, Rechauteur, 32, 0, 0, 0, 0);

         while(boucle){

            SDL_WaitEvent(&evenement); // Récupération de l'évènement
            switch(evenement.type){//Type d'évènement

                case SDL_QUIT: // Arrêt du programme
                    boucle = 0;
                    renvoi=0;
                    break;

                case SDL_KEYDOWN: //Appui sur une touche
                    switch(evenement.key.keysym.sym){// Analyse de la touche

                        case SDLK_ESCAPE://Echap
                            boucle=0;
                            renvoi=0;
                            break;

                        default:
                            break;
                    }
                    break;

                case SDL_MOUSEBUTTONUP: // Clic souris
                    switch(evenement.button.button){ //Analyse de l'équipement de la souris

                        case SDL_BUTTON_LEFT:

                            /*JOUER - Choix difficulte*/
                            if(interieurClic(evenement,positionRect_Jouer, Reclongueur, Rechauteur)){
                                boucle=0;
                                renvoi=2;
                            }

                            /*STATS*/
                            if(interieurClic(evenement,positionRect_Stats, Reclongueur, Rechauteur)){
                                boucle=0;
                                renvoi=4;
                            }

                            /*OPTIONS*/
                            if(interieurClic(evenement,positionRect_Opt, Reclongueur, Rechauteur)){
                                boucle=0;
                                renvoi=5;
                            }

                            /*QUITTER*/
                            if(interieurClic(evenement,positionRect_Quit, Reclongueur, Rechauteur)){
                                boucle=0;
                                renvoi=0;
                            }
                            break;
                    }
                    break;
                case SDL_MOUSEMOTION:

                    //Jouer
                    if(interieurMove(evenement, positionRect_Jouer, Reclongueur, Rechauteur)){
                        SDL_FillRect(rect_Jouer, NULL, SDL_MapRGB(fenetre->format, 255, 206, 112));
                    }

                    //Stats
                    if(interieurMove(evenement, positionRect_Stats, Reclongueur, Rechauteur)){
                        SDL_FillRect(rect_Stats, NULL, SDL_MapRGB(fenetre->format, 255, 206, 112));
                    }

                    //Options
                    if(interieurMove(evenement, positionRect_Opt, Reclongueur, Rechauteur)){
                        SDL_FillRect(rect_Opt, NULL, SDL_MapRGB(fenetre->format, 255, 206, 112));
                    }

                    //Arret
                    if(interieurMove(evenement, positionRect_Quit, Reclongueur, Rechauteur)){
                        SDL_FillRect(rect_Quit, NULL, SDL_MapRGB(fenetre->format, 255, 206, 112));
                       }
                    break;
            }

            /*Affichage des élèments + background à chaque tour de boucle*/
                //Coloration du fond

                    SDL_FillRect(fenetre, NULL, SDL_MapRGB(fenetre->format, 0, 0, 0));
                    SDL_BlitSurface(imagebg, NULL, fenetre, &positionFond);

                    //Application de l'élèment sur le background

                    SDL_BlitSurface(rect_Jouer, NULL, fenetre, &positionRect_Jouer);
                    SDL_BlitSurface(rect_Stats, NULL, fenetre, &positionRect_Stats);
                    SDL_BlitSurface(rect_Opt, NULL, fenetre, &positionRect_Opt);
                    SDL_BlitSurface(rect_Quit, NULL, fenetre, &positionRect_Quit);

                    SDL_FillRect(rect_Jouer, NULL, SDL_MapRGB(fenetre->format, 17, 206, 112));
                    SDL_FillRect(rect_Stats, NULL, SDL_MapRGB(fenetre->format, 17, 206, 112));
                    SDL_FillRect(rect_Opt, NULL, SDL_MapRGB(fenetre->format, 17, 206, 112));
                    SDL_FillRect(rect_Quit, NULL, SDL_MapRGB(fenetre->format, 17, 206, 112));

                //Caractéristiques du texte

                    SDL_BlitSurface(txt_Jouer, NULL, fenetre, &positionTxt_Jouer);
                    SDL_BlitSurface(txt_Stats, NULL, fenetre, &positionTxt_Stats);
                    SDL_BlitSurface(txt_Opt, NULL, fenetre, &positionTxt_Opt);
                    SDL_BlitSurface(txt_Quit, NULL, fenetre, &positionTxt_Quit);

                /*Mise à jour de la fenêtre avec les élèments modifiés*/
                    SDL_Flip(fenetre);
        }
        SDL_FreeSurface(rect_Jouer);
        SDL_FreeSurface(rect_Stats);
        SDL_FreeSurface(rect_Opt);
        SDL_FreeSurface(rect_Quit);
        SDL_FreeSurface(txt_Jouer);
        SDL_FreeSurface(txt_Stats);
        SDL_FreeSurface(txt_Opt);
        SDL_FreeSurface(txt_Quit);

        return renvoi;
}

