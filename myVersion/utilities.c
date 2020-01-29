/*
utilities.c
------------
AvaN0x
*/
#include <stdio.h>
#include <stdlib.h>

#include "utilities.h"

int readInt(int min, int max) {
    int res;
    do {
        scanf("%d", &res);
        if (res < min  || res > max) 
            printf("Veuillez rentrer un entier entre %d et %d : ", min, max);
    } while (res < min || res > max);
    return res;
}

int randomInt(int min, int max) {
    return rand()%(max-min+1)+min;
}
