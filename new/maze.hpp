#ifndef _H_MAZE
#define _H_MAZE

class Maze
{
    private:
        int level, rows, cols;
        std::vector<std::vector<char> > table;

    public:
        Maze(int level);

        void createTable();
        void updateTable();
        void replaceTable();
        std::vector<std::vector<char> > getTable();
        std::pair<int, int> getDims();
        void setTable(int row, int col, char val);
};

#endif