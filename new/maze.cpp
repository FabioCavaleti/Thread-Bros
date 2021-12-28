#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "maze.hpp"

Maze::Maze(int level)
{
    this->level = level;
}

void Maze::createTable(){

    std::ifstream infile("mapabasico.txt");


    std::string line;

    while (std::getline(infile, line)) {
        std::vector<char> row;

        for (char &c : line) {
            row.push_back(c);
        }

        cols = row.size();

        table.push_back(row);
    }

    rows = table.size();
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

std::pair<int, int> Maze::getDims()
{
    return std::make_pair(rows, cols);
}


void Maze::setTable(int row, int col, char val)
{
    table[row][col] = val;
}

void Maze::replaceTable()
{
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if(table[i][j] == 'M' || table[i][j] == 'L' || (table[i][j] >= 97 && table[i][j] <= 106) || (table[i][j] >= 65 && table[i][j] <= 74))
            {
                setTable(i, j, ' ');
            }
        }
    }
}