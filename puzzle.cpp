#include "puzzle.hpp"

Puzzle::Puzzle(char kn, int kpx, int kpy, char dn, int dpx, int dpy)
{
    keyName = kn;
    keyPx = kpx;
    keyPy = kpy;
    doorName = dn;
    doorPx = dpx;
    doorPy = dpy;
}

char Puzzle::getKeyName()
{
    return keyName;        
}

int Puzzle::getKeyPX()
{
    return keyPx;
}

int Puzzle::getKeyPY()
{
    return keyPy;
}

char Puzzle::getDoorName()
{
    return doorName;
}

int Puzzle::getDoorPX()
{
    return doorPx;
}

int Puzzle::getDoorPY()
{
    return doorPy;
}

bool Puzzle::isSolved(int px, int py)
{
    if(px == keyPx && py == keyPy)
        return true;
    else
        return false;
}