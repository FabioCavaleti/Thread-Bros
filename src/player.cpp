/*  
    SSC0140 - Sistemas Operacionais I

    Trabalho Prático - Parte 2

    Antonio Rodrigues Rigolino, 11795791
    Breno Lívio Silva de Almeida, 10276675
    Favio Henrique Alves Cavaleti, 11200550

    ----------------------------------------------------------------

    Este arquivo de código contém as funções para definição dos jogadores, com suas respectivas coordenadas e direções que podem ir.
    Também conta com a lógica da movimentação baseado no conteúdo do labirinto.

*/

#include <iostream>
#include <vector>
#include "player.hpp"

/*
 * Construtor da classe Player.
 * 
 * Parâmetros: int px, posição x do personagem; int py, posição y do personagem; std::pair<int, int> endPosition, posição destino do personagem.
 * 
 */
Player::Player(int px, int py, std::pair<int, int> endPosition)
{
    x = px;
    y = py;
    endPos = endPosition;
}

/*
 * Define posição x do personagem.
 * 
 * Parâmetros: int px, posição x do personagem.
 * 
 */
void Player::setX(int px)
{
    x = px;
}

/*
 * Define posição y do personagem.
 * 
 * Parâmetros: int py, posição y do personagem.
 * 
 */
void Player::setY(int py)
{
    y = py;
}

/*
 * Retorna posição x do personagem.
 * 
 * Retorna: int x, posição x do personagem.
 * 
 */
int Player::getX()
{
    return x;
}

/*
 * Retorna posição y do personagem.
 * 
 * Retorna: int y, posição y do personagem.
 * 
 */
int Player::getY()
{
    return y;
}

/*
 * Retorna posição destino do personagem.
 * 
 * Retorna: std::pair<int, int> endPos, posição destino do personagem.
 * 
 */
std::pair<int, int> Player::getEndPos()
{
    return endPos;
}

/*
 * Define posição destino do personagem.
 * 
 * Parâmetros: std::pair<int, int> endPosition, posição destino do personagem.
 * 
 */
void Player::setEndPos(std::pair<int, int> endPosition)
{
    endPos = endPosition;
}


/*
 * Move o jogador para a esquerda verificando a lógica se o jogador pode se mover de acordo com o conteúdo do labirinto.
 * 
 * Parâmetros: Maze &maze, referência do objeto de labirinto; std::vector<Puzzle> &puzzles, referência de objetos dos puzzles.
 * 
 */
void Player::moveLeft(Maze &maze, std::vector<Puzzle> &puzzles)
{
    bool canMove = false;
    if(y > 1)
    {
        if(maze.getTable()[x][y - 1] == ' ')  // Se para esquerda o espaço estiver em branco, pode mover
        {
            canMove = true;
        }
        for(int i = 0; i < (int) puzzles.size(); i++)
            if(puzzles[i].isSolved(x, y - 1))  // Já verifica se tem uma chave para esquerda
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

/*
 * Move o jogador para a direita verificando a lógica se o jogador pode se mover de acordo com o conteúdo do labirinto.
 * 
 * Parâmetros: Maze &maze, referência do objeto de labirinto; std::vector<Puzzle> &puzzles, referência de objetos dos puzzles.
 * 
 */
void Player::moveRight(Maze &maze, std::vector<Puzzle> &puzzles)
{
    bool canMove = false;
    if(y < maze.getDims().second - 2)
    {
        if(maze.getTable()[x][y + 1] == ' ') // Se para direita o espaço estiver em branco, pode mover
        {
            canMove = true;
        }
        for(int i = 0; i < (int) puzzles.size(); i++)
            if(puzzles[i].isSolved(x, y + 1)) // Já verifica se tem uma chave para direita
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

/*
 * Move o jogador para cima verificando a lógica se o jogador pode se mover de acordo com o conteúdo do labirinto.
 * 
 * Parâmetros: Maze &maze, referência do objeto de labirinto; std::vector<Puzzle> &puzzles, referência de objetos dos puzzles.
 * 
 */
void Player::moveUp(Maze &maze, std::vector<Puzzle> &puzzles)
{
    bool canMove = false;
    if(x > 1)
    {
        if(maze.getTable()[x - 1][y] == ' ') // Se para cima o espaço estiver em branco, pode mover
        {
            canMove = true;
        }
        for(int i = 0; i < (int) puzzles.size(); i++)
            if(puzzles[i].isSolved(x - 1, y))
            {
                puzzles.erase(puzzles.begin() + i); // Já verifica se tem uma chave acima
                canMove = true;
            }

        if(x - 1 == endPos.first && y == endPos.second)
            canMove = true;
        
    }

    if(canMove)
        x -= 1;

}

/*
 * Move o jogador para baixo verificando a lógica se o jogador pode se mover de acordo com o conteúdo do labirinto.
 * 
 * Parâmetros: Maze &maze, referência do objeto de labirinto; std::vector<Puzzle> &puzzles, referência de objetos dos puzzles.
 * 
 */
void Player::moveDown(Maze &maze, std::vector<Puzzle> &puzzles)
{
    bool canMove = false;
    if(x < maze.getDims().first - 2)
    {
        if(maze.getTable()[x + 1][y] == ' ') // Se para baixo o espaço estiver em branco, pode mover
        {
            canMove = true;
        }
        for(int i = 0; i < (int) puzzles.size(); i++)
            if(puzzles[i].isSolved(x + 1, y)) // Já verifica se tem uma chave abaixo
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
