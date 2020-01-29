#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"

/////////////
//utilities//
/////////////
void Lire_Entier(int *res, int min, int max) {
    do {
        scanf("%d", res);
        if (*res < min  || *res > max) 
            printf("Veuillez rentrer un entier entre %d et %d : ", min, max);
    } while (*res < min || *res > max);
}

int Hasard(int min, int max) {
    return rand()%(max-min+1)+min;
}




////////////////////////////////////////
//fonctions à la création de la partie//
////////////////////////////////////////
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
    *nban = (*nlig > *ncol) ? Hasard(0,*nlig) : Hasard(0,*ncol);
}

void fillGrid(T_Case *grid, int nlig, int ncol) { // remplir la grille avec les coordonnées de chaque case
    int x, y, k = 0;
    for (y = 1; y <= nlig; y++) {
        for (x = 1; x <= ncol; x++) {
            grid[k].x = x;
            grid[k].y = y;
            k++;
        }   
    }

}

void Hasard_Ban(int nban, T_Case *ban, int nlig, int ncol) {
    int i, j, allowed;
    for (i = 0; i < nban; i++) {
        allowed = 0;
        while (!allowed) {
            ban[i].x = Hasard(2, ncol-1); //on récupère des coordonnées aléatoire pour une case sans comprendre la dernière colonne et la dernière ligne
            ban[i].y = Hasard(2, nlig-1);
            if (!(ban[i].x == 1 && ban[i].y == 1)) { //si la case n'est pas la case (1,1), alors elle est autorisé
                allowed = 1;
            }
            for (j = 0; j < nban; j++) {
                if (j == i) {
                    continue;
                } else if (ban[i].x == ban[j].x-1 && ban[i].y == ban[j].y+1 // case diagonale inférieur gauche est déjà bannie
                    || ban[i].x == ban[j].x+1 && ban[i].y == ban[j].y-1 // case diagonale supérieur droit est déjà bannie
                    || ban[i].x == ban[j].x && ban[i].y == ban[j].y // case diagonale est déjà bannie
                    ) {
                    allowed = 0;
                }
            }
        }
    }
}

void Calcul_Nimbers(int nim[][VMAX], int nlig, int ncol) {
    int x, y;

    nim[ncol-1][nlig-1] = 0; //on set la case de coordonnées (ncol,nlig) : de 0 à ncol-1 (au lieu de 1 à ncol)
    // dernière colonne
    for (y = nlig-2; y >= 0; y--) {
        if (nim[ncol-1][y+1] == 1 && nim[ncol-1][y+2] == 1) // case en dessous == 1 et case encore en dessous == 1
            nim[ncol-1][y] = 0;
        else 
            nim[ncol-1][y] = 1;
    }  
    // autres colonnes 
    for (x = ncol-2; x >= 0; x--) {
        //derniere ligne
        if (nim[x+1][nlig-1] == 1 && nim[x+2][nlig-1] == 1) // case a droite == 1 et celle encore a droite == 1
            nim[x][nlig-1] = 0;
        else 
            nim[x][nlig-1] = 1;

        //autres lignes
        for (y = nlig-2; y >= 0; y--) {
            if (x != ncol-1 && nim[x+1][y+1] == 0 // case diagonale en bas a droite
                ) 
                nim[x][y] = 0;
            else 
                nim[x][y] = 1;
        }   
    }
    // dispNim(nim, nlig, ncol); // pour voir la génération des nim
}

    void dispNim(int nim[][VMAX], int nlig, int ncol) { // pour voir la génération des nim
        int x, y;

        printf("   "); 
        for (x = 0; x < ncol; x++) { //affichage première ligne avec coord x
                printf(" %-2d ", x+1);
        }

        printf("\n");
        for (y = 0; y < nlig; y++) {
                printf("%2d", y+1); //affichage coord y
                for (x = 0; x < ncol; x++) {
                    (nim[x][y] == 1) ? printf("| . ") : printf("| %d ", nim[x][y]); // si la valeur est 1 on affiche un '.', sinon on met 0
                }   
                printf("\n"); 
        }   
    }

void displayGrid(T_Case *grid, T_Case *ban, T_Case pion, int nlig, int ncol, int nban, int nb_vois, T_Case vois[]) {
    int x, y, i, isVois = 0;
    char res;

    printf("   "); 
    for (x = 1; x <= ncol; x++) { //affichage première ligne avec coord x
            printf(" %-2d ", x);
    }

    printf("\n");
    for (y = 1; y <= nlig; y++) {
        printf("%2d", y); //affichage coord y
        for (x = 1; x <= ncol; x++) {
             // si la case est une voisine on affiche le numero de voisin
            isVois = 0;
            for (i = 0; i < nb_vois; i++)
                if (x == vois[i].x && y == vois[i].y) {
                    isVois = 1;
                    break;
                }
            if (isVois == 1)
                printf("| %d ", i+1);
            else { // sinon on regarde si le pion est a la position de la case, ou si elle est bannie
                res = '-'; 
                for (i = 0; i < nban; i++) {
                    if (x == ban[i].x && y == ban[i].y) {
                        res = 'X';
                    }
                }
                if (x == pion.x && y == pion.y) {
                    res = 'O';
                }
                printf("| %c ", res);
            }
        }   
        printf("\n"); 
    }
}




////////////////////////////////////////
//fonction du déroulement de la partie//
////////////////////////////////////////

void launchGame() {
	int nlig, ncol, niveau, next = 2, nban, nb_vois, move = 1, nim[VMAX][VMAX] = { 0 };
	T_Case pion, * grid, * ban, * vois;
        pion.x = 1;
        pion.y = 1;

        //récupération des différents paramètres
        Parametres(&nlig, &ncol, &niveau, &next, &nban);

        //Pour rentrer les paramètres manuellement
        //nlig = 10; ncol = 10, niveau = 1; next = 2; nban = 5;

        //on alloue la place necessaire
        grid = malloc(nlig*ncol * sizeof(T_Case));
        ban = malloc(nban * sizeof(T_Case));
        vois = malloc(4 * sizeof(T_Case));

        // ne fonctionne que sous windows bizarrement
        // nim = malloc(ncol * sizeof(int)); // première dimension de nim
        // for (i = 0; i < ncol; i++)
        //         nim[i] = malloc(nlig * sizeof(int)); //deuxieme dimension de nim

        // on prépare la partie
        fillGrid(grid, nlig, ncol); // on remplit le tableau de la grille avec chaque coordonnées de case
        Hasard_Ban(nban, ban, nlig, ncol); // on définit les cases bannies
        Calcul_Nimbers(nim, nlig, ncol); // on définit le nimber

        // résumé des spécifications de la partie
        printf("\nVous allez jouer sur une grille de %dx%d avec %d cases bannies et un niveau de difficulte ", nlig, ncol, nban);
        switch (niveau) {
            case 1: 
                printf("debutant");
                break;
            case 2:
                printf("moyen");
                break;
            case 3: 
                printf("expert");
                break;
            case 4: 
                printf("virtuose");
                break;
        }
        switch (next) {
            case 1:
                printf(" et la machine commence.\n");
                break;
            case 2:
                printf(" et vous commencez.\n");
                break;
        }

        while (!(pion.x == ncol && pion.y == nlig)) {
            Voisines(&nb_vois, vois, nlig, ncol, grid, ban, nban, pion); //on définie la table des cases voisines

            printf("\n\n");
            displayGrid(grid, ban, pion, nlig, ncol, nban, nb_vois, vois);

            if (next == 1) { //machine
                switch (niveau) {
                    case 1: //debutant :  1 Hasard
                        move = Coup_Ordi_Hasard(nb_vois, vois);
                        break;
                    case 2: //moyen : 2/3 hasard et 1/3 gagnant -- PS : dans le sujet moyen et expert sont inversés
                        if (Hasard(1,3) <= 2)
                            move = Coup_Ordi_Hasard(nb_vois, vois);
                        else 
                            move = Coup_Ordi_Gagnant(nb_vois, vois, nim);
                        break;
                    case 3: //expert : 1/3 hasard et 2/3 gagnant
                        if (Hasard(1,3) <= 1)
                            move = Coup_Ordi_Hasard(nb_vois, vois);
                        else 
                            move = Coup_Ordi_Gagnant(nb_vois, vois, nim);
                        break;
                    case 4: //virtuose : 1 gagnant
                        move = Coup_Ordi_Gagnant(nb_vois, vois, nim);
                        break;
                }
                printf("La machine se deplace en %d:(%d,%d)\n", move, vois[move-1].x, vois[move-1].y);

            } else { //joueur
                move = Coup_joueur(nb_vois, vois);
            }
            
            //on déplace le pion au move-1 (car le choix était entre 1 et nb_vois alors qu'il doit etre entre 0 et nb_vois-1)
            Deplacement(&pion, move-1, vois);

            if (!(pion.x == ncol && pion.y == nlig))
                next = next == 1 ? 2 : 1; //on change le prochain joueur, sauf si la partie est finie
        }
        nb_vois = 0;
        displayGrid(grid, ban, pion, nlig, ncol, nban, nb_vois, vois);
        if (next == 1) {
            printf("  _____             _       \n");
            printf(" |  __ \\           | |      \n");
            printf(" | |__) |__ _ __ __| |_   _ \n");
            printf(" |  ___/ _ \\ '__/ _` | | | |\n");
            printf(" | |  |  __/ | | (_| | |_| |\n");
            printf(" |_|   \\___|_|  \\__,_|\\__,_|\n");
            printf("La machine est contente d'avoir gagne :)\n");
        } else {
            printf("   _____                     __ \n");
            printf("  / ____|                   /_/ \n");
            printf(" | |  __  __ _  __ _ _ __   ___ \n");
            printf(" | | |_ |/ _` |/ _` | '_ \\ / _ \\\n");
            printf(" | |__| | (_| | (_| | | | |  __/\n");
            printf("  \\_____|\\__,_|\\__, |_| |_|\\___|\n");
            printf("                __/ |           \n");
            printf("               |___/            \n");
            printf("La machine est triste d'avoir perdu :(\n");
        }
        free(grid);
        free(ban);
        free(vois);
        // ne fonctionne que sous windows bizarrement
        // for (i = 0; i < ncol; i++)
        //     free(nim[i]);
        // free(nim);

}

void Deplacement(T_Case *pion, int rangVois, T_Case vois[]) {
    pion->x = vois[rangVois].x;
    pion->y = vois[rangVois].y;
}

void Voisines(int *nb_vois, T_Case vois[], int nlig, int ncol, T_Case *grid, T_Case *ban, int nban, T_Case pion) {
    int rangPion, i, j, isBanned, observedFrame;
    *nb_vois = 0;

    //on récupère le rang du pion
    for (rangPion = 0; rangPion < nlig*ncol; rangPion++)
        if (grid[rangPion].x == pion.x && grid[rangPion].y == pion.y) {
            break;
        }    
    for (i = 0; i < 4; i++) {
        isBanned = 0; // on redéfinie la case comme non bannie

        // on set la valeur de la case qu'on va regarder
        observedFrame = nlig*ncol;
        switch (i) {
            case 0:
                if (grid[rangPion].x + 1 <= ncol) //si la case est dans le tableau
                    observedFrame = rangPion + 1;
                break;
            case 1:
                if (grid[rangPion].x + 2 <= ncol) //si la case est dans le tableau
                    observedFrame = rangPion + 2;
                break;
            case 2:
            if (grid[rangPion].y + 1 <= nlig) //si la case est dans le tableau
                observedFrame = rangPion + ncol;
                break;
            case 3:
            if (grid[rangPion].y + 2 <= nlig) //si la case est dans le tableau
                observedFrame = rangPion + 2 * ncol;
                break;
        }

        //on vérifie si la case existe bien ou si la case suit l'alignement des cases (valeur mise a nlig*ncol)
        if (observedFrame < nlig*ncol) {
            //on verifie si la case est bannie
            for(j = 0; j < nban; j++)
                if (grid[observedFrame].x == ban[j].x && grid[observedFrame].y == ban[j].y) 
                    isBanned = 1;

            // si la case n'est pas bannie, on peut la garder
            if (isBanned == 0) {
                vois[*nb_vois].x = grid[observedFrame].x;
                vois[*nb_vois].y = grid[observedFrame].y;
                (*nb_vois)++;
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

int Coup_joueur(int nb_vois, T_Case vois[]) {
    int i, choice;
    printf("A vous de jouer !\n");
    printf("Ou voulez vous vous deplacer ? ");
    for (i = 1; i <= nb_vois; i++) {
        printf("%d:(%d,%d)", i, vois[i-1].x, vois[i-1].y);
    if (i!=nb_vois) 
        printf(" | ");
    }
    printf("\nChoix : ");

    //on récupère la valeur du déplacement
    Lire_Entier(&choice, 1, nb_vois);

    return choice;
}

int Coup_Ordi_Hasard(int nb_vois, T_Case vois[]) {
    int choice;
    choice = Hasard(1, nb_vois);

    return choice; //on renvoit le choix pour faire le mouvement
}

int Coup_Ordi_Gagnant(int nb_vois, T_Case vois[], int nim[][VMAX]) {
    int i, choice = -1;
    for (i = 0; i < nb_vois; i++) { 
        if (nim[vois[i].x - 1][vois[i].y - 1] == 0) { //si la case a un nim de 0, on peut aller dessus
            choice = i+1;
            break;
        }
    }
    if (choice == -1)
        choice = Coup_Ordi_Hasard(nb_vois, vois);

    return choice; //on renvoit le choix pour afficher le mouvement
}
