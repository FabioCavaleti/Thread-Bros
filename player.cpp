#include "player.hpp"
#include "maps.hpp"
#include <bits/stdc++.h>

Player::Player (bool isMario) {
    isMario = isMario;
    if(isMario)
        playerIcon = 'M';
    else
        playerIcon = 'L';
}

void Player::movePlayer(map_t *mapa, std::string direction, int amount){
    std::pair<int,int> pos;

    if(isMario){ 
        pos = mapa->marioPos;
    } else {
        pos = mapa->luigiPos;
    }

    char prevChar;

    if(direction.compare("up") == 0){
        //se a nova posição for válida
        if(pos.first-amount > 0){
            char nextPos = mapa->contents[pos.first-amount][pos.second];                
            switch (nextPos)
            {
                case '@':
                    if(critOcupada(mapa)){
                        printf("Não posso me mover para uma zona crítica!, meu irmão já está em uma!!");
                        break;
                    }
                    mapa->contents[pos.first-amount][pos.second] = playerIcon;
                    mapa->contents[pos.first][pos.second] = prevChar;
                    prevChar = '@';
                    break;
                case ' ':
                    mapa->contents[pos.first-amount][pos.second] = playerIcon;
                    mapa->contents[pos.first][pos.second] = prevChar;
                    prevChar = ' ';
                    break;
                default:
                    printf("Não posso me mover pra lá!\n");
                    break;
            }
        }


    }else if (direction.compare("down") == 0)
    {



    }else if (direction.compare("left") == 0)
    {


    }else if (direction.compare("right") == 0)
    {

    }
      
}
