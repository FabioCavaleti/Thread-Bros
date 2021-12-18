#include <cstdio>
#include <iostream>
#include <vector>
#include <windows.h>
#include <conio.h>


#define VK_W 0x57
#define VK_S 0x53
#define VK_A 0x41
#define VK_D 0x44

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 77
#define KEY_RIGHT 75

#define LIN 5
#define COL 30
using namespace std;

char table[LIN][COL];


void printMaze();

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

        Puzzle(char kn, int kpx, int kpy, char dn, int dpx, int dpy)
        {
            keyName = kn;
            keyPx = kpx;
            keyPy = kpy;
            doorName = dn;
            doorPx = dpx;
            doorPy = dpy;
        }

        char getKeyName()
        {
            return keyName;        
        }
        int getKeyPX()
        {
            return keyPx;
        }
        int getKeyPY()
        {
            return keyPy;
        }
        char getDoorName()
        {
            return doorName;
        }
        int getDoorPX()
        {
            return doorPx;
        }
        int getDoorPY()
        {
            return doorPy;
        }

        bool isSolved(int px, int py)
        {
            if(px == keyPx && py == keyPy)
                return true;
            else
                return false;
        }

};

class Player
{
    private:
        int x;
        int y;

    public:
        Player(int px, int py)
        {
            x = px;
            y = py;
        }

        void setX( int px)
        {
            x = px;
        }

        void setY(int py)
        {
            y = py;
        }

        int getX()
        {
            return x;
        }

        int getY()
        {
            return y;
        }



};


vector<Puzzle> puzzles;
Player m(1,1);
Player l(3,3);

void startPuzzles()
{
    Puzzle p('a', 1, COL-5, 'A', 3, COL-3);
    puzzles.push_back(p);
}

void createTable()
{
    for(int i = 0; i < LIN; i++)
    {
        for(int j = 0; j < COL; j++)
        {
            if(i == 0 || j == 0 || i == LIN - 1 || j == COL - 1)
                table[i][j] = '.';
            else
                table[i][j] = ' ';
        }
    }
}

void attMaze()
{
    system("CLS");
    createTable();
    for(int i = 0; i < COL; i++)
        table[2][i] = '.';
    table[m.getX()][m.getY()] = '*';
    table[l.getX()][l.getY()] = '#';

    for(int i = 0; i < (int) puzzles.size(); i++)
    {
        int kpx = puzzles[i].getKeyPX();
        int kpy = puzzles[i].getKeyPY();
        int dpx = puzzles[i].getDoorPX();
        int dpy = puzzles[i].getDoorPY();
        table[kpx][kpy] = puzzles[i].getKeyName();
        table[dpx][dpy] = puzzles[i].getDoorName();
    }

    printMaze();
}



void printMaze()
{
    for(int i = 0; i < LIN; i++)
    {
        for(int j = 0; j < COL; j++)
        {
            cout << table[i][j];
        }
        cout << endl;
    }
}

void move()
{
    //Semaphoro aqui.
    char key = _getch();
    if(key == 'd')
    {
        m.setY(m.getY() + 1);
    }
    if(key == 'a')
    {
        m.setY(m.getY() - 1);
    }


    if(key == KEY_RIGHT)
    {
        l.setY(l.getY() - 1);
    }
    if(key == KEY_LEFT)
    {
        l.setY(l.getY() + 1);
    }
    

}
    


// void colision(Player m, Player l)
// {

// }

void game()
{
    move();
    // colision(m, l);
    attMaze();
    Sleep(500);
}

int main()
{

    startPuzzles();
 
    attMaze();
    while(true)
    {
        game();
    }


    return 0;
}