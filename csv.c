#include "bibliotheque.h"

int main9(int argc, char *argv[])
{

    FILE *CSV;
    char ligne[200];
    char *ssChaine;
    int h=0,i=0;
    char element[50];
    printf("test");
    //Ouverture du csv
    CSV = fopen("csv.csv","rt");
    while(fgets(ligne,40,CSV) != NULL){
        //Explosion de la ligne avec le ;
        ssChaine = strtok(ligne,";");

        for(i=0;i<6;i++){
            sscanf(ssChaine,"%s",element);
            printf("%s", element);;
            ssChaine = strtok(NULL, ";");
        }
        h++;
    }
    fclose(CSV);
    return 0;
}

