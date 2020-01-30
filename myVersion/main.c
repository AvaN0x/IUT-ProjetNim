#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utilities.h"
#include "game.h"

int main(int argc, char* argv[]) {
        int choice;
        srand((unsigned int)time(NULL));

        printf("  _   _ _            _____                      \n");
        printf(" | \\ | (_)          / ____|                     \n");
        printf(" |  \\| |_ _ __ ___ | |  __  __ _ _ __ ___   ___ \n");
        printf(" | . ` | | '_ ` _ \\| | |_ |/ _` | '_ ` _ \\ / _ \\\n");
        printf(" | |\\  | | | | | | | |__| | (_| | | | | | |  __/\n");
        printf(" |_| \\_|_|_| |_| |_|\\_____|\\__,_|_| |_| |_|\\___|\n");
        printf("Par Clement RICATTE, Valentin AZANCOTH et Alexandre FURET\n");
                                                
        do {
                printf("\nQue voulez vous faire ?");
                printf("\n0/ Quitter");
                printf("\n1/ Jouer");
                printf("\nChoisissez : ");
                choice = readInt(0, 1);
                (choice == 1) ? launchGame() : printf("=> Aurevoir !");
                printf("\n");
        } while (choice != 0);

        return EXIT_SUCCESS;
}

