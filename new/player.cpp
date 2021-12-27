#include <iostream>
#include "player.hpp"

Player::Player(std::pair<int, int> pos, std::pair<int, int> endPos, char table[][30])
{
    this->pos = pos;
    this->endPos = endPos;
    this->table = table;
}

void Player::setPos(std::pair<int, int> pos)
{
    this->pos = pos;
}

std::pair<int, int> Player::getPos()
{
    return pos;
}

void Player::setEndPos(std::pair<int, int> endPos)
{
    this->endPos = endPos;
}

std::pair<int, int> Player::getEndPos()
{
    return endPos;
}

void Player::moveLeft()
{
    bool canMove = false;
    
    if(y > 1)
    {
        if(table[x][y - 1] == ' ')
        {
            canMove = true;
        }
        for(int i = 0; i < puzzles.size(); i++)
            if(puzzles[i].isSolved(x, y - 1))
            {
                puzzles.erase(puzzles.begin() + i);
                canMove = true;
            }
        if((x == endM.first && y -  1 == endM.second) || (x == endL.first && y - 1 == endL.second))
            canMove = true;
    }

    if(canMove)
        y -= 1;
}

void Player::moveRight()
{
    bool canMove = false;

    if(y < COL - 2 )
    {
        if(table[x][y + 1] == ' ')
        {
            canMove = true;
        }
        for(int i = 0; i < puzzles.size(); i++)
            if(puzzles[i].isSolved(x, y + 1))
            {
                puzzles.erase(puzzles.begin() + i);
                canMove = true;
            }
        if((x == endM.first && y + 1 == endM.second) || (x == endL.first && y + 1 == endL.second))
            canMove = true;
    }

    if(canMove)
        y += 1;
}

void Player::moveUp()
{
    bool canMove = false;

    if( x > 1 )
    {
        if(table[x - 1][y] == ' ')
        {
            canMove = true;
        }
        for(int i = 0; i < puzzles.size(); i++)
            if(puzzles[i].isSolved(x - 1, y))
            {
                puzzles.erase(puzzles.begin() + i);
                canMove = true;
            }
            if((x - 1 == endM.first && y == endM.second) || (x - 1 == endL.first && y == endL.second))
                canMove = true;
        
    }

    if(canMove)
        x -= 1;

}

void Player::moveDown()
{
    bool canMove = false;

    if(x < LIN - 2)
    {
        if(table[x + 1][y] == ' ')
        {
            canMove = true;
        }
        for(int i = 0; i < puzzles.size(); i++)
            if(puzzles[i].isSolved(x + 1, y))
            {
                puzzles.erase(puzzles.begin() + 1);
                canMove = true;
            }
        if((x + 1 == endM.first && y == endM.second) || (x + 1 == endL.first && y == endL.second))
            canMove = true;
        
    }

    if(canMove)
        x += 1;
}
