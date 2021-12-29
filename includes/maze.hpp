#ifndef _H_MAZE
#define _H_MAZE

class Maze
{
    private:
        int level, rows, cols; // Nível do labirinto, linhas e colunas do labirinto
        std::vector<std::vector<char> > table; // Tabela do labirinto

    public:
        Maze(int level);

        void createTable();
        void updateTable();
        void replaceTable();
        std::vector<std::vector<char> > getTable();
        std::pair<int, int> getDims();
        void setTable(int row, int col, char val);
        void printTable();
};

#endif