#include <bits/stdc++.h>

#define LIN 5
#define COL 30
using namespace std;

char table[LIN][COL];

void createTable()
{
    for(int i = 0; i < LIN; i++)
    {
        for(int j = 0; j < COL; j++)
        {
            if(i == 0 || j == 0 || i == LIN - 1 || j == COL - 1)
                table[i][j] = '.';
            else
                table[i][j] = ' ';
        }
    }
}

void createMaze()
{
    createTable();
    for(int i = 0; i < COL; i++)
        table[2][i] = '.';
    table[1][1] = '*';
    table[3][1] = '#';
    table[1][COL-5] = 'A';
    table[3][COL - 3] = 'a';
}

void printMaze()
{
    for(int i = 0; i < LIN; i++)
    {
        for(int j = 0; j < COL; j++)
        {
            cout << table[i][j];
        }
        cout << endl;
    }
}

int main()
{
    createMaze();
    printMaze();


    return 0;
}