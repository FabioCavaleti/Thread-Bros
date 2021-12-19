#include <cstdio>
#include <iostream>
#include <vector>
#include <curses.h>
#include <ncurses.h>
#include <thread>
#include <mutex>
#include <unistd.h>

//g++ -g trab.cpp -o trab -lncurses -lpthread



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

vector<char> buffer;
std::mutex mtx;
vector<Puzzle> puzzles;
Player m(1,1);
Player l(3,3);

void startPuzzles()
{
    Puzzle p('a', 1, COL-7, 'A', 3, COL-7);
    Puzzle p2('b', 3, COL-6, 'B', 1, COL - 6);
    puzzles.push_back(p);
    puzzles.push_back(p2);
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
    system("clear");
    createTable();
    for(int i = 0; i < COL; i++)
        table[2][i] = '.';
    table[m.getX()][m.getY()] = 'M';
    table[l.getX()][l.getY()] = 'L';

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

void moveM()
{
    mtx.lock();
    if(buffer.size() > 0)
    {
        if(buffer[0] == 'd')
        {
            m.setY(m.getY() + 1);
            buffer.erase(buffer.begin());
        }
        if(buffer[0] == 'a')
        {
            m.setY(m.getY() - 1);
            buffer.erase(buffer.begin());
        }
    }
    mtx.unlock();

}

void moveL()
{

    mtx.lock();
    if(buffer.size() > 0)
    {
        
            if(buffer[0] == 'l')
            {
                l.setY(l.getY() + 1);
                buffer.erase(buffer.begin());
            }
            else if(buffer[0] == 'j')
            {
                l.setY(l.getY() - 1);
                buffer.erase(buffer.begin());
            }
    }
    mtx.unlock();
}

void move()
{
    //Semaphoro aqui.
    system("stty raw");
    char key;
    scanf("%c", &key);
    buffer.push_back(key);
    system("stty cooked");

    std::thread Mario(moveM);
    std::thread Luigi(moveL);

    Mario.join();
    Luigi.join();

}
    


// void colision(Player m, Player l)
// {

// }
// ^[[C
// [C

void game()
{
    move();
    // colision(m, l);
    attMaze();
    
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

// #include <cstdio>
// #include <iostream>
// #include <vector>
// #include <curses.h>
// #include <unistd.h>
// #include <termios.h>



// #define LIN 5
// #define COL 30
// using namespace std;

// char table[LIN][COL];


// void printMaze();




// class Puzzle
// {
//     private:

//         char keyName;
//         int keyPx;
//         int keyPy;
        
//         char doorName;
//         int doorPx;
//         int doorPy;

//     public:

//         Puzzle(char kn, int kpx, int kpy, char dn, int dpx, int dpy)
//         {
//             keyName = kn;
//             keyPx = kpx;
//             keyPy = kpy;
//             doorName = dn;
//             doorPx = dpx;
//             doorPy = dpy;
//         }

//         char getKeyName()
//         {
//             return keyName;        
//         }
//         int getKeyPX()
//         {
//             return keyPx;
//         }
//         int getKeyPY()
//         {
//             return keyPy;
//         }
//         char getDoorName()
//         {
//             return doorName;
//         }
//         int getDoorPX()
//         {
//             return doorPx;
//         }
//         int getDoorPY()
//         {
//             return doorPy;
//         }

//         bool isSolved(int px, int py)
//         {
//             if(px == keyPx && py == keyPy)
//                 return true;
//             else
//                 return false;
//         }

// };

// class Player
// {
//     private:
//         int x;
//         int y;

//     public:
//         Player(int px, int py)
//         {
//             x = px;
//             y = py;
//         }

//         void setX( int px)
//         {
//             x = px;
//         }

//         void setY(int py)
//         {
//             y = py;
//         }

//         int getX()
//         {
//             return x;
//         }

//         int getY()
//         {
//             return y;
//         }



// };


// vector<Puzzle> puzzles;
// Player m(1,1);
// Player l(3,3);

// void startPuzzles()
// {
//     Puzzle p('a', 1, COL-5, 'A', 3, COL-3);
//     puzzles.push_back(p);
// }

// void createTable()
// {
//     for(int i = 0; i < LIN; i++)
//     {
//         for(int j = 0; j < COL; j++)
//         {
//             if(i == 0 || j == 0 || i == LIN - 1 || j == COL - 1)
//                 table[i][j] = '.';
//             else
//                 table[i][j] = ' ';
//         }
//     }
// }

// void attMaze()
// {
//     system("clear");
//     createTable();
//     for(int i = 0; i < COL; i++)
//         table[2][i] = '.';
//     table[m.getX()][m.getY()] = '*';
//     table[l.getX()][l.getY()] = '#';

//     for(int i = 0; i < (int) puzzles.size(); i++)
//     {
//         int kpx = puzzles[i].getKeyPX();
//         int kpy = puzzles[i].getKeyPY();
//         int dpx = puzzles[i].getDoorPX();
//         int dpy = puzzles[i].getDoorPY();
//         table[kpx][kpy] = puzzles[i].getKeyName();
//         table[dpx][dpy] = puzzles[i].getDoorName();
//     }

//     printMaze();
// }



// void printMaze()
// {
//     for(int i = 0; i < LIN; i++)
//     {
//         for(int j = 0; j < COL; j++)
//         {
//             cout << table[i][j];
//         }
//         cout << endl;
//     }
// }

// void move()
// {
//     //Semaphoro aqui.
//     system("stty raw");
//     //  initscr();
//     char key;
//     scanf("%c", &key);
//     // char key = getch();
//     // endwin();

//     system("stty cooked");
//      cout << key << endl;
//     if(key == 'd')
//     {
//         m.setY(m.getY() + 1);
        
        
       
        
//     }
//     if(key == 'a')
//     {
//         m.setY(m.getY() - 1);
        
//     }


//     if(key == '[')
//     {
//         scanf("%c", &key);
//         if(key == 'C')
//         {
//             l.setY(l.getY() + 1);
             
//         }
//         if(key == 'D')
//         {
//             l.setY(l.getY() - 1);
            
//         }

//     }
    

// }
    


// // void colision(Player m, Player l)
// // {

// // }

// void game()
// {
//     move();
//     // colision(m, l);
//     attMaze();
//     // sleep(500);
// }

// int main()
// {
//     termios t;

//     startPuzzles();
 
//     attMaze();
//     while(true)
//     {
//         game();
//     }


//     return 0;
// }