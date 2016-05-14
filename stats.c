#include "bibliotheque.h"
#include "fonctions.h"
#include "strucStats.h"

int stats(SDL_Surface *fenetre, SDL_Surface *imagebg, SDL_Rect positionFond, TTF_Font *police, int renvoi){

    SDL_Surface *txt_Titre=NULL, *txt_Score=NULL, *txt_Quit=NULL, *txt_Menu=NULL;
    SDL_Surface *rect_Titre=NULL, *rect_Score=NULL, *rect_Quit=NULL, *rect_Menu=NULL;

    SDL_Rect positionRect_Titre,positionRect_Score,positionRect_Quit,positionRect_Menu;
    SDL_Rect positionTxt_Titre, positionTxt_Score, positionTxt_Quit, positionTxt_Menu;

    SDL_Color couleurNoire = {0,0,0};

    /*Declaration de la variable d'évènements*/

    SDL_Event evenement;
    int boucle = 1;
    int Reclongueur=250, Rechauteur=60;


    /*GESTION DU CSV*/

    FILE *CSV;
    char ligne[100];
    char *ssChaine;
    int i=0;
    char elementTab[200];

    //Tableau de structure pour 10 questions
    score tab[10];
    int nb_question=0;

    CSV = fopen("stats.csv","rt");
    while(fgets(ligne,40,CSV) != NULL){
        //Explosion de la ligne avec le ;
        ssChaine = strtok(ligne,";");
        for(i=0;i<2;i++){ // score, bareme
            sscanf(ssChaine,"%s",elementTab);
            switch(i){
                case 0:
                    strcpy(tab[nb_question].note, elementTab);break;
                case 1:
                    strcpy(tab[nb_question].bareme, elementTab);break;
            }
            ssChaine = strtok(NULL, ";");
        }
    }

    fclose(CSV);

    /*Chargement de la police*/

    TTF_SetFontStyle(police,TTF_STYLE_NORMAL);//, TTF_STYLE_ITALIC | TTF_STYLE_UNDERLINE);

    txt_Titre   = TTF_RenderText_Blended(police, "RESULTAT", couleurNoire);
    txt_Score   = TTF_RenderText_Blended(police, tab[nb_question].note, couleurNoire);
    txt_Menu    = TTF_RenderText_Blended(police, "RETOUR AU MENU", couleurNoire);
    txt_Quit    = TTF_RenderText_Blended(police, "QUITTER", couleurNoire);

    positionRect_Titre.x = 200;
    positionRect_Titre.y = 0;

    positionRect_Score.x = 200;
    positionRect_Score.y = 100;

    positionRect_Menu.x = 200;
    positionRect_Menu.y = 300;

    positionRect_Quit.x = 200;
    positionRect_Quit.y = 400;

    positionTxt_Titre.x=positionRect_Titre.x+(Reclongueur/3);
    positionTxt_Titre.y=positionRect_Titre.y+(Rechauteur/4);

    positionTxt_Score.x=positionRect_Score.x+(Reclongueur/4);
    positionTxt_Score.y=positionRect_Score.y+(Rechauteur/4);

    positionTxt_Menu.x=positionRect_Menu.x+(Reclongueur/10);
    positionTxt_Menu.y=positionRect_Menu.y+(Rechauteur/4);

    positionTxt_Quit.x=positionRect_Quit.x+(Reclongueur/4);
    positionTxt_Quit.y=positionRect_Quit.y+(Rechauteur/4);

    //Caractéristiques des élèments "rectangles"

    rect_Titre  = SDL_CreateRGBSurface(SDL_HWSURFACE, Reclongueur, Rechauteur, 32, 0, 0, 0, 0);
    rect_Score  = SDL_CreateRGBSurface(SDL_HWSURFACE, Reclongueur, Rechauteur, 32, 0, 0, 0, 0);
    rect_Menu   = SDL_CreateRGBSurface(SDL_HWSURFACE, Reclongueur, Rechauteur, 32, 0, 0, 0, 0);
    rect_Quit   = SDL_CreateRGBSurface(SDL_HWSURFACE, Reclongueur, Rechauteur, 32, 0, 0, 0, 0);

     while(boucle){

        SDL_WaitEvent(&evenement); // Récupération de l'évènement
        switch(evenement.type){//Type d'évènement

            case SDL_QUIT: // Arrêt du programme
                boucle = 0;
                break;

            case SDL_MOUSEBUTTONUP: // Clic souris
                switch(evenement.button.button){ //Analyse de l'équipement de la souris
                    case SDL_BUTTON_LEFT:

                        //Menu
                        if(interieurClic(evenement,positionRect_Menu, Reclongueur, Rechauteur)){
                            boucle=0;
                            renvoi=1;
                        }

                        //Arret
                        if(interieurClic(evenement,positionRect_Quit, Reclongueur, Rechauteur)){
                            boucle=0;
                            renvoi=0;
                        }

                        break;
                }
                break;

            case SDL_MOUSEMOTION:
                //Score
                if(interieurMove(evenement, positionRect_Score, Reclongueur, Rechauteur)){
                    SDL_FillRect(rect_Score, NULL, SDL_MapRGB(fenetre->format, 255, 206, 112));
                }

                //Menu
                if(interieurMove(evenement, positionRect_Menu, Reclongueur, Rechauteur)){
                    SDL_FillRect(rect_Menu, NULL, SDL_MapRGB(fenetre->format, 255, 206, 112));
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
                SDL_BlitSurface(rect_Titre, NULL, fenetre, &positionRect_Titre);
                SDL_BlitSurface(rect_Score, NULL, fenetre, &positionRect_Score);
                SDL_BlitSurface(rect_Menu, NULL, fenetre, &positionRect_Menu);
                SDL_BlitSurface(rect_Quit, NULL, fenetre, &positionRect_Quit);

                SDL_FillRect(rect_Titre, NULL, SDL_MapRGB(fenetre->format, 17, 206, 112));
                SDL_FillRect(rect_Score, NULL, SDL_MapRGB(fenetre->format, 17, 206, 112));
                SDL_FillRect(rect_Quit, NULL, SDL_MapRGB(fenetre->format, 17, 206, 112));
                SDL_FillRect(rect_Menu, NULL, SDL_MapRGB(fenetre->format, 17, 206, 112));

            //Caractéristiques du texte
                SDL_BlitSurface(txt_Titre, NULL, fenetre, &positionTxt_Titre);
                SDL_BlitSurface(txt_Score, NULL, fenetre, &positionTxt_Score);
                SDL_BlitSurface(txt_Menu, NULL, fenetre, &positionTxt_Menu);
                SDL_BlitSurface(txt_Quit, NULL, fenetre, &positionTxt_Quit);

            /*Mise à jour de la fenêtre avec les élèments modifiés*/
                SDL_Flip(fenetre);
    }
    SDL_FreeSurface(rect_Titre);
    SDL_FreeSurface(rect_Score);
    SDL_FreeSurface(rect_Quit);
    SDL_FreeSurface(rect_Menu);
    SDL_FreeSurface(txt_Titre);
    SDL_FreeSurface(txt_Score);
    SDL_FreeSurface(txt_Quit);
    SDL_FreeSurface(txt_Menu);

    return renvoi;
}
