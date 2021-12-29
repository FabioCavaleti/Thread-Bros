/*  
    SSC0140 - Sistemas Operacionais I

    Trabalho Prático - Parte 2

    Antonio Rodrigues Rigolino, 11795791
    Breno Lívio Silva de Almeida, 10276675
    Favio Henrique Alves Cavaleti, 11200550

    ----------------------------------------------------------------

    Este arquivo contém as funções principais do jogo, contando com funções de imprimir a tela, alocação de threads e o loop
    para a execução do jogo.

*/

#include <cstdio>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
#include <unistd.h>
#include <fstream>
#include "maze.hpp"
#include "puzzle.hpp"
#include "player.hpp"

std::vector<char> buffer;
std::mutex mtx;

int move(Maze &maze, std::vector<Puzzle> &puzzles, Player &m, Player &l);
void moveM(Maze &maze, std::vector<Puzzle> &puzzles, Player &m);
void moveL(Maze &maze, std::vector<Puzzle> &puzzles, Player &l);
void attMaze(Maze &maze, std::vector<Puzzle> &puzzles, Player &m, Player &l);
void setObjectsMaze(Maze &maze, std::vector<Puzzle> &puzzles, Player &m, Player &l);
std::pair<int, int> findObject(Maze &maze, char key);
void endGame(int select);
void printScreen(int select);

/*
 * Leitura dos movimentos para os personagens e alocação de threads para os movimentos deles.
 * 
 * Parâmetros: Maze &maze, referência ao objeto do labirinto trabalhado; std::vector<Puzzle> &puzzles, referência ao vetor de puzzles trabalhado;
 *              Player &m, referência ao jogador M; Player &l, referência ao jogador L.
 * 
 * Retorna: inteiro igual a -1, se os irmãos chegaram ao destino; 1 caso o usuário sai do jogo; 0 caso o usuário ainda não tenha chegado ao destino.
 * 
 */
int move(Maze &maze, std::vector<Puzzle> &puzzles, Player &m, Player &l)
{
    // Se os dois personagens chegaram nas suas respectivas posiçõs finais, o labirinto acaba
    if(m.getX() == m.getEndPos().first && m.getY() == m.getEndPos().second && l.getX() == l.getEndPos().first && l.getY() == l.getEndPos().second)
        return -1;

    // Lidar com inputs de char um por vez
    system("stty raw");
    char key;
    scanf("%c", &key);

    // Usuário pressionou espaço, termina jogo
    if(key == ' ')
    {
        system("stty cooked");
        return 1;
    }

    // Coloca no buffer para ser lido como possível movimento para os personagens
    buffer.push_back(key);

    // Voltando à leitura padrão do terminal
    system("stty cooked");

    // Criação de threads para a movimentação de cada personagem
    std::thread Mario(moveM, std::ref(maze), std::ref(puzzles), std::ref(m));
    std::thread Luigi(moveL, std::ref(maze), std::ref(puzzles), std::ref(l));

    Mario.join();
    Luigi.join();

    return 0;
}

/*
 * Função de movimento para o jogador M. Utiliza do semáforo mutex para permitir exclusão mútua. Os irmãos devem compartilhar do mesmo recurso,
 * mas não devem acessar o mesmo recurso ao mesmo tempo para evitar conflitos com a movimentação utilizando o buffer.
 * 
 * Parâmetros: Maze &maze, referência ao objeto do labirinto trabalhado; std::vector<Puzzle> &puzzles, referência ao vetor de puzzles trabalhado;
 *              Player &m, referência ao jogador M.
 * 
 */
void moveM(Maze &maze, std::vector<Puzzle> &puzzles, Player &m)
{
    // Define região crítica para acesso ao buffer
    mtx.lock();

    // Verifica se o buffer está vazio para trabalhar com os direcionais do personagem
    if(buffer.size() > 0)
    {
        if(buffer[0] == 'd')
        {
            m.moveRight(maze, puzzles);
            buffer.erase(buffer.begin());
        }
        else if(buffer[0] == 'a')
        {
            m.moveLeft(maze, puzzles);
            buffer.erase(buffer.begin());
        }
        else if(buffer[0] == 'w')
        {
            m.moveUp(maze, puzzles);
            buffer.erase(buffer.begin());
        }
        else if(buffer[0] == 's' )
        {
            m.moveDown(maze, puzzles);
            buffer.erase(buffer.begin());
        }
    }

    mtx.unlock();

}

/*
 * Função de movimento para o jogador L. Utiliza do semáforo mutex para permitir exclusão mútua. Os irmãos devem compartilhar do mesmo recurso,
 * mas não devem acessar o mesmo recurso ao mesmo tempo para evitar conflitos com a movimentação utilizando o buffer.
 * 
 * Parâmetros: Maze &maze, referência ao objeto do labirinto trabalhado; std::vector<Puzzle> &puzzles, referência ao vetor de puzzles trabalhado;
 *              Player &l, referência ao jogador L.
 * 
 */
void moveL(Maze &maze, std::vector<Puzzle> &puzzles, Player &l)
{
    // Define região crítica para acesso ao buffer
    mtx.lock();

    // Verifica se o buffer está vazio para trabalhar com os direcionais do personagem
    if(buffer.size() > 0)
    {
        if(buffer[0] == 'l')
        {
            l.moveRight(maze, puzzles);
            buffer.erase(buffer.begin());
        }
        else if(buffer[0] == 'j')
        {
            l.moveLeft(maze, puzzles);
            buffer.erase(buffer.begin());
        }
        else if(buffer[0] == 'i')
        {
            l.moveUp(maze, puzzles);
            buffer.erase(buffer.begin());
        }
        else if(buffer[0] == 'k')
        {
            l.moveDown(maze, puzzles);
            buffer.erase(buffer.begin());
        }
    }
    mtx.unlock();
}


/*
 * Atualiza o labirinto considerando a leitura do mesmo arquivo de texto, mas com informações das posições dos personagens e puzzles.
 * 
 * Parâmetros: Maze &maze, referência ao objeto do labirinto trabalhado; std::vector<Puzzle> &puzzles, referência ao vetor de puzzles trabalhado;
 *              Player &m, referência ao jogador M; Player &l, referência ao jogador L.
 * 
 */
void attMaze(Maze &maze, std::vector<Puzzle> &puzzles, Player &m, Player &l)
{
    // Limpa o terminal
    system("clear");

    // Atualiza tabela do labirinto
    maze.updateTable();

    // Atualiza posição dos personagens
    maze.setTable(m.getX(), m.getY(), 'M');
    maze.setTable(l.getX(), l.getY(), 'L');

    // Atualiza posição dos puzzles
    for(int i = 0; i < (int) puzzles.size(); i++)
    {
        int kpx = puzzles[i].getKeyPX();
        int kpy = puzzles[i].getKeyPY();
        int dpx = puzzles[i].getDoorPX();
        int dpy = puzzles[i].getDoorPY();
        maze.setTable(kpx, kpy, puzzles[i].getKeyName());
        maze.setTable(dpx, dpy, puzzles[i].getDoorName());
    }
}

/*
 * Dado um labirinto lido por arquivo de texto, são definidos os objetos e suas respectivas posições para serem usadas no jogo.
 * 
 * Parâmetros: Maze &maze, referência ao objeto do labirinto trabalhado; std::vector<Puzzle> &puzzles, referência ao vetor de puzzles trabalhado;
 *              Player &m, referência ao jogador M; Player &l, referência ao jogador L.
 * 
 */
void setObjectsMaze(Maze &maze, std::vector<Puzzle> &puzzles, Player &m, Player &l)
{
    maze.createTable();

    auto table = maze.getTable();

    // Pegamos a posição do Mario e Luigi no mapa
    std::pair<int, int> posMario = findObject(maze, 'M');
    std::pair<int, int> posLuigi = findObject(maze, 'L');

    // Salvamos as posições deles
    m.setX(posMario.first);
    m.setY(posMario.second);
    l.setX(posLuigi.first);
    l.setY(posLuigi.second);

    // Saída dos personagens
    m.setEndPos(findObject(maze, '+'));
    l.setEndPos(findObject(maze, '-'));

    // Chaves e portas
    char key = 'a';

    // Incrementa 1, indo de 'a' até 'j'
    for (int i = 0; i < 10; i++)
    {
        std::pair<int, int> keyPos = findObject(maze, key + i);

        if(keyPos.first == -1) // Não tem chave no labirinto, então considera-se que não existem mais chaves
            break;

        char door = key + i - 32; // Letra maiúscula, que representa a porta

        std::pair<int, int> doorPos = findObject(maze, door);

        Puzzle p(key + i, keyPos.first, keyPos.second, door, doorPos.first, doorPos.second);
        puzzles.push_back(p);

    }
}

/*
 * Considerando um labirinto, é procurado por um dado objeto por ele e retornado sua posição.
 * 
 * Parâmetros: Maze &maze, referência ao objeto do labirinto trabalhado; char object, objeto a ser procurado.
 * 
 * Retorna: Par <int, int>, que representa a posição do objeto.
 * 
 */
std::pair<int, int> findObject(Maze &maze, char object)
{
    int x = -1, y = -1;
    
    for(int i = 0; i < maze.getDims().first; i++){
        for(int j = 0; j < maze.getDims().second; j++){
            if(maze.getTable()[i][j] == object)
            {
                x = i;
                y = j;
            }
        }
    }

    return std::make_pair(x, y);
}

/*
 * Finaliza jogo com uma mensagem dependendo do que aconteceu, se o usuário fechou o jogo, ou passou por todos os níveis.
 * 
 * Parâmetros: int select, seleção do que aconteceu.
 * 
 */
void endGame(int select)
{
    if (select == 1){ // Se o usuário saiu do jogo
        system("clear");
        std::cout << "Você encerrou o jogo." << std::endl;
    } else { // Caso contrário, ele ganhou, imprime tela de parabéns
        printScreen(5);
    }
    
}

/*
 * Imprime telas como a tela inicial, instruções e abertura de um nível.
 * 
 * Parâmetros: int select, seleção da tela a ser impressa.
 * 
 */
void printScreen(int select){
    system("clear");

    std::ifstream infile;

    if (select == -2){
        infile = std::ifstream("screens/main.txt");
    } else if (select == -1) {
        infile = std::ifstream("screens/instructions.txt");
    } else if (select == 0) {
        infile = std::ifstream("screens/instructions2.txt");
    } else if (select == 1) {
        infile = std::ifstream("screens/level1.txt");
    } else if (select == 2) {
        infile = std::ifstream("screens/level2.txt");
    } else if (select == 3) {
        infile = std::ifstream("screens/level3.txt");
    } else if (select == 4) {
        infile = std::ifstream("screens/level4.txt");
    } else if (select == 5) {
        infile = std::ifstream("screens/congrats.txt");
    }

    // Armazena tela a ser mostrada em vetor de vetor de char
    std::vector<std::vector<char> > screen;

    std::string line;

    while (std::getline(infile, line)) {
        std::vector<char> row;

        for (char &c : line) {
            row.push_back(c);
        }

        screen.push_back(row);
    }

    for (int i = 0; i < (int) screen.size(); i++)
    {
        for (int j = 0; j < (int) screen[i].size(); j++)
        {
            std::cout << screen[i][j];
        }
        std::cout << std::endl;
    }

    infile.close();
}

/*
 * Função principal onde é executado o loop para execução do jogo.
 * 
 * Retorna: 0, caso execução da função foi um sucesso.
 * 
 */
int main()
{
    // Tela inicial e instruções
    printScreen(-2);

    char key;
    scanf("%c", &key);

    printScreen(-1);

    scanf("%c", &key);

    printScreen(0);

    scanf("%c", &key);

    int end = 0;

    // Loop pelos labirintos disponíveis
    for (int i = 1; i <= 4; i++) {
        printScreen(i);
        // Mostra tela por 1,5 segundos
        std::this_thread::sleep_for(std::chrono::milliseconds(1500));

        // Inicializa elementos como o próprio labirinto, puzzles e personagens
        Maze maze(i);
        std::vector<Puzzle> puzzles;
        Player m(0, 0, std::make_pair(0, 0));
        Player l(0, 0, std::make_pair(0, 0));

        // Aloca as posições dos objetos baseado no que arquivo de texto lido do labirinto
        setObjectsMaze(maze, puzzles, m, l);

        // Loop para execução do jogo em um dado labirinto
        while(true)
        {     
            attMaze(maze, puzzles, m, l);
            maze.printTable();
            end = move(maze, puzzles, m, l);
            if (end == -1 || end == 1){ // Ou o usuário saiu do jogo ou passou pelo labirinto
                break;
            } 
        }

        if (end == 1) // Se saiu do jogo, sai do loop externo também
            break;
    }

    // Finaliza jogo de acordo com o que ocorreu
    endGame(end);

    return 0;
}