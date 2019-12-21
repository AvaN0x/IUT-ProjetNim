#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"

void launchGame();

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
        
        Parametres(&nlig, &ncol, &niveau, &next, &nban);
        // nlig = 15; ncol = 15, niveau = 1; next = 1; nban = 15;
        char grid[nlig*ncol];

        T_Case ban[nban];

        fillGrid(grid, nlig, ncol);
        Hasard_Ban(nban, ban, nlig, ncol);

        displayGrid(grid, ban, pion, nlig, ncol, nban);

        printf("\nVous allez jouer sur une grille de %d lignes et %d colonnes avec %d cases bannies et un niveau de difficulte de %d avec %d qui commence.", nlig, ncol, nban, niveau, next);
}

