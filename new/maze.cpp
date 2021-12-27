#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "maze.hpp"

Maze::Maze(int rows, int cols)
{
    this->rows = rows;
    this->cols = cols;
}

void Maze::createTable(){
    table.clear();

    std::ifstream infile("mapabasico.txt");
    std::string line;

    while (std::getline(infile, line)) {
        std::vector<char> row;

        for (char &c : line) {
            row.push_back(c);
        }

        table.push_back(row);
    }
}

void Maze::updateTable(){
    table.clear();

    std::ifstream infile("mapabasico.txt");
    std::string line;

    while (std::getline(infile, line)) {
        std::vector<char> row;

        for (char &c : line) {
            row.push_back(c);
        }

        table.push_back(row);
    }

    replaceTable();
}

std::vector<std::vector<char> > Maze::getTable()
{
    return table;
}

void Maze::setTable(int row, int col, char val)
{
    table[row][col] = val;
}

void Maze::replaceTable()
{
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if(table[i][j] == 'M' || table[i][j] == 'L')
            {
                setTable(i, j, ' ');
            }
        }
    }
}