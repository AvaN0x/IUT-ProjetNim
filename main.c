#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"

int main(int argc, char* argv[]) {
        int choice;
        srand((unsigned int)time(NULL));

        printf(".-. .-..-..-.   .-.\n");
        printf("|  `| || ||  `.'  |\n");
        printf("| |\\  || || |\\ /| |\n");
        printf("`-' `-'`-'`-' ` `-'\n");
        do {
                printf("\nQue voulez vous faire ?");
                printf("\n1/ Jouer");
                printf("\n2/ Quitter");
                printf("\nChoisissez : ");
                scanf("%d", &choice);
                (choice == 1) ? launchGame() : (choice == 2) ? printf("=> Adios") : printf("=> Veuillez entrer une des propositions.");
                printf("\n");
        } while (choice !=2);
}
// ajouter la possibilité d'avoir les regles?

void launchGame() {
        int nlig, ncol, niveau, next, nban;
        T_Case pion;
        pion.x = 1;
        pion.y = 1;
        char* grid;
        int* nim;
        T_Case* ban;

        Parametres(&nlig, &ncol, &niveau, &next, &nban);

        //juste pour les tests et pas se faire chier a rerentrer a chaque fois
        //nlig = 9; ncol = 10, niveau = 1; next = 1; nban = 10;

        grid = malloc(nlig*ncol * sizeof(char));
        nim = malloc(nlig*ncol * sizeof(int));
        ban = malloc(nban * sizeof(T_Case));

        fillGrid(grid, nlig, ncol);
        Hasard_Ban(nban, ban, nlig, ncol);

        Calcul_Nimbers(nim, nlig, ncol);

        displayGrid(grid, ban, pion, nlig, ncol, nban);
        //niim(nim, nlig, ncol);

        printf("\nVous allez jouer sur une grille de %d lignes et %d colonnes avec %d cases bannies et un niveau de difficulte de %d avec %d qui commence.", nlig, ncol, nban, niveau, next);
}

