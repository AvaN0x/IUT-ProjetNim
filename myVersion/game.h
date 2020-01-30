#ifndef DEF_GAME
#define DEF_GAME
    #include "constant.h"

    ////////////////////////////////////////
    //fonctions à la création de la partie//
    ////////////////////////////////////////
    void Parametres(Plate *p);
    void fillNimber(int * grid, Plate p);
    void dispNim(int * grid, Plate p); // pour voir la génération des nim
    void randomBan(int * grid, Plate p);


    /////////////////////////////////////////
    //fonctions du déroulement de la partie//
    /////////////////////////////////////////
    void launchGame();
    void dispGrid(int * grid, Plate p, int pion, int * vois, int nb_vois);
    int isVois(int frame, int * vois, int nb_vois);
    void findVois(Plate p, int *vois, int * grid, int pion, int *nbVois);
    int userMove(int nbVois);
    int randomMoveAI(int nbVois);
    int winningMoveAI(int nbVois, int * vois, int * grid);


#endif