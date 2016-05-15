#include "bibliotheque.h"
#include "fonctions.h"
#include "strucSave.h"

/*CHARGEMENT D'UNE PARTIE*/

int sauvegarde(SDL_Surface *fenetre, SDL_Surface *imagebg, SDL_Rect positionFond,  TTF_Font *police){

    SDL_Surface *txt_titre=NULL, *txt_totalPartie=NULL, *txt_nbPartie=NULL, *txt_reussite=NULL, *txt_percent=NULL, *txt_back=NULL;
    SDL_Surface *rect_titre=NULL, *rect_totalPartie=NULL, *rect_nbPartie=NULL, *rect_reussite=NULL, *rect_percent=NULL, *rect_back=NULL;

    SDL_Rect positionRect_Titre,positionRect_totalPartie,positionRect_nbPartie,positionRect_reussite, positionRect_percent, positionRect_Back;
    SDL_Rect positionTxt_Titre, positionTxt_totalPartie, positionTxt_nbPartie, positionTxt_reussite, positionTxt_percent, positionTxt_Back;

    SDL_Color couleurNoire = {0,0,0};

    /*Declaration de la variable d'évènements*/
    SDL_Event evenement;
    int boucle  = 1;
    int renvoi  = 1;
    int Reclongueur=300, Rechauteur=60;

    //Chargement de la police
    TTF_SetFontStyle(police,TTF_STYLE_NORMAL);//, TTF_STYLE_ITALIC | TTF_STYLE_UNDERLINE);


   /*GESTION DU CSV*/

    FILE *CSV;
    char elementTab[100];
    char resultat[20];

    //Tableau de structure pour 10 questions
    score tab[100];
    char *mot;
    char *percent;
    int nb_partie=0;
    CSV = fopen("stats.txt","r");
    while(( fgets(elementTab,100,CSV) ) != NULL ){
        nb_partie++;

        mot = strtok(elementTab,",");
        tab[nb_partie-1].note=atoi(mot);

        mot = strtok(NULL," ");
        tab[nb_partie-1].bareme=atoi(mot);

        //Pourcentage de bonnes réponses par ligne
        tab[nb_partie-1].moyenne = (tab[nb_partie-1].note * 100) / tab[nb_partie-1].bareme;
    }
    fclose(CSV);


    int i=0, moyenne = 0;
    for(i=0; i < nb_partie ;i++){
        moyenne += tab[i].moyenne;
    }
    moyenne /= nb_partie;

    sprintf(mot,"%d",nb_partie);
    txt_nbPartie    = TTF_RenderText_Blended(police, mot, couleurNoire);

    sprintf(mot,"%d",moyenne);
    txt_percent     = TTF_RenderText_Blended(police, mot, couleurNoire);

    txt_titre       = TTF_RenderText_Blended(police, "STATISTIQUES", couleurNoire);
    txt_totalPartie = TTF_RenderText_Blended(police, "Nombre total de parties:", couleurNoire);
    txt_reussite    = TTF_RenderText_Blended(police, "Taux de réussite:", couleurNoire);
    txt_back        = TTF_RenderText_Blended(police, "RETOUR AU MENU", couleurNoire);

    positionRect_Titre.x = 150;
    positionRect_Titre.y = 0;

    positionRect_totalPartie.x = 25;
    positionRect_totalPartie.y = 100;

    positionRect_nbPartie.x = Reclongueur + positionRect_totalPartie.x + 10;
    positionRect_nbPartie.y = positionRect_totalPartie.y;

    positionRect_reussite.x = 25;
    positionRect_reussite.y = 200;

    positionRect_percent.x = Reclongueur + positionRect_reussite.x + 10;
    positionRect_percent.y = positionRect_reussite.y;

    positionRect_Back.x = 200;
    positionRect_Back.y = 400;

    positionTxt_Titre.x =   positionRect_Titre.x+(Reclongueur/3);
    positionTxt_Titre.y =   positionRect_Titre.y+(Rechauteur/4);

    positionTxt_totalPartie.x   =   positionRect_totalPartie.x+(Reclongueur/10);
    positionTxt_totalPartie.y   =   positionRect_totalPartie.y+(Rechauteur/4);

    positionTxt_nbPartie.x = positionRect_nbPartie.x+(Reclongueur/10);
    positionTxt_nbPartie.y = positionTxt_totalPartie.y;

    positionTxt_reussite.x   =   positionRect_reussite.x+(Reclongueur/10);
    positionTxt_reussite.y   =   positionRect_reussite.y+(Rechauteur/4);

    positionTxt_percent.x = positionRect_percent.x+(Reclongueur/10);
    positionTxt_percent.y = positionRect_percent.y+(Rechauteur/4);

    positionTxt_Back.x  =   positionRect_Back.x+(Reclongueur/5);
    positionTxt_Back.y  =   positionRect_Back.y+(Rechauteur/4);

    //Caractéristiques des élèments "rectangles"

    rect_titre       =   SDL_CreateRGBSurface(SDL_HWSURFACE, Reclongueur+(Reclongueur/4), Rechauteur, 32, 0, 0, 0, 0);
    rect_totalPartie =   SDL_CreateRGBSurface(SDL_HWSURFACE, Reclongueur, Rechauteur, 32, 0, 0, 0, 0);
    rect_nbPartie    =   SDL_CreateRGBSurface(SDL_HWSURFACE, (Reclongueur/2), Rechauteur, 32, 0, 0, 0, 0);
    rect_reussite    =   SDL_CreateRGBSurface(SDL_HWSURFACE, Reclongueur, Rechauteur, 32, 0, 0, 0, 0);
    rect_percent     =   SDL_CreateRGBSurface(SDL_HWSURFACE, (Reclongueur/2), Rechauteur, 32, 0, 0, 0, 0);
    rect_back        =   SDL_CreateRGBSurface(SDL_HWSURFACE, Reclongueur, Rechauteur, 32, 0, 0, 0, 0);

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
                        if(interieurClic(evenement, positionRect_Back, Reclongueur, Rechauteur)){
                            boucle=0;
                            renvoi=1;
                        }
                        break;
                }
                break;

            case SDL_MOUSEMOTION:
                //Total parties
                if(interieurMove(evenement, positionRect_totalPartie, Reclongueur, Rechauteur)){
                    SDL_FillRect(rect_totalPartie, NULL, SDL_MapRGB(fenetre->format, 255, 206, 112));
                }

                //Pourcentage reussite
                if(interieurMove(evenement, positionRect_reussite, Reclongueur, Rechauteur)){
                    SDL_FillRect(rect_reussite, NULL, SDL_MapRGB(fenetre->format, 255, 206, 112));
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
                SDL_BlitSurface(rect_totalPartie, NULL, fenetre, &positionRect_totalPartie);
                SDL_BlitSurface(rect_nbPartie, NULL, fenetre, &positionRect_nbPartie);
                SDL_BlitSurface(rect_reussite, NULL, fenetre, &positionRect_reussite);
                SDL_BlitSurface(rect_percent, NULL, fenetre, &positionRect_percent);
                SDL_BlitSurface(rect_back, NULL, fenetre, &positionRect_Back);

                SDL_FillRect(rect_titre, NULL, SDL_MapRGB(fenetre->format, 17, 206, 112));
                SDL_FillRect(rect_totalPartie, NULL, SDL_MapRGB(fenetre->format, 17, 206, 112));
                SDL_FillRect(rect_nbPartie, NULL, SDL_MapRGB(fenetre->format, 17, 206, 112));
                SDL_FillRect(rect_reussite, NULL, SDL_MapRGB(fenetre->format, 17, 206, 112));
                SDL_FillRect(rect_percent, NULL, SDL_MapRGB(fenetre->format, 17, 206, 112));
                SDL_FillRect(rect_back, NULL, SDL_MapRGB(fenetre->format, 17, 206, 112));

            //Caractéristiques du texte

                SDL_BlitSurface(txt_titre, NULL, fenetre, &positionTxt_Titre);
                SDL_BlitSurface(txt_totalPartie, NULL, fenetre, &positionTxt_totalPartie);
                SDL_BlitSurface(txt_nbPartie, NULL, fenetre, &positionTxt_nbPartie);
                SDL_BlitSurface(txt_reussite, NULL, fenetre, &positionTxt_reussite);
                SDL_BlitSurface(txt_percent, NULL, fenetre, &positionTxt_percent);
                SDL_BlitSurface(txt_back, NULL, fenetre, &positionTxt_Back);

            /*Mise à jour de la fenêtre avec les élèments modifiés*/
                SDL_Flip(fenetre);
    }
    SDL_FreeSurface(rect_titre);
    SDL_FreeSurface(rect_totalPartie);
    SDL_FreeSurface(rect_nbPartie);
    SDL_FreeSurface(rect_reussite);
    SDL_FreeSurface(rect_percent);
    SDL_FreeSurface(rect_back);

    SDL_FreeSurface(txt_titre);
    SDL_FreeSurface(txt_totalPartie);
    SDL_FreeSurface(txt_nbPartie);
    SDL_FreeSurface(txt_reussite);
    SDL_FreeSurface(txt_percent);
    SDL_FreeSurface(txt_back);

    return renvoi;
}
