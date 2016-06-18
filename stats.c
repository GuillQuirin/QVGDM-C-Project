#include "bibliotheque.h"
#include "fonctions.h"
#include "strucStats.h"

int stats(SDL_Surface *fenetre, SDL_Surface *imagebg, SDL_Rect positionFond, TTF_Font *police, int renvoi){

    SDL_Surface *txt_Titre=NULL, *txt_Score=NULL, *txt_Score2=NULL, *txt_Quit=NULL, *txt_Menu=NULL;
    SDL_Surface *rect_Titre=NULL, *rect_Score=NULL, *rect_Score2=NULL, *rect_Quit=NULL, *rect_Menu=NULL;

    SDL_Rect positionRect_Titre,positionRect_Score,positionRect_Score2, positionRect_Quit,positionRect_Menu;
    SDL_Rect positionTxt_Titre, positionTxt_Score, positionTxt_Score2, positionTxt_Quit, positionTxt_Menu;

    SDL_Color couleurNoire = {0,0,0};

    /*Declaration de la variable d'évènements*/

    SDL_Event evenement;
    int boucle = 1;
    int Reclongueur=250, Rechauteur=60;


   /*GESTION DU CSV*/

    FILE *CSV;
    char elementTab[100];
    char resultat[20];

    //Tableau de structure pour 10 questions
    donnee tab[100];
    donnee tab1[100];
    char *mot;
    int nb_question=-1;
    int nb_question1=-1;

    CSV = fopen("stats.txt","r");

    if(CSV){
        while(( fgets(elementTab,100,CSV) ) != NULL ){
            nb_question++;

            mot = strtok(elementTab,",");
            tab[nb_question].note=atoi(mot);

            mot = strtok(NULL," ");
            tab[nb_question].bareme=atoi(mot);
        }
    }
    else{
        CSV = fopen("stats.txt","w");
        nb_question++;
        tab[nb_question].note=0;
        tab[nb_question].bareme=0;
    }
    fclose(CSV);

    if(renvoi==7){
        CSV = fopen("statsjoueur2.txt","r");

        if(CSV){
            while(( fgets(elementTab,100,CSV) ) != NULL ){
                nb_question1++;

                mot = strtok(elementTab,",");
                tab1[nb_question1].note=atoi(mot);

                mot = strtok(NULL," ");
                tab1[nb_question1].bareme=atoi(mot);
            }
        }
        else{
            CSV = fopen("statsjoueur2.txt","w");
            nb_question1++;
            tab1[nb_question1].note=0;
            tab1[nb_question1].bareme=0;
        }
        fclose(CSV);
    }

    /*Chargement de la police*/

    TTF_SetFontStyle(police,TTF_STYLE_NORMAL);//, TTF_STYLE_ITALIC | TTF_STYLE_UNDERLINE);

    txt_Titre   = TTF_RenderText_Blended(police, "RESULTAT", couleurNoire);
        sprintf(resultat, "JOUEUR 1 : %d / %d", tab[nb_question].note, tab[nb_question].bareme);
    txt_Score   = TTF_RenderText_Blended(police, resultat, couleurNoire);

        sprintf(resultat, "JOUEUR 2 : %d / %d", tab1[nb_question1].note, tab1[nb_question1].bareme);
    txt_Score2  = TTF_RenderText_Blended(police, resultat, couleurNoire);

    txt_Menu    = TTF_RenderText_Blended(police, "RETOUR AU MENU", couleurNoire);
    txt_Quit    = TTF_RenderText_Blended(police, "QUITTER", couleurNoire);

    positionRect_Titre.x = 200;
    positionRect_Titre.y = 0;

    positionRect_Score.x = 200;
    positionRect_Score.y = 100;

    positionRect_Score2.x = 200;
    positionRect_Score2.y = 200;

    positionRect_Menu.x = 200;
    positionRect_Menu.y = 300;

    positionRect_Quit.x = 200;
    positionRect_Quit.y = 400;

    positionTxt_Titre.x = positionRect_Titre.x+(Reclongueur/3);
    positionTxt_Titre.y = positionRect_Titre.y+(Rechauteur/4);

    positionTxt_Score.x = positionRect_Score.x+(Reclongueur/4);
    positionTxt_Score.y = positionRect_Score.y+(Rechauteur/4);

    positionTxt_Score2.x = positionRect_Score2.x+(Reclongueur/4);
    positionTxt_Score2.y = positionRect_Score2.y+(Rechauteur/4);

    positionTxt_Menu.x = positionRect_Menu.x+(Reclongueur/10);
    positionTxt_Menu.y = positionRect_Menu.y+(Rechauteur/4);

    positionTxt_Quit.x = positionRect_Quit.x+(Reclongueur/4);
    positionTxt_Quit.y = positionRect_Quit.y+(Rechauteur/4);

    //Caractéristiques des élèments "rectangles"

    rect_Titre  = SDL_CreateRGBSurface(SDL_HWSURFACE, Reclongueur, Rechauteur, 32, 0, 0, 0, 0);
    rect_Score  = SDL_CreateRGBSurface(SDL_HWSURFACE, Reclongueur, Rechauteur, 32, 0, 0, 0, 0);
    rect_Score2 = SDL_CreateRGBSurface(SDL_HWSURFACE, Reclongueur, Rechauteur, 32, 0, 0, 0, 0);
    rect_Menu   = SDL_CreateRGBSurface(SDL_HWSURFACE, Reclongueur, Rechauteur, 32, 0, 0, 0, 0);
    rect_Quit   = SDL_CreateRGBSurface(SDL_HWSURFACE, Reclongueur, Rechauteur, 32, 0, 0, 0, 0);

     while(boucle){

        SDL_WaitEvent(&evenement); // Récupération de l'évènement
        switch(evenement.type){//Type d'évènement

            case SDL_QUIT: // Arrêt du programme
                return EXIT_SUCCESS;
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
                if(renvoi==7)
                    SDL_BlitSurface(rect_Score2, NULL, fenetre, &positionRect_Score2);

                SDL_BlitSurface(rect_Menu, NULL, fenetre, &positionRect_Menu);
                SDL_BlitSurface(rect_Quit, NULL, fenetre, &positionRect_Quit);

                SDL_FillRect(rect_Titre, NULL, SDL_MapRGB(fenetre->format, 17, 206, 112));
                SDL_FillRect(rect_Score, NULL, SDL_MapRGB(fenetre->format, 17, 206, 112));
                if(renvoi==7)
                    SDL_FillRect(rect_Score2, NULL, SDL_MapRGB(fenetre->format, 17, 206, 112));

                SDL_FillRect(rect_Quit, NULL, SDL_MapRGB(fenetre->format, 17, 206, 112));
                SDL_FillRect(rect_Menu, NULL, SDL_MapRGB(fenetre->format, 17, 206, 112));

            //Caractéristiques du texte
                SDL_BlitSurface(txt_Titre, NULL, fenetre, &positionTxt_Titre);
                SDL_BlitSurface(txt_Score, NULL, fenetre, &positionTxt_Score);
                if(renvoi==7)
                    SDL_BlitSurface(txt_Score2, NULL, fenetre, &positionTxt_Score2);

                SDL_BlitSurface(txt_Menu, NULL, fenetre, &positionTxt_Menu);
                SDL_BlitSurface(txt_Quit, NULL, fenetre, &positionTxt_Quit);

            /*Mise à jour de la fenêtre avec les élèments modifiés*/
                SDL_Flip(fenetre);
    }
    SDL_FreeSurface(rect_Titre);
    SDL_FreeSurface(rect_Score);
    SDL_FreeSurface(rect_Score2);
    SDL_FreeSurface(rect_Quit);
    SDL_FreeSurface(rect_Menu);

    SDL_FreeSurface(txt_Titre);
    SDL_FreeSurface(txt_Score);
    SDL_FreeSurface(txt_Score2);
    SDL_FreeSurface(txt_Quit);
    SDL_FreeSurface(txt_Menu);

    return renvoi;
}
