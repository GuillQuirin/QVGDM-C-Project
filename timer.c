#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>


#include "timer.h"

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
