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
    static float temps0=0.0;
    float temps1=0.0;

    temps1 = SDL_GetTicks(); // Récupère le nb de millisecondes depuis le lancement

    if(temps1-temps0 >= 100)
    {
        if(seconde>=1)
            seconde-=0.1;
        else
            seconde=0.0;

        temps0=temps1;
    }
    else // On endort le programme le temps qu'il faut
    {
        SDL_Delay(100 - (temps1 - temps0));
    }

    return seconde;
}

void del_char(char* str, char c) //Enleve tous les c de str
{
   int id_read, id_write;
   id_read = 0;
   id_write = 0;

   while (str[id_read] != '\0')
   {
      if (str[id_read] != c)
      {
          str[id_write] = str[id_read];
          id_write++;
      }
      id_read++;
    }
    str[id_write-1] = '\0';
}
