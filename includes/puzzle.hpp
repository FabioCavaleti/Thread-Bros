#ifndef _H_PUZZLE
#define _H_PUZZLE

class Puzzle
{
    private:

        char keyName; // Valor da chave
        int keyPx; // Posição x da chave
        int keyPy; // Posição y da chave
        
        char doorName; // Valor da porta
        int doorPx; // Posição x da porta
        int doorPy; // Posição y da porta

    public:

        Puzzle(char kn, int kpx, int kpy, char dn, int dpx, int dpy);

        char getKeyName();
        int getKeyPX();
        int getKeyPY();
        char getDoorName();
        int getDoorPX();
        int getDoorPY();
        bool isSolved(int px, int py);
};

#endif