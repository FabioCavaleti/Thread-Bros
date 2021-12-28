#include <cstdio>
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <unistd.h>
#include "maze.hpp"
#include "puzzle.hpp"
#include "player.hpp"

using namespace std;

vector<Puzzle> puzzles;
std::pair<int, int> endM, endL;
Maze maze(1);

Player m(0, 0, make_pair(0, 0), make_pair(0, 0));
Player l(0, 0, make_pair(0, 0), make_pair(0, 0));

void printMaze();
void endGame();

vector<char> buffer;
std::mutex mtx;


void attMaze()
{
    system("clear");

    maze.updateTable();
    
    //maze.setTable(endM.first, endM.second, '+');
    //maze.setTable(endL.first, endL.second, '-');

    maze.setTable(m.getX(), m.getY(), 'M');
    maze.setTable(l.getX(), l.getY(), 'L');

    for(int i = 0; i < (int) puzzles.size(); i++)
    {
        int kpx = puzzles[i].getKeyPX();
        int kpy = puzzles[i].getKeyPY();
        int dpx = puzzles[i].getDoorPX();
        int dpy = puzzles[i].getDoorPY();
        maze.setTable(kpx, kpy, puzzles[i].getKeyName());
        maze.setTable(dpx, dpy, puzzles[i].getDoorName());
    }

    printMaze();
}


void printMaze()
{
    for(int i = 0; i < maze.getDims().first; i++)
    {
        for(int j = 0; j < maze.getDims().second; j++)
        {
            cout << maze.getTable()[i][j];
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
            m.moveRight(maze, puzzles);
            buffer.erase(buffer.begin());
        }
        else if(buffer[0] == 'a')
        {
            m.moveLeft(maze, puzzles);
            buffer.erase(buffer.begin());
        }
        else if(buffer[0] == 'w')
        {
            m.moveUp(maze, puzzles);
            buffer.erase(buffer.begin());
        }
        else if(buffer[0] == 's' )
        {
            m.moveDown(maze, puzzles);
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
            l.moveRight(maze, puzzles);
            buffer.erase(buffer.begin());
        }
        else if(buffer[0] == 'j')
        {
            // l.setY(l.getY() - 1);
            l.moveLeft(maze, puzzles);
            buffer.erase(buffer.begin());
        }
        else if(buffer[0] == 'i')
        {
            l.moveUp(maze, puzzles);
            buffer.erase(buffer.begin());
        }
        else if(buffer[0] == 'k')
        {
            l.moveDown(maze, puzzles);
            buffer.erase(buffer.begin());
        }
    }
    mtx.unlock();
}

void move()
{
    if(m.getX() == endM.first && m.getY() == endM.second && l.getX() ==  endL.first && l.getY() == endL.second)
        endGame();

    system("stty raw");
    char key;
    scanf("%c", &key);

    if(key == ' ')
    {
        system("stty cooked");
        exit(1);
    }

    buffer.push_back(key);
    system("stty cooked");

    std::thread Mario(moveM);
    std::thread Luigi(moveL);

    Mario.join();
    Luigi.join();
}
    
void endGame()
{
    system("clear");
    cout << "Parabéns!!\nOs irmaos Threads conseguiram superar o labirinto!!" << endl;
    exit(1);
}

std::pair<int, int> find(auto table, char key)
{
    int x = -1, y = -1;
    
    for(int i = 0; i < maze.getDims().first; i++){
        for(int j = 0; j < maze.getDims().second; j++){
            if(table[i][j] == key)
            {
                x = i;
                y = j;
            }
        }
    }

    return make_pair(x, y);
}


void setObjectsMaze()
{
    maze.createTable();

    auto dims = maze.getDims();

    auto table = maze.getTable();

    // Pegamos a posição do Mario e Luigi no mapa
    std::pair<int, int> posMario = find(table, 'M');
    std::pair<int, int> posLuigi = find(table, 'L');

    // Salvamos as posições deles
    m.setX(posMario.first);
    m.setY(posMario.second);
    l.setX(posLuigi.first);
    l.setY(posLuigi.second);

    // Saída dos personagens
    endM = find(table, '+');
    endL = find(table, '-');

    m.setEndM(endM);
    m.setEndL(endL);
    l.setEndM(endM);
    l.setEndL(endL);

    // Chaves e portas

    char key = 'a';

    for (int i = 0; i < 10; i++)
    {
        std::pair<int, int> keyPos = find(table, key + i);

        if(keyPos.first == -1)
            break;

        char door = key + i - 32;

        //cout << keyPos.first << " " << keyPos.second << endl;

        //cout << key + i << endl;

        std::pair<int, int> doorPos = find(table, door);

        Puzzle p(key + i, keyPos.first, keyPos.second, door, doorPos.first, doorPos.second);
        puzzles.push_back(p);

    }
}



int main()
{
    setObjectsMaze();

    while(true)
    {     
        attMaze();
        move();
    }

    return 0;
}