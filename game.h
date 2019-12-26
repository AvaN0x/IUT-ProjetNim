typedef struct T_Case{
        int x;
        int y;
} T_Case;

void Lire_Entier(int *res, int min, int max);
void Parametres(int *nlig, int *ncol, int *niveau, int *next, int *nban);
int Hasard(int min, int max);
void fillGrid(char grid[], int nlig, int ncol);
void displayGrid(char grid[], T_Case ban[], T_Case pion, int nlig, int ncol, int nban);
char checkFrame(int x, int y, int k, char grid[], T_Case ban[], T_Case pion, int nban);
void Hasard_Ban(int nban, T_Case ban[], int nlig, int ncol);
void Calcul_Nimbers(int nim[], int nlig, int ncol);



// fonction pour voir les nim (dev)
//void niim(int nim[], int nlig, int ncol);




