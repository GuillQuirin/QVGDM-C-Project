#include "bibliotheque.h"
#include "fonctions.h"
#include "struc.h"

int partie(SDL_Surface *fenetre, SDL_Surface *imagebg, SDL_Rect positionFond, TTF_Font *police, int renvoi){

    SDL_Surface *txt_Question=NULL, *txt_Rep1=NULL, *txt_Rep2=NULL, *txt_Rep3=NULL, *txt_Rep4=NULL, *txt_Timer=NULL;
    SDL_Surface *rect_Question=NULL, *rect_Rep1=NULL, *rect_Rep2=NULL, *rect_Rep3=NULL, *rect_Rep4=NULL,  *rect_Timer=NULL;

    SDL_Rect positionRect_Quest, positionRect_Rep1,positionRect_Rep2,positionRect_Rep3,positionRect_Rep4, positionRect_Timer;
    SDL_Rect positionTxt_Quest, positionTxt_Rep1, positionTxt_Rep2, positionTxt_Rep3, positionTxt_Rep4, positionTxt_Timer;

    SDL_Color couleurNoire = {0,0,0};


    /*Declaration de la variable d'évènements*/
    SDL_Event evenement;
    int boucle = 1;

    char temps[20];
    float tempsTot = 60.0;
    float seconde=60.0;

    switch(renvoi){
        case 21: //Facile
            tempsTot=20.0;break;

        case 22: //Moyen
            tempsTot=15.0;break;
        case 23: //Difficile
            tempsTot=5.0;break;

        default:
            tempsTot=60.0;break;
    }

    seconde=tempsTot;

    int Reclongueur=300, Rechauteur=60;

    int note=0;

    /*GESTION DU CSV*/

    FILE *CSV;
    char ligne[100];
    char *ssChaine;
    int i=0;
    char elementTab[200];

    //Tableau de structure pour 10 questions
    etape tab[10];
    int nb_question=0;

    CSV = fopen("csv.csv","rt");
    while(fgets(ligne,80,CSV) != NULL){
        //Explosion de la ligne avec le ;
        ssChaine = strtok(ligne,";");
        for(i=0;i<7;i++){
            // id, lib_question, r1, r2, r3, r4, id_reponse
            sscanf(ssChaine,"%s",elementTab);
            switch(i){
                case 0:
                    strcpy(tab[nb_question].id, elementTab);break;
                case 1:
                    strcpy(tab[nb_question].question, elementTab);break;
                case 2:
                    strcpy(tab[nb_question].reponse1, elementTab);break;
                case 3:
                    strcpy(tab[nb_question].reponse2, elementTab);break;
                case 4:
                    strcpy(tab[nb_question].reponse3, elementTab);break;
                case 5:
                    strcpy(tab[nb_question].reponse4, elementTab);break;
                case 6:
                    tab[nb_question].resultat = char_to_int(elementTab[0]);break;
            }
            ssChaine = strtok(NULL, ";");
        }
        nb_question++;
    }

    fclose(CSV);


    /*Chargement de la police*/

    TTF_SetFontStyle(police,TTF_STYLE_NORMAL);//, TTF_STYLE_ITALIC | TTF_STYLE_UNDERLINE);

    positionRect_Quest.x = 100;
    positionRect_Quest.y = 25;

    positionRect_Timer.x = 250;
    positionRect_Timer.y = 200;

    positionRect_Rep1.x = 20;
    positionRect_Rep1.y = 300;

    positionRect_Rep2.x = 330;
    positionRect_Rep2.y = 300;

    positionRect_Rep3.x = 20;
    positionRect_Rep3.y = 400;

    positionRect_Rep4.x = 330;
    positionRect_Rep4.y = 400;

    positionTxt_Quest.x = positionRect_Quest.x+(Reclongueur/5);
    positionTxt_Quest.y = positionRect_Quest.y+(Rechauteur/4);

    positionTxt_Timer.x = positionRect_Timer.x+(Reclongueur/5);
    positionTxt_Timer.y = positionRect_Timer.y+(Rechauteur/4);

    positionTxt_Rep1.x  = positionRect_Rep1.x+(Reclongueur/4);
    positionTxt_Rep1.y  = positionRect_Rep1.y+(Rechauteur/4);

    positionTxt_Rep2.x  = positionRect_Rep2.x+(Reclongueur/4);
    positionTxt_Rep2.y  = positionRect_Rep2.y+(Rechauteur/4);

    positionTxt_Rep3.x  = positionRect_Rep3.x+(Reclongueur/4);
    positionTxt_Rep3.y  = positionRect_Rep3.y+(Rechauteur/4);

    positionTxt_Rep4.x  = positionRect_Rep4.x+(Reclongueur/4);
    positionTxt_Rep4.y  = positionRect_Rep4.y+(Rechauteur/8);

    //Caractéristiques des élèments

    rect_Question = SDL_CreateRGBSurface(SDL_HWSURFACE, Reclongueur+(Reclongueur/2), Rechauteur, 32, 0, 0, 0, 0);
    rect_Timer    = SDL_CreateRGBSurface(SDL_HWSURFACE, (Reclongueur/2), Rechauteur, 32, 0, 0, 0, 0);
    rect_Rep1     = SDL_CreateRGBSurface(SDL_HWSURFACE, Reclongueur, Rechauteur, 32, 0, 0, 0, 0);
    rect_Rep2     = SDL_CreateRGBSurface(SDL_HWSURFACE, Reclongueur, Rechauteur, 32, 0, 0, 0, 0);
    rect_Rep3     = SDL_CreateRGBSurface(SDL_HWSURFACE, Reclongueur, Rechauteur, 32, 0, 0, 0, 0);
    rect_Rep4     = SDL_CreateRGBSurface(SDL_HWSURFACE, Reclongueur, Rechauteur, 32, 0, 0, 0, 0);

int now=0, last=0;

    while(boucle!=0 && nb_question!=0 && note<3){

        /*Gestion du chronomètre dans le jeu*/
        seconde = timer(seconde);
        if(seconde !=-1.0){
            sprintf(temps, "%.1f", seconde);
        }

        if(seconde == 0.0){
            now = SDL_GetTicks();
            if(now > last + 500) {
               nb_question--;
                seconde=tempsTot;
            }
         last=now;
        }

        SDL_PollEvent(&evenement); // Récupération de l'évènement
        //SDL_WaitEvent(&evenement);
        switch(evenement.type){//Type d'évènement

            case SDL_QUIT: // Arrêt du programme
                boucle = 0;
                break;

            case SDL_MOUSEBUTTONUP: // Clic souris
                switch(evenement.button.button){ //Analyse de l'équipement de la souris
                    case SDL_BUTTON_LEFT:

                        //Delai de 0.5 secondes avant de pouvoir réexcuter un évènement
                        now = SDL_GetTicks();
                        if(now > last + 500){
                            //Reponse 1
                            if(interieurClic(evenement,positionRect_Rep1, Reclongueur, Rechauteur)){
                                if(tab[nb_question-1].resultat==1){
                                    note++;
                                }
                                nb_question--;
                                seconde=tempsTot;
                                evenement.type=SDL_ACTIVEEVENT;
                                // on change evenement.type pour eviter la boucle infinie
                            }


                            //Reponse 2
                            if(interieurClic(evenement,positionRect_Rep2, Reclongueur, Rechauteur)){
                                if(tab[nb_question-1].resultat==2){
                                    note++;
                                }
                                nb_question--;
                                seconde=tempsTot;
                                evenement.type=SDL_ACTIVEEVENT;
                                // on change evenement.type pour eviter la boucle infinie
                            }

                            //Reponse 3
                            if(interieurClic(evenement,positionRect_Rep3, Reclongueur, Rechauteur)){
                                if(tab[nb_question-1].resultat==3){
                                    note++;
                                }
                                nb_question--;
                                seconde=tempsTot;
                                evenement.type=SDL_ACTIVEEVENT;
                                // on change evenement.type pour eviter la boucle infinie
                            }

                            //Reponse 4
                            if(interieurClic(evenement,positionRect_Rep4, Reclongueur, Rechauteur)){
                                if(tab[nb_question-1].resultat==4){
                                    note++;
                                }
                                nb_question--;
                                seconde=tempsTot;
                                evenement.type=SDL_ACTIVEEVENT;
                                // on change evenement.type pour eviter la boucle infinie
                            }
                            last=now;
                        }
                        break;
                }
                break;

            case SDL_MOUSEMOTION:

                //Reponse 1
                if(interieurMove(evenement, positionRect_Rep1, Reclongueur, Rechauteur)){
                    SDL_FillRect(rect_Rep1, NULL, SDL_MapRGB(fenetre->format, 255, 206, 112));
                }

                //Reponse 2
                if(interieurMove(evenement, positionRect_Rep2, Reclongueur, Rechauteur)){
                    SDL_FillRect(rect_Rep2, NULL, SDL_MapRGB(fenetre->format, 255, 206, 112));
                }

                //Reponse 3
                if(interieurMove(evenement, positionRect_Rep3, Reclongueur, Rechauteur)){
                    SDL_FillRect(rect_Rep3, NULL, SDL_MapRGB(fenetre->format, 255, 206, 112));
                }

                //Reponse 4
                if(interieurMove(evenement, positionRect_Rep4, Reclongueur, Rechauteur)){
                    SDL_FillRect(rect_Rep4, NULL, SDL_MapRGB(fenetre->format, 255, 206, 112));
                }
                break;
        }

        if(nb_question<=0)
            continue;

        //MAJ du texte

        txt_Question = TTF_RenderText_Blended(police,tab[nb_question-1].question,couleurNoire);
        txt_Timer    = TTF_RenderText_Blended(police, temps, couleurNoire);
        txt_Rep1     = TTF_RenderText_Blended(police, tab[nb_question-1].reponse1, couleurNoire);
        txt_Rep2     = TTF_RenderText_Blended(police, tab[nb_question-1].reponse2, couleurNoire);
        txt_Rep3     = TTF_RenderText_Blended(police, tab[nb_question-1].reponse3, couleurNoire);
        txt_Rep4     = TTF_RenderText_Blended(police, tab[nb_question-1].reponse4, couleurNoire);

        /*Affichage des élèments + background à chaque tour de boucle*/

            //Coloration du fond
                SDL_FillRect(fenetre, NULL, SDL_MapRGB(fenetre->format, 0, 0, 0));
                SDL_BlitSurface(imagebg, NULL, fenetre, &positionFond);

                //Application de l'élèment sur le background

                SDL_BlitSurface(rect_Question, NULL, fenetre, &positionRect_Quest);
                SDL_BlitSurface(rect_Timer, NULL, fenetre, &positionRect_Timer);
                SDL_BlitSurface(rect_Rep1, NULL, fenetre, &positionRect_Rep1);
                SDL_BlitSurface(rect_Rep2, NULL, fenetre, &positionRect_Rep2);
                SDL_BlitSurface(rect_Rep3, NULL, fenetre, &positionRect_Rep3);
                SDL_BlitSurface(rect_Rep4, NULL, fenetre, &positionRect_Rep4);

                SDL_FillRect(rect_Question, NULL, SDL_MapRGB(fenetre->format, 17, 206, 112));
                SDL_FillRect(rect_Timer, NULL, SDL_MapRGB(fenetre->format, 17, 206, 112));
                SDL_FillRect(rect_Rep1, NULL, SDL_MapRGB(fenetre->format, 17, 206, 112));
                SDL_FillRect(rect_Rep2, NULL, SDL_MapRGB(fenetre->format, 17, 206, 112));
                SDL_FillRect(rect_Rep3, NULL, SDL_MapRGB(fenetre->format, 17, 206, 112));
                SDL_FillRect(rect_Rep4, NULL, SDL_MapRGB(fenetre->format, 17, 206, 112));

            //Caractéristiques du texte
                SDL_BlitSurface(txt_Question, NULL, fenetre, &positionTxt_Quest);
                SDL_BlitSurface(txt_Timer, NULL, fenetre, &positionTxt_Timer);
                SDL_BlitSurface(txt_Rep1, NULL, fenetre, &positionTxt_Rep1);
                SDL_BlitSurface(txt_Rep2, NULL, fenetre, &positionTxt_Rep2);
                SDL_BlitSurface(txt_Rep3, NULL, fenetre, &positionTxt_Rep3);
                SDL_BlitSurface(txt_Rep4, NULL, fenetre, &positionTxt_Rep4);

            /*Mise à jour de la fenêtre avec les élèments modifiés*/
                SDL_Flip(fenetre);
    }

    SDL_FreeSurface(rect_Question);
    SDL_FreeSurface(rect_Timer);
    SDL_FreeSurface(rect_Rep1);
    SDL_FreeSurface(rect_Rep2);
    SDL_FreeSurface(rect_Rep3);
    SDL_FreeSurface(rect_Rep4);
    SDL_FreeSurface(txt_Question);
    SDL_FreeSurface(txt_Timer);
    SDL_FreeSurface(txt_Rep1);
    SDL_FreeSurface(txt_Rep2);
    SDL_FreeSurface(txt_Rep3);
    SDL_FreeSurface(txt_Rep4);

    /*ECRITURE DANS LE FICHIER DE SAUVEGARDE*/

    return (renvoi>20 && renvoi<30) ? (renvoi+40) : renvoi;
}
