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

vector<char> buffer;
std::mutex mtx;

void attMaze(Maze &maze, vector<Puzzle> &puzzles, Player &m, Player &l)
{
    system("clear");

    maze.updateTable();

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
}


void moveM(Maze &maze, vector<Puzzle> &puzzles, Player &m)
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

void moveL(Maze &maze, vector<Puzzle> &puzzles, Player &l)
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

void endGame()
{
    system("clear");
    cout << "Parabéns!!\nOs irmaos Threads conseguiram superar o labirinto!!" << endl;
    exit(1);
}

void move(Maze &maze, vector<Puzzle> &puzzles, Player &m, Player &l)
{
    if(m.getX() == m.getEndM().first && m.getY() == m.getEndM().second && l.getX() == l.getEndL().first && l.getY() == l.getEndL().second)
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

    std::thread Mario(moveM, std::ref(maze), std::ref(puzzles), std::ref(m));
    std::thread Luigi(moveL, std::ref(maze), std::ref(puzzles), std::ref(l));

    Mario.join();
    Luigi.join();
}

std::pair<int, int> find(Maze &maze, char key)
{
    int x = -1, y = -1;
    
    for(int i = 0; i < maze.getDims().first; i++){
        for(int j = 0; j < maze.getDims().second; j++){
            if(maze.getTable()[i][j] == key)
            {
                x = i;
                y = j;
            }
        }
    }

    return make_pair(x, y);
}

//std::pair<int, int> endM, endL;
void setObjectsMaze(Maze &maze, vector<Puzzle> &puzzles, Player &m, Player &l)
{
    maze.createTable();

    auto dims = maze.getDims();

    auto table = maze.getTable();

    // Pegamos a posição do Mario e Luigi no mapa
    std::pair<int, int> posMario = find(maze, 'M');
    std::pair<int, int> posLuigi = find(maze, 'L');

    // Salvamos as posições deles
    m.setX(posMario.first);
    m.setY(posMario.second);
    l.setX(posLuigi.first);
    l.setY(posLuigi.second);

    // Saída dos personagens
    auto endM = find(maze, '+');
    auto endL = find(maze, '-');

    m.setEndM(endM);
    m.setEndL(endL);
    l.setEndM(endM);
    l.setEndL(endL);

    // Chaves e portas

    char key = 'a';

    for (int i = 0; i < 10; i++)
    {
        std::pair<int, int> keyPos = find(maze, key + i);

        if(keyPos.first == -1)
            break;

        char door = key + i - 32;

        std::pair<int, int> doorPos = find(maze, door);

        Puzzle p(key + i, keyPos.first, keyPos.second, door, doorPos.first, doorPos.second);
        puzzles.push_back(p);

    }
}


int main()
{
    Maze maze(2);
    vector<Puzzle> puzzles;
    Player m(0, 0, make_pair(0, 0), make_pair(0, 0));
    Player l(0, 0, make_pair(0, 0), make_pair(0, 0));

    setObjectsMaze(maze, puzzles, m, l);

    while(true)
    {     
        attMaze(maze, puzzles, m, l);
        maze.printTable();
        move(maze, puzzles, m, l);
    }

    return 0;
}