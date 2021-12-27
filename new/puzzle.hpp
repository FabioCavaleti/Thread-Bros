#ifndef _H_PUZZLE
#define _H_PUZZLE

class Puzzle
{
    private:

        char keyName;
        int keyPx;
        int keyPy;
        
        char doorName;
        int doorPx;
        int doorPy;

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