#ifndef _H_PLAYER
#define _H_PLAYER

#include "maze.hpp"
#include "puzzle.hpp"

class Player
{
    private:
        int x, y;
        std::pair<int, int> endPos;

    public:
        Player(int px, int py, std::pair<int, int> endPosition);

        void setX(int px);
        void setY(int py);
        int getX();
        int getY();

        std::pair<int, int> getEndPos();
        void setEndPos(std::pair<int, int> endPosition);

        void moveLeft(Maze &maze, std::vector<Puzzle> &puzzles);
        void moveRight(Maze &maze, std::vector<Puzzle> &puzzles);
        void moveUp(Maze &maze, std::vector<Puzzle> &puzzles);
        void moveDown(Maze &maze, std::vector<Puzzle> &puzzles);
};

#endif