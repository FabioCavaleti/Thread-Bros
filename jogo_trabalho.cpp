#include <bits/stdc++.h>
#include "maps.hpp"
#include "player.hpp"

int main()
{

    std::string mapname;
    printf("Escolha um mapa!\n");
    std::cin >> mapname;
    mapname.append(".txt");
    map_t *mapaEscolhido = readMap(mapname);

    if(mapaEscolhido == NULL)
    {
        printf("Mapa inexistente!\n");
        return 1;
    }

    printf("\n\t\tMAPA ESCOLHIDO\n");
    printMap(mapaEscolhido);
    std::string move = "";

    Player mario (true);
    Player luigi (false);

    while (move.compare("exit")!=0) {
        printf("para sair digite 'exit'\n");
        printf("Quem vai mover ? (mario ou luigi)\n");
        std::cin >> move;
        std::size_t who = move.find("mario");
        if(who != std::string::npos){//movimento é do Mario
            printf("Para aonde? (up,down,left,right)\n");
            std:: cin >> move;
            mario.movePlayer(mapaEscolhido, move, 1);
        }else
        {
            who = move.find("luigi");
            if(who == std::string::npos){
                continue;
            }                                  
            printf("Para aonde? (up,down,left,right)\n");                                  
            std::cin >> move;
            luigi.movePlayer(mapaEscolhido,move,1);
        }
        printMap(mapaEscolhido);
    }
    
    free(mapaEscolhido);
    printf("FIM DE JOGO\n");

    return 0;
}