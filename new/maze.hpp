#ifndef _H_MAZE
#define _H_MAZE

#include <vector>

class Maze
{
    private:
        int rows, cols;
        std::vector<std::vector<char> > table;

    public:
        Maze(int rows, int cols);

        void createTable();
        std::vector<std::vector<char> > getTable();
        void setTable(int row, int col, char val);
};

#endif