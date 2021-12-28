#include <iostream>
#include <vector>
#include "player.hpp"

Player::Player(int px, int py, std::pair<int, int> endPosition)
{
    x = px;
    y = py;
    endPos = endPosition;
}

void Player::setX(int px)
{
    x = px;
}

void Player::setY(int py)
{
    y = py;
}

int Player::getX()
{
    return x;
}

int Player::getY()
{
    return y;
}

std::pair<int, int> Player::getEndPos()
{
    return endPos;
}

void Player::setEndPos(std::pair<int, int> endPosition)
{
    endPos = endPosition;
}


void Player::moveLeft(Maze &maze, std::vector<Puzzle> &puzzles)
{
    bool canMove = false;
    if(y > 1)
    {
        if(maze.getTable()[x][y - 1] == ' ')
        {
            canMove = true;
        }
        for(int i = 0; i < puzzles.size(); i++)
            if(puzzles[i].isSolved(x, y - 1))
            {
                puzzles.erase(puzzles.begin() + i);
                canMove = true;
            }
        if(x == endPos.first && y -  1 == endPos.second)
            canMove = true;
    }

    if(canMove)
        y -= 1;
}

void Player::moveRight(Maze &maze, std::vector<Puzzle> &puzzles)
{
    bool canMove = false;
    if(y < maze.getDims().second - 2 )
    {
        if(maze.getTable()[x][y + 1] == ' ')
        {
            canMove = true;
        }
        for(int i = 0; i < puzzles.size(); i++)
            if(puzzles[i].isSolved(x, y + 1))
            {
                puzzles.erase(puzzles.begin() + i);
                canMove = true;
            }
        if(x == endPos.first && y + 1 == endPos.second)
            canMove = true;
    }

    if(canMove)
        y += 1;
}

void Player::moveUp(Maze &maze, std::vector<Puzzle> &puzzles)
{
    bool canMove = false;
    if( x > 1 )
    {
        if(maze.getTable()[x - 1][y] == ' ')
        {
            canMove = true;
        }
        for(int i = 0; i < puzzles.size(); i++)
            if(puzzles[i].isSolved(x - 1, y))
            {
                puzzles.erase(puzzles.begin() + i);
                canMove = true;
            }
            if(x - 1 == endPos.first && y == endPos.second)
                canMove = true;
        
    }

    if(canMove)
        x -= 1;

}

void Player::moveDown(Maze &maze, std::vector<Puzzle> &puzzles)
{
    bool canMove = false;
    if( x < maze.getDims().first - 2 )
    {
        if(maze.getTable()[x + 1][y] == ' ')
        {
            canMove = true;
        }
        for(int i = 0; i < puzzles.size(); i++)
            if(puzzles[i].isSolved(x + 1, y))
            {
                puzzles.erase(puzzles.begin() + 1);
                canMove = true;
            }
        if(x + 1 == endPos.first && y == endPos.second)
            canMove = true;
        
    }

    if(canMove)
        x += 1;
}
