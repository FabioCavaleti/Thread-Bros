/*  
    SSC0140 - Sistemas Operacionais I

    Trabalho Prático - Parte 2

    Antonio Rodrigues Rigolino, 11795791
    Breno Lívio Silva de Almeida, 10276675
    Favio Henrique Alves Cavaleti, 11200550

    ----------------------------------------------------------------

    Este arquivo de código contém as funções para a manipulação dos puzzles dos labirintos. Os puzzles representam a ideia de chave e porta.
    Se um jogador pega uma chave, uma porta é aberta em um lugar do labirinto.

*/

#include "puzzle.hpp"

/*
 * Construtor da classe Puzzle.
 * 
 * Parâmetros: char kn, valor da chave; int kpx, posição x da chave; int kpy, posição y da chave; 
 *              char dn, valor da porta; int dpx, posição x da porta; int dpy, posição y da porta.
 * 
 */
Puzzle::Puzzle(char kn, int kpx, int kpy, char dn, int dpx, int dpy)
{
    keyName = kn;
    keyPx = kpx;
    keyPy = kpy;
    doorName = dn;
    doorPx = dpx;
    doorPy = dpy;
}

/*
 * Retorna valor da chave.
 * 
 * Retorna: char keyName, valor da chave.
 * 
 */
char Puzzle::getKeyName()
{
    return keyName;        
}

/*
 * Retorna posição x da chave.
 * 
 * Retorna: int keyPx, posição x da chave.
 * 
 */
int Puzzle::getKeyPX()
{
    return keyPx;
}

/*
 * Retorna posição y da chave.
 * 
 * Retorna: int keyPy, posição y da chave.
 * 
 */
int Puzzle::getKeyPY()
{
    return keyPy;
}

/*
 * Retorna valor da porta.
 * 
 * Retorna: char doorName, valor da porta.
 * 
 */
char Puzzle::getDoorName()
{
    return doorName;
}

/*
 * Retorna posição x da porta.
 * 
 * Retorna: int doorPx, posição x da porta.
 * 
 */
int Puzzle::getDoorPX()
{
    return doorPx;
}

/*
 * Retorna posição y da porta.
 * 
 * Retorna: int doorPy, posição y da porta.
 * 
 */
int Puzzle::getDoorPY()
{
    return doorPy;
}

/*
 * Verifica se o puzzle foi resolvido. Para isso verifica se a posição do jogador é a mesma que a posição da chave,
 * ou seja, se o jogador pegou a chave.
 * 
 * Parâmetros: int px, posição x do jogador; int py, posição y do jogador.
 * 
 * Retorna: bool, true se o puzzle foi resolvido, false caso contrário.
 * 
 */
bool Puzzle::isSolved(int px, int py)
{
    if(px == keyPx && py == keyPy)
        return true;
    else
        return false;
}