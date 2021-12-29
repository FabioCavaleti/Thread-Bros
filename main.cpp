#include <cstdio>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
#include <unistd.h>
#include <fstream>
#include "maze.hpp"
#include "puzzle.hpp"
#include "player.hpp"

std::vector<char> buffer;
std::mutex mtx;

void printScreen(int select);


void attMaze(Maze &maze, std::vector<Puzzle> &puzzles, Player &m, Player &l)
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


void moveM(Maze &maze, std::vector<Puzzle> &puzzles, Player &m)
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

void moveL(Maze &maze, std::vector<Puzzle> &puzzles, Player &l)
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


void endGame(int select)
{
    if (select == 1){
        system("clear");
        std::cout << "Você encerrou o jogo." << std::endl;
    } else {
        printScreen(5);
    }
    
}

int move(Maze &maze, std::vector<Puzzle> &puzzles, Player &m, Player &l)
{
    if(m.getX() == m.getEndPos().first && m.getY() == m.getEndPos().second && l.getX() == l.getEndPos().first && l.getY() == l.getEndPos().second)
        return -1;

    system("stty raw");
    char key;
    scanf("%c", &key);

    if(key == ' ') // LIDAR COM ISSO AQUI
    {
        system("stty cooked");
        return 1;
    }

    buffer.push_back(key);
    system("stty cooked");

    std::thread Mario(moveM, std::ref(maze), std::ref(puzzles), std::ref(m));
    std::thread Luigi(moveL, std::ref(maze), std::ref(puzzles), std::ref(l));

    Mario.join();
    Luigi.join();

    return 0;
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

    return std::make_pair(x, y);
}

void setObjectsMaze(Maze &maze, std::vector<Puzzle> &puzzles, Player &m, Player &l)
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
    m.setEndPos(find(maze, '+'));
    l.setEndPos(find(maze, '-'));

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

void printScreen(int select){
    system("clear");

    std::ifstream infile;

    if (select == -2){
        infile = std::ifstream("screens/main.txt");
    } else if (select == -1) {
        infile = std::ifstream("screens/instructions.txt");
    } else if (select == 0) {
        infile = std::ifstream("screens/instructions2.txt");
    } else if (select == 1) {
        infile = std::ifstream("screens/level1.txt");
    } else if (select == 2) {
        infile = std::ifstream("screens/level2.txt");
    } else if (select == 3) {
        infile = std::ifstream("screens/level3.txt");
    } else if (select == 4) {
        infile = std::ifstream("screens/level4.txt");
    } else if (select == 5) {
        infile = std::ifstream("screens/congrats.txt");
    }

    std::vector<std::vector<char> > screen;

    std::string line;

    while (std::getline(infile, line)) {
        std::vector<char> row;

        for (char &c : line) {
            row.push_back(c);
        }

        screen.push_back(row);
    }

    for (int i = 0; i < screen.size(); i++)
    {
        for (int j = 0; j < screen[i].size(); j++)
        {
            std::cout << screen[i][j];
        }
        std::cout << std::endl;
    }

    infile.close();
}


int main()
{
    printScreen(-2);

    char key;
    scanf("%c", &key);

    printScreen(-1);

    scanf("%c", &key);

    printScreen(0);

    scanf("%c", &key);

    int end = 0;

    for (int i = 1; i <= 4; i++) {
        printScreen(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(1500));

        Maze maze(i);
        std::vector<Puzzle> puzzles;
        Player m(0, 0, std::make_pair(0, 0));
        Player l(0, 0, std::make_pair(0, 0));

        setObjectsMaze(maze, puzzles, m, l);

        while(true)
        {     
            attMaze(maze, puzzles, m, l);
            maze.printTable();
            end = move(maze, puzzles, m, l);
            if (end == -1){
                break;
            } else if (end == 1){
                break;
            }
        }
        if (end == 1)
            break;
    }

    endGame(end);

    return 0;
}