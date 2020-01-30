/*
constant.h
------------
AvaN0x
*/
#ifndef DEF_DIFFICULTY
#define DEF_DIFFICULTY

    #define SIZEMIN 5
    #define SIZEMAX 30

    typedef enum {
        DEBUTANT = 1,
        MOYEN,
        EXPERT,
        VIRTUOSE,
        MULTIPLAYER
    } Difficulty;

    typedef enum {
        PLAYER1 = 1,
        PLAYER2
    } Player;

    typedef struct {
            int nrow;
            int ncol;
            Difficulty niveau;
            Player nextPlayer;
            int nban;
    } Plate;

#endif