#include "bibliotheque.h"

/*Fonctions utiles*/

int interieurClic(SDL_Event event, SDL_Rect zone, int longueur, int hauteur)
{
    //Vérification si le clic est dans la zone ciblée

    if(event.button.x<(zone.x+longueur)
           && event.button.x>zone.x
           && event.button.y<(zone.y+hauteur)
           && event.button.y>zone.y)
        return 1;
    else
        return 0;
}

int interieurMove(SDL_Event event, SDL_Rect zone, int longueur, int hauteur){

    //Vérification si le curseur passe au dessus de la zone ciblée

    if(event.motion.x<(zone.x+longueur)
           && event.motion.x>zone.x
           && event.motion.y<(zone.y+hauteur)
           && event.motion.y>zone.y)
        return 1;
    else
        return 0;
}



float timer(float seconde){
    /*static float temps0=0.0;
    float temps1=0.0;

    temps1 = SDL_GetTicks(); // Récupère le nb de millisecondes depuis le lancement
    if(temps1-temps0 >= 100)
    {
        if(seconde>=1)
            seconde-=0.1;
        else
            seconde=0.0;
        temps0=temps1;
        return seconde;
    }
    else // On endort le programme le temps qu'il faut
    {
        SDL_Delay(100 - (temps1 - temps0));
        return -1.0;
    }*/
    return 1.1;
}


int OK(int tab[]){
    return 1;
}
