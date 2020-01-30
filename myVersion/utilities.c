/*
utilities.c
------------
AvaN0x
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utilities.h"

// int readInt(int min, int max) {
    // int res;
    // do {
    //     scanf("%d", &res);
    //     if (res < min  || res > max) 
    //         printf("Veuillez rentrer un entier entre %d et %d : ", min, max);
    // } while (res < min || res > max);
    // return res;
// }

int randomInt(int min, int max) {
    return rand()%(max-min+1)+min;
}


void viderBuffer() {
    int c = 0;
    while (c != '\n' && c != EOF)
        c = getchar();
}

int read(char *chaine, int longueur) {
    char *positionEntree = NULL;
 
    if (fgets(chaine, longueur, stdin) != NULL) {
        positionEntree = strchr(chaine, '\n');
        if (positionEntree != NULL)
            *positionEntree = '\0';
        else
            viderBuffer();
        return 1;
    }
    else
    {
        viderBuffer();
        return EXIT_FAILURE;
    }
}

int readInt(int min, int max) {
    char nombreTexte[16] = {0}; // 100 cases devraient suffire
    int res;
 

    do {
        read(nombreTexte, 16);
        // convertir le nombre en int et le retourner
        res = (int)strtol(nombreTexte, NULL, 10);
        if (res < min  || res > max) 
            printf("Veuillez rentrer un entier entre %d et %d : ", min, max);
    } while (res < min || res > max);
    return res;

}
