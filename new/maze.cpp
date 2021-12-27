#include "maze.hpp"



Maze::Maze(int rows, int cols)
{
    this->rows = rows;
    this->cols = cols;
}

void Maze::createTable(){
    table.clear();

    for(int i = 0; i < rows; i++)
    {
        std::vector<char> v1;
        for(int j = 0; j < cols; j++)
        {
            if(i == 0 || j == 0 || i == rows - 1 || j == cols - 1)
                v1.push_back('.');
            else
                v1.push_back(' ');
        }
        table.push_back(v1);
    }
}

std::vector<std::vector<char> > Maze::getTable()
{
    return table;
}

void Maze::setTable(int row, int col, char val)
{
    table[row][col] = val;
}