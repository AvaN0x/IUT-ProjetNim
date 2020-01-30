#include <stdio.h>
#include <stdlib.h>

#include "constant.h"
#include "utilities.h"
#include "game.h"



////////////////////////////////////////
//fonctions à la création de la partie//
////////////////////////////////////////
void Parametres(Plate *p) {
    int config = 0; 
    printf("\nVoulez-vous configurer la partie ? ");
    printf("\n1 - oui");
    printf("\n2 - non (%dx%d contre la machine et l'utilisateur commence)", p->nrow, p->ncol);
    printf("\nVous choisissez : ");
    config = readInt(1,2);

    if (config == 1) {
        printf("\nCombien de lignes voulez-vous (entre %d et %d) ? ", SIZEMIN, SIZEMAX);
        p->nrow = readInt(SIZEMIN, SIZEMAX);
        
        printf("\nCombien de colonnes voulez-vous (entre %d et %d) ? ", SIZEMIN, SIZEMAX);
        p->ncol = readInt(SIZEMIN, SIZEMAX);

        printf("\nQuel niveau de difficulte cherchez-vous :");
        printf("\n%d - debutant", DEBUTANT);
        printf("\n%d - moyen", MOYEN);
        printf("\n%d - expert", EXPERT);
        printf("\n%d - virtuose", VIRTUOSE);
        printf("\n%d - multijoueur", MULTIPLAYER);
        printf("\nVous choisissez : ");
        p->niveau = readInt(DEBUTANT, MULTIPLAYER);

        printf("\nQui commence :");
        printf("\n%d - le joueur", PLAYER1);
        printf("\n%d - la machine", PLAYER2);
        printf("\nVous choisissez : ");
        p->nextPlayer = readInt(PLAYER1, PLAYER2);
    }
    
    p->nban = (p->nrow > p->ncol) ? randomInt(0,p->nrow) : randomInt(0,p->ncol);
}

void fillNimber(int * grid, Plate p) {
    int x, y;
    for (x = p.ncol-1; x >= 0; x--) {
        //derniere ligne
        if ((p.nrow-1)*p.ncol + x == p.nrow * p.ncol - 1
                || grid[(p.nrow-1)*p.ncol + x + 1] == 1 && grid[(p.nrow-1)*p.ncol + x + 2] == 1 // case a droite == 1 et celle encore a droite == 1
                )
            grid[(p.nrow-1)*p.ncol + x] = 0;
        else {
            grid[(p.nrow-1)*p.ncol + x] = 1;
        }
        //les autres lignes
        for (y = p.nrow-2; y >= 0; y--) {
            if ((grid[(y+1)*p.ncol + x] == 1) && (grid[(y+2)*p.ncol + x] == 1) // case en dessous == 1 et case encore en dessous == 1
                || x != p.ncol-1 && grid[(y+1)*p.ncol + x + 1] == 0 // case diagonale en bas a droite
                ) 
                grid[y*p.ncol + x] = 0;
            else {
                grid[y*p.ncol + x] = 1;
            }
        }   
    }

}

void randomBan(int * grid, Plate p) {
    int i, allowed, frame;
    for (i = 0; i < p.nban; i++) {
        allowed = 0;
        do {
            frame = randomInt(1, p.nrow-2)*p.ncol + randomInt(1, p.ncol-2); //on récupère des coordonnées aléatoire pour une case sans comprendre la dernière colonne et la dernière ligne
            if (grid[frame] != 2 // case diagonale est déjà bannie
                && grid[frame - p.ncol + 1 ] != 2  // case diagonale supérieur droit est déjà bannie
                && grid[frame + p.ncol - 1] != 2 // case diagonale inférieur gauche est déjà bannie
                ) {
                allowed = 1;
                grid[frame] = 2;
            } 
        } while (!allowed);
    }
}



void dispGrid(int * grid, Plate p, int pion, int * vois, int nbVois) {
    int x, y, frame = 0, moveNumber = 1;
    for (y = 0; y < p.nrow; y++) {
        for (x = 0; x < p.ncol; x++) {
            if (x!=0) printf("|");
            if (frame == pion)
                printf("O");
            else if (isVois(frame, vois, nbVois))
                printf("%d", moveNumber++);
            else if (grid[frame] == 0) //printf("+"); si on veut voir les coups gagnants
                printf("-");
            else if (grid[frame] == 1)
                printf("-");
            else if (grid[frame] == 2)
                printf("X");
        
            frame++;
        }   
        printf("\n"); 
    }   
}

int isVois(int frame, int * vois, int nbVois) {
    int i;
    for (i = 0; i < nbVois; i++)
        if (frame == vois[i]) return 1;
    return 0;
}


////////////////////////////////////////
//fonction du déroulement de la partie//
////////////////////////////////////////

void launchGame() {
	int pion = 0, * grid, * vois, move = 1, nbVois = 4;
    Plate plate = {20, 20, VIRTUOSE, PLAYER1, 20};

    //récupération des différents paramètres
    Parametres(&plate);

    //on alloue la place necessaire
    grid = malloc(plate.nrow*plate.ncol * sizeof(int));
    vois = malloc(4 * sizeof(int));


    fillNimber(grid, plate);
    randomBan(grid, plate);

    // résumé des spécifications de la partie
    printf("\nVous allez jouer sur une grille de %dx%d avec %d cases bannies et un niveau de difficulte ", plate.nrow, plate.ncol, plate.nban);
    switch (plate.niveau) {
        case DEBUTANT: 
            printf("debutant");
            break;
        case MOYEN:
            printf("moyen");
            break;
        case EXPERT:
            printf("expert");
            break;
        case VIRTUOSE: 
            printf("virtuose");
            break;
    }
    switch (plate.nextPlayer) {
        case PLAYER1:
            printf(" et la machine commence.\n");
            break;
        case PLAYER2:
            printf(" et vous commencez.\n");
            break;
    }


    while (pion != plate.ncol*plate.nrow-1) {
        findVois(plate, vois, grid, pion, &nbVois); //on définie la table des cases voisines

        printf("\n\n");
        dispGrid(grid, plate, pion, vois, nbVois);

        if (plate.nextPlayer == PLAYER2) { //machine
            switch (plate.niveau) {
                case 1: //debutant :  1 randomInt
                    move = randomMoveAI(nbVois);
                    break;
                case 2: //moyen : 2/3 randomInt et 1/3 gagnant
                    if (randomInt(1,3) <= 2)
                        move = randomMoveAI(nbVois);
                    else 
                        move = winningMoveAI(nbVois, vois, grid);
                    break;
                case 3: //expert : 1/3 randomInt et 2/3 gagnant
                    if (randomInt(1,3) <= 1)
                        move = randomMoveAI(nbVois);
                    else 
                        move = winningMoveAI(nbVois, vois, grid);
                    break;
                case 4: //virtuose : 1 gagnant
                    move = winningMoveAI(nbVois, vois, grid);
                    break;
            }
            printf("La machine se deplace en %d.\n", move);


        } else { //joueur
            move = userMove(nbVois);
        }
        
        //on déplace le pion au move-1 (car le choix était entre 1 et nbVois alors qu'il doit etre entre 0 et nbVois-1)
        pion = vois[move-1];

        if (pion != plate.ncol*plate.nrow-1)
            plate.nextPlayer = (plate.nextPlayer == PLAYER1) ? PLAYER2 : PLAYER1; //on change le prochain joueur, sauf si la partie est finie
    }
    nbVois = 0;

    printf("\n\n");
    dispGrid(grid, plate, pion, vois, nbVois);
    if (plate.nextPlayer == PLAYER2) {
        printf("  _____             _\n");
        printf(" |  __ \\           | |\n");
        printf(" | |__) |__ _ __ __| |_   _ \n");
        printf(" |  ___/ _ \\ '__/ _` | | | |\n");
        printf(" | |  |  __/ | | (_| | |_| |\n");
        printf(" |_|   \\___|_|  \\__,_|\\__,_|\n");
        printf("La machine est contente d'avoir gagne :)\n");
    } else {
        printf("   _____                     __\n");
        printf("  / ____|                   /_/\n");
        printf(" | |  __  __ _  __ _ _ __   ___\n");
        printf(" | | |_ |/ _` |/ _` | '_ \\ / _ \\\n");
        printf(" | |__| | (_| | (_| | | | |  __/\n");
        printf("  \\_____|\\__,_|\\__, |_| |_|\\___|\n");
        printf("                __/ |\n");
        printf("               |___/\n");
        printf("La machine est triste d'avoir perdu :(\n");
    }
    free(grid);
    free(vois);
}

void findVois(Plate p, int * vois, int * grid, int pion, int *nbVois) {

    int i, observedFrame, x, y;
    *nbVois = 0;
    x = pion%p.ncol;
    y = pion/p.ncol;
    //on récupère le rang du pion
    for (i = 0; i < 4; i++) {
        // on set la valeur de la case qu'on va regarder
        observedFrame = p.nrow*p.ncol;
        switch (i) {
            case 0:
            if (x + 1 < p.ncol) //si la case est dans le tableau
                    observedFrame = pion + 1;
                break;
            case 1:
                if (x + 2 < p.ncol) //si la case est dans le tableau
                    observedFrame = pion + 2;
                break;
            case 2:
            if (y + 1 < p.nrow) //si la case est dans le tableau
                observedFrame = pion + p.ncol;
                break;
            case 3:
            if (y + 2 < p.nrow) //si la case est dans le tableau
                observedFrame = pion + 2 * p.ncol;
                break;

        }

        //on vérifie si la case existe bien ou si la case suit l'alignement des cases (valeur mise a p.nrow*p.ncol)
        if (observedFrame < p.nrow*p.ncol) {
            if (grid[observedFrame] != 2) {
                vois[*nbVois] = observedFrame;
                (*nbVois)++;
            } else { //on enlève les cas ou l'on devrait "sauter" par dessus une case bannie
                switch (i) {
                    case 0: 
                        i++;
                        break;
                    case 2:
                        i++;
                        break;
                }
            }
        }
    }
}

int userMove(int nbVois) {
    int i, choice;
    printf("A vous de jouer !\n");
    printf("Ou voulez vous vous deplacer ? ");
    for (i = 1; i <= nbVois; i++) {
        printf("%d", i);
    if (i == nbVois-1) 
        printf(" ou ");
    else if (i<nbVois-1) 
        printf(", ");
    } 

    printf("\nChoix : ");

    //on récupère la valeur du déplacement
    choice = readInt(1, nbVois);

    return choice;
}

int randomMoveAI(int nbVois) {
    int choice;
    choice = randomInt(1, nbVois);

    return choice; //on renvoit le choix pour faire le mouvement
}

int winningMoveAI(int nbVois, int * vois, int * grid) {
    int i, choice = -1;
    for (i = 0; i < nbVois; i++) { 
        if (grid[vois[i]] == 0) { //si la case a un nim de 0, on peut aller dessus
            choice = i+1;
            break;
        }
    }
    if (choice == -1)
        choice = randomMoveAI(nbVois);

    return choice; //on renvoit le choix pour afficher le mouvement
}
