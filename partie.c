#include "bibliotheque.h"
#include "fonctions.h"
#include "struc.h"

int partie(SDL_Surface *fenetre, SDL_Surface *imagebg, SDL_Rect positionFond, TTF_Font *police, int renvoi){

    SDL_Surface *txt_Question=NULL, *txt_Rep1=NULL, *txt_Rep2=NULL, *txt_Rep3=NULL, *txt_Rep4=NULL, *txt_Timer=NULL;
    SDL_Surface *rect_Question=NULL, *rect_Rep1=NULL, *rect_Rep2=NULL, *rect_Rep3=NULL, *rect_Rep4=NULL,  *rect_Timer=NULL;

    SDL_Rect positionRect_Quest, positionRect_Rep1,positionRect_Rep2,positionRect_Rep3,positionRect_Rep4, positionRect_Timer;
    SDL_Rect positionTxt_Quest, positionTxt_Rep1, positionTxt_Rep2, positionTxt_Rep3, positionTxt_Rep4, positionTxt_Timer;

    SDL_Color couleurNoire = {0,0,0};

    /*Declaration de la variable d'�v�nements*/
    SDL_Event evenement;
    int boucle = 1;
    char nombre[5];
    sprintf(nombre, "%d", renvoi);

    char temps[20];
    float seconde=10.0;

    int Reclongueur=250, Rechauteur=60;

    //Tableau [id_question][libelle (question/reponses)]
    int tableau[4][5];
    int cpt=0, note=0;

    //Chargement de la police
    TTF_SetFontStyle(police,TTF_STYLE_NORMAL);//, TTF_STYLE_ITALIC | TTF_STYLE_UNDERLINE);

    positionRect_Quest.x = 150;
    positionRect_Quest.y = 100;

    positionRect_Timer.x = 150;
    positionRect_Timer.y = 200;

    positionRect_Rep1.x = 40;
    positionRect_Rep1.y = 300;

    positionRect_Rep2.x = 330;
    positionRect_Rep2.y = 300;

    positionRect_Rep3.x = 40;
    positionRect_Rep3.y = 400;

    positionRect_Rep4.x = 330;
    positionRect_Rep4.y = 400;

    positionTxt_Quest.x = positionRect_Quest.x+(Reclongueur/4);
    positionTxt_Quest.y = positionRect_Quest.y+(Rechauteur/4);

    positionTxt_Timer.x = positionRect_Timer.x+(Reclongueur/4);
    positionTxt_Timer.y = positionRect_Timer.y+(Rechauteur/4);

    positionTxt_Rep1.x  = positionRect_Rep1.x+(Reclongueur/4);
    positionTxt_Rep1.y  = positionRect_Rep1.y+(Rechauteur/4);

    positionTxt_Rep2.x  = positionRect_Rep2.x+(Reclongueur/4);
    positionTxt_Rep2.y  = positionRect_Rep2.y+(Rechauteur/4);

    positionTxt_Rep3.x  = positionRect_Rep3.x+(Reclongueur/4);
    positionTxt_Rep3.y  = positionRect_Rep3.y+(Rechauteur/4);

    positionTxt_Rep4.x  = positionRect_Rep4.x+(Reclongueur/4);
    positionTxt_Rep4.y  = positionRect_Rep4.y+(Rechauteur/4);

    //Caract�ristiques des �l�ments

    rect_Question = SDL_CreateRGBSurface(SDL_HWSURFACE, (Reclongueur+Reclongueur/3), Rechauteur, 32, 0, 0, 0, 0);
    rect_Timer    = SDL_CreateRGBSurface(SDL_HWSURFACE, Reclongueur, Rechauteur, 32, 0, 0, 0, 0);
    rect_Rep1     = SDL_CreateRGBSurface(SDL_HWSURFACE, Reclongueur, Rechauteur, 32, 0, 0, 0, 0);
    rect_Rep2     = SDL_CreateRGBSurface(SDL_HWSURFACE, Reclongueur, Rechauteur, 32, 0, 0, 0, 0);
    rect_Rep3     = SDL_CreateRGBSurface(SDL_HWSURFACE, Reclongueur, Rechauteur, 32, 0, 0, 0, 0);
    rect_Rep4     = SDL_CreateRGBSurface(SDL_HWSURFACE, Reclongueur, Rechauteur, 32, 0, 0, 0, 0);


    FILE *CSV;
    char ligne[100];
    char *ssChaine;
    int i=0, j=0;
    char elementTab[200];

    //Ouverture du csv
    etape tab[10];
    CSV = fopen("csv.csv","rt");
    int compteur=0;
    while(fgets(ligne,40,CSV) != NULL){
        //Explosion de la ligne avec le ;
        ssChaine = strtok(ligne,";");

        for(i=0;i<6;i++){
            sscanf(ssChaine,"%s",elementTab);
            switch(i){
                case 0:
                    strcpy(tab[compteur].id, elementTab);break;
                case 1:
                    strcpy(tab[compteur].question, elementTab);break;
                case 2:
                    strcpy(tab[compteur].reponse1, elementTab);break;
                case 3:
                    strcpy(tab[compteur].reponse2, elementTab);break;
                case 4:
                    strcpy(tab[compteur].reponse3, elementTab);break;
                case 5:
                    strcpy(tab[compteur].reponse4, elementTab);break;
            }
            ssChaine = strtok(NULL, ";");
        }
        printf("--------------\n");
        compteur++;
    }
    fclose(CSV);

    while(boucle!=0 && cpt!=1){

        /*Gestion du chronom�tre dans le jeu*/
        seconde = timer(seconde);
        if(seconde !=-1.0){
            sprintf(temps, "%.1f", seconde);
        }

        if(seconde == 0.0){
            boucle =0;
        }

        SDL_PollEvent(&evenement); // R�cup�ration de l'�v�nement
        switch(evenement.type){//Type d'�v�nement

            case SDL_QUIT: // Arr�t du programme
                boucle = 0;
                break;

            case SDL_KEYDOWN: //Appui sur une touche
                switch(evenement.key.keysym.sym){// Analyse de la touche

                    case SDLK_ESCAPE://Acc�s aux options
                        renvoi = 51;
                        boucle = 0;
                        break;
                    default:
                        break;
                }
                break;

            case SDL_MOUSEBUTTONUP: // Clic souris
                switch(evenement.button.button){ //Analyse de l'�quipement de la souris
                    case SDL_BUTTON_LEFT:

                        //Reponse 1
                        if(interieurClic(evenement,positionRect_Rep1, Reclongueur, Rechauteur)){
                            if(OK(tableau[4])){
                                note++;
                            }
                            cpt++;
                        }

                        //Reponse 2
                        if(interieurClic(evenement,positionRect_Rep2, Reclongueur, Rechauteur)){
                            if(OK(tableau[4])){
                                note++;
                            }
                            cpt++;
                        }

                        //Reponse 3
                        if(interieurClic(evenement,positionRect_Rep3, Reclongueur, Rechauteur)){
                            if(OK(tableau[4])){
                                note++;
                            }
                            cpt++;
                        }

                        //Reponse 4
                        if(interieurClic(evenement,positionRect_Rep4, Reclongueur, Rechauteur)){
                            if(OK(tableau[4])){
                                note++;
                            }
                            cpt++;
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


        //MAJ du texte

        txt_Question = TTF_RenderText_Blended(police,tab[0].question,couleurNoire);
        //txt_Timer    = TTF_RenderText_Blended(police, temps, couleurNoire);
        txt_Rep1     = TTF_RenderText_Blended(police, tab[0].reponse1, couleurNoire);
        txt_Rep2     = TTF_RenderText_Blended(police, tab[0].reponse2, couleurNoire);
        txt_Rep3     = TTF_RenderText_Blended(police, tab[0].reponse3, couleurNoire);
        txt_Rep4     = TTF_RenderText_Blended(police, tab[0].reponse4, couleurNoire);

        j++;

        /*Affichage des �l�ments + background � chaque tour de boucle*/

            //Coloration du fond
                SDL_FillRect(fenetre, NULL, SDL_MapRGB(fenetre->format, 255, 255, 112));
                SDL_BlitSurface(imagebg, NULL, fenetre, &positionFond);

                //Application de l'�l�ment sur le background

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

            //Caract�ristiques du texte
                SDL_BlitSurface(txt_Question, NULL, fenetre, &positionTxt_Quest);
                SDL_BlitSurface(txt_Timer, NULL, fenetre, &positionTxt_Timer);
                SDL_BlitSurface(txt_Rep1, NULL, fenetre, &positionTxt_Rep1);
                SDL_BlitSurface(txt_Rep2, NULL, fenetre, &positionTxt_Rep2);
                SDL_BlitSurface(txt_Rep3, NULL, fenetre, &positionTxt_Rep3);
                SDL_BlitSurface(txt_Rep4, NULL, fenetre, &positionTxt_Rep4);

            /*Mise � jour de la fen�tre avec les �l�ments modifi�s*/
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

    return (renvoi>30 && renvoi<40) ? (renvoi+30) : renvoi;
}
