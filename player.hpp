#ifndef _H_PLAYER
#define _H_PLAYER

#include "maze.hpp"
#include "puzzle.hpp"

class Player
{
    private:
        int x, y;
        std::pair<int, int> endM, endL;

    public:
        Player(int px, int py, std::pair<int, int> endMPos, std::pair<int, int> endLPos);

        void setX(int px);
        void setY(int py);
        int getX();
        int getY();

        std::pair<int, int> getEndM();
        std::pair<int, int> getEndL();
        void setEndM(std::pair<int, int> endMPos);
        void setEndL(std::pair<int, int> endMPos);

        void moveLeft(Maze &maze, std::vector<Puzzle> &puzzles);
        void moveRight(Maze &maze, std::vector<Puzzle> &puzzles);
        void moveUp(Maze &maze, std::vector<Puzzle> &puzzles);
        void moveDown(Maze &maze, std::vector<Puzzle> &puzzles);
};

#endif