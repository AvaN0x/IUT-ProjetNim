#ifndef DEF_GAME
#define DEF_GAME

    #define VMIN 5
    #define VMAX 30

    typedef struct {
            int x;
            int y;
    } T_Case;

    /////////////
    //utilities//
    /////////////
    void Lire_Entier(int *res, int min, int max);
    int Hasard(int min, int max);


    ////////////////////////////////////////
    //fonctions à la création de la partie//
    ////////////////////////////////////////
    void Parametres(int *nlig, int *ncol, int *niveau, int *next, int *nban);
    void fillGrid(T_Case *grid, int nlig, int ncol);
    void Hasard_Ban(int nban, T_Case *ban, int nlig, int ncol);
    void Calcul_Nimbers(int nim[][VMAX], int nlig, int ncol);
    void dispNim(int nim[][VMAX], int nlig, int ncol); // pour voir la génération des nim
    void displayGrid(T_Case *grid, T_Case *ban, T_Case pion, int nlig, int ncol, int nban, int nb_vois, T_Case *vois);


    /////////////////////////////////////////
    //fonctions du déroulement de la partie//
    /////////////////////////////////////////
    void launchGame();
    void Deplacement(T_Case *pion, int rangVois, T_Case *vois);
    void Voisines(int *nb_vois, T_Case *vois, int nlig, int ncol, T_Case *grid, T_Case *ban, int nban, T_Case pion);
    int Coup_joueur(int nb_vois, T_Case *vois);
    int Coup_Ordi_Hasard(int nb_vois, T_Case *vois);
    int Coup_Ordi_Gagnant(int nb_vois, T_Case *vois, int nim[][VMAX]);

#endif