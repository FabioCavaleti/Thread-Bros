/*  
    SSC0140 - Sistemas Operacionais I

    Trabalho Prático - Parte 2

    Antonio Rodrigues Rigolino, 11795791
    Breno Lívio Silva de Almeida, 10276675
    Favio Henrique Alves Cavaleti, 11200550

    ----------------------------------------------------------------

    Este arquivo de código contém as funções para leitura e criação dos labirintos, além de funções para os modificar e imprimir.

*/

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "maze.hpp"

/*
 * Construtor da classe Maze.
 * 
 * Parâmetros: int level, define o nível do labirinto a ser criado e carregado.
 * 
 */
Maze::Maze(int level)
{
    this->level = level;
}

/*
 * Gera labirinto baseado em um arquivo de texto de acordo com o nível informado.
 * 
 */
void Maze::createTable(){

    std::ifstream infile;

    if (level == 1){
        infile = std::ifstream("levels/level1.txt");
    } else if (level == 2){
        infile = std::ifstream("levels/level2.txt");
    } else if (level == 3){
        infile = std::ifstream("levels/level3.txt");
    } else if (level == 4){
        infile = std::ifstream("levels/level4.txt");
    } 

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

    infile.close();
}

/*
 * Atualiza labirinto lendo o arquivo de texto de acordo com o nível informado, mas alterando o labirinto para o estado atual.
 *
 */
void Maze::updateTable(){
    table.clear();

    std::ifstream infile;

    if (level == 1){
        infile = std::ifstream("levels/level1.txt");
    } else if (level == 2){
        infile = std::ifstream("levels/level2.txt");
    } else if (level == 3){
        infile = std::ifstream("levels/level3.txt");
    } else if (level == 4){
        infile = std::ifstream("levels/level4.txt");
    } 
 
    std::string line;

    while (std::getline(infile, line)) {
        std::vector<char> row;

        for (char &c : line) {
            row.push_back(c);
        }

        table.push_back(row);
    }

    replaceTable();

    infile.close();
}

/*
 * Retorna o labirinto.
 * 
 * Retorna: std::vector<std::vector<char> > table, labirinto.
 * 
 */
std::vector<std::vector<char> > Maze::getTable()
{
    return table;
}

/*
 * Retorna a dimensão do labirinto.
 * 
 * Retorna: std::pair<int, int> pair, dimensão do labirinto em linhas e colunas.
 * 
 */
std::pair<int, int> Maze::getDims()
{
    return std::make_pair(rows, cols);
}

/*
 * Define valor para uma dada posição no labirinto.
 * 
 * Parâmetros: int row, posição de linha; int col, posição de coluna; char val, valor a ser inserido.
 * 
 */
void Maze::setTable(int row, int col, char val)
{
    table[row][col] = val;
}

/*
 * Troca valores que representam os irmãos e puzzles por espaços em branco. Isso é necessário devido à característica dinâmica do labirinto, com esses
 * objetos tendo a possibilidade de mudarem de posição ou sumirem depois que o labirinto inicial é carregado. Outra função é responsável por propriamente colocar
 * os objetos nos devidos lugares.
 *
 */
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

/*
 * Imprime o labirinto.
 *
 */
void Maze::printTable()
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            std::cout << table[i][j];
        }
        std::cout << std::endl;
    }
}