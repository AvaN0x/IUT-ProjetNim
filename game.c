#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"

#define VMIN 5
#define VMAX 30

void Parametres(int *nlig, int *ncol, int *niveau, int *next, int *nban) {  
    printf("\nCombien de lignes voulez-vous (entre %d et %d) ? ", VMIN, VMAX);
    Lire_Entier(nlig, VMIN, VMAX);
    
    printf("\nCombien de colonnes voulez-vous (entre %d et %d) ? ", VMIN, VMAX);
    Lire_Entier(ncol, VMIN, VMAX);

    printf("\nQuel niveau de difficulte cherchez-vous :");
    printf("\n1 - debutant");
    printf("\n2 - moyen");
    printf("\n3 - expert");
    printf("\n4 - virtuose");
    printf("\nVous choisissez : ");
    Lire_Entier(niveau, 1, 4);

    printf("\nQui commence :");
    printf("\n1 - la machine");
    printf("\n2 - le joueur");
    printf("\nVous choisissez : ");
    Lire_Entier(next, 1, 2);
    //faire des enum
    *nban = (*nlig > *ncol) ? Hasard(0,*nlig) : Hasard(0,*ncol);
}

void Lire_Entier(int *res, int min, int max) {
    do {
        scanf("%d", res);
        if (*res < min  || *res > max) 
            printf("Veuillez rentrer un entier entre %d et %d.\n", min, max);
    } while (*res < min || *res > max);
}

int Hasard(int min, int max) {
    return rand()%(max-min+1)+min;
}

void fillGrid(char grid[], int nlig, int ncol) {
    int i;
    for (i = 0; i < nlig*ncol; i++) {
        grid[i] = '-';
    }
}

void Calcul_Nimbers(int nim[], int nlig, int ncol) {
    int x, y;
    for (x = ncol-1; x >= 0; x--) {
        //derniere ligne
        if ((nlig-1)*ncol + x == nlig * ncol - 1
                || nim[(nlig-1)*ncol + x + 1] == 1 && nim[(nlig-1)*ncol + x + 2] == 1 // case a droite == 1 et celle encore a droite == 0
                )
            nim[(nlig-1)*ncol + x] = 0;
        else {
            nim[(nlig-1)*ncol + x] = 1;
        }
        //les autres lignes
        for (y = nlig-2; y >= 0; y--) {
            if ((nim[(y+1)*ncol + x] == 1) && (nim[(y+2)*ncol + x] == 1) // case en dessous == 1 et case encore en dessous == 1
                || x != ncol-1 && nim[(y+1)*ncol + x + 1] == 0 // case diagonale en bas a droite
                ) 
                nim[y*ncol + x] = 0;
            else {
                nim[y*ncol + x] = 1;
            }
        }   
    }
}

//JUSTE POUR TEST LES NIIIIIIIMBER
        // void niim(int nim[], int nlig, int ncol) {
        //     int x, y, k = 0;

        //     printf("   "); 
        //     for (x = 1; x <= ncol; x++) { //affichage première ligne avec coord x
        //             printf("%3d ", x);
        //     }

        //     printf("\n");
        //     for (y = 1; y <= nlig; y++) {
        //             printf("%2d", y); //affichage coord y
        //             for (x = 1; x <= ncol; x++) {
        //                 (nim[k] == 1) ? printf("| . ") : printf("| %d ", nim[k]);
        //                 k++;
        //             }   
        //             printf("\n"); 
        //     }

        // }

void displayGrid(char grid[], T_Case ban[], T_Case pion, int nlig, int ncol, int nban) {
    int x, y, k = 0;

    printf("   "); 
    for (x = 1; x <= ncol; x++) { //affichage première ligne avec coord x
            printf("%3d ", x);
    }

    printf("\n");
    for (y = 1; y <= nlig; y++) {
            printf("%2d", y); //affichage coord y
            for (x = 1; x <= ncol; x++) {
                    printf("| %c ", checkFrame(x, y, k, grid, ban, pion, nban));
                    k++;
            }   
            printf("\n"); 
    }

}

char checkFrame(int x, int y, int k, char grid[], T_Case ban[], T_Case pion, int nban) {
    int i;
    char ret = grid[k]; // ret pour return
    if (x == pion.x && y == pion.y) {
        ret = 'O';
    }
    for (i = 0; i < nban; i++) {
        if (x == ban[i].x && y == ban[i].y) {
            ret = 'X';
        }
    }
    return ret;
}

void Hasard_Ban(int nban, T_Case ban[], int nlig, int ncol) {
    int i, j, allowed;
    for (i = 0; i < nban; i++) {
        allowed = 0;
        while (!allowed) {
            ban[i].x = Hasard(1, ncol-1);
            ban[i].y = Hasard(1, nlig-1);
            if (ban[i].x == 1 && ban[i].y == 1) {
                continue;
            } else {
                allowed = 1;
            }
            for (j = 0; j < nban; j++) {
                if (j == i) {
                    continue;
                } else if (ban[i].x == ban[j].x-1 && ban[i].y == ban[j].y+1 || ban[i].x == ban[j].x+1 && ban[i].y == ban[j].y-1 || ban[i].x == ban[j].x && ban[i].y == ban[j].y) {
                    allowed = 0;
                }
            }
        }
    }
}