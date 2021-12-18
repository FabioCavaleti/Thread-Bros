#include "player.hpp"
#include "maps.hpp"
#include <bits/stdc++.h>

Player::Player (bool isMario) {
    isMario = isMario;

    playerIcon = isMario ? 'M' : 'L';
}

void Player::movePlayer(map_t *mapa, std::string direction, int amount){
    std::pair<int,int> pos;

    pos = isMario ? mapa->marioPos : mapa->luigiPos;

    char prevChar;

    if(direction.compare("up") == 0){
        //se a nova posição for válida
        //if(pos.first+amount > 0){ Necessário checar?
            char nextPos = mapa->contents[pos.first+amount][pos.second];                
            switch (nextPos)
            {
                case '@':
                    if(critOcupada(mapa)){
                        printf("Não posso me mover para uma zona crítica!, meu irmão já está em uma!!");
                        break;
                    }

                    prevChar = '@';

                    mapa->contents[pos.first+amount][pos.second] = playerIcon;
                    mapa->contents[pos.first][pos.second] = prevChar;

                    if(isMario){ 
                        mapa->marioPos = std::make_pair(pos.first+amount, pos.second);
                    } else {
                        mapa->luigiPos = std::make_pair(pos.first+amount, pos.second);
                    }

                    break;
                case ' ':
                    prevChar = ' ';

                    mapa->contents[pos.first+amount][pos.second] = playerIcon;
                    mapa->contents[pos.first][pos.second] = prevChar;

                    if(isMario){ 
                        mapa->marioPos = std::make_pair(pos.first+amount, pos.second);
                    } else {
                        mapa->luigiPos = std::make_pair(pos.first+amount, pos.second);
                    }

                    break;
                default:
                    printf("Não posso me mover pra lá!\n");
                    break;
            }
        //}


    }else if (direction.compare("down") == 0)
    {

        if(pos.first-amount > 0){ 
            char nextPos = mapa->contents[pos.first-amount][pos.second];                
            switch (nextPos)
            {
                case '@':
                    if(critOcupada(mapa)){
                        printf("Não posso me mover para uma zona crítica!, meu irmão já está em uma!!");
                        break;
                    }

                    prevChar = '@';

                    mapa->contents[pos.first-amount][pos.second] = playerIcon;
                    mapa->contents[pos.first][pos.second] = prevChar;

                    if(isMario){ 
                        mapa->marioPos = std::make_pair(pos.first-amount, pos.second);
                    } else {
                        mapa->luigiPos = std::make_pair(pos.first-amount, pos.second);
                    }

                    break;
                case ' ':
                    prevChar = ' ';

                    mapa->contents[pos.first-amount][pos.second] = playerIcon;
                    mapa->contents[pos.first][pos.second] = prevChar;

                    if(isMario){ 
                        mapa->marioPos = std::make_pair(pos.first-amount, pos.second);
                    } else {
                        mapa->luigiPos = std::make_pair(pos.first-amount, pos.second);
                    }

                    break;
                default:
                    printf("Não posso me mover pra lá!\n");
                    break;
            }
        }

    }else if (direction.compare("left") == 0)
    {

        if(pos.second-amount > 0){
            char nextPos = mapa->contents[pos.first][pos.second-amount];                
            switch (nextPos)
            {
                case '@':
                    if(critOcupada(mapa)){
                        printf("Não posso me mover para uma zona crítica!, meu irmão já está em uma!!");
                        break;
                    }

                    prevChar = '@';

                    mapa->contents[pos.first][pos.second-amount] = playerIcon;
                    mapa->contents[pos.first][pos.second] = prevChar;

                    if(isMario){ 
                        mapa->marioPos = std::make_pair(pos.first, pos.second-amount);
                    } else {
                        mapa->luigiPos = std::make_pair(pos.first, pos.second-amount);
                    }

                    break;
                case ' ':
                    prevChar = ' ';

                    mapa->contents[pos.first][pos.second-amount] = playerIcon;
                    mapa->contents[pos.first][pos.second] = prevChar;

                    if(isMario){ 
                        mapa->marioPos = std::make_pair(pos.first, pos.second-amount);
                    } else {
                        mapa->luigiPos = std::make_pair(pos.first, pos.second-amount);
                    }
                    break;
                default:
                    printf("Não posso me mover pra lá!\n");
                    break;
            }
        }

    }else if (direction.compare("right") == 0)
    {

        //if(pos.second+amount > 0){ Necessário checar?
            char nextPos = mapa->contents[pos.first][pos.second+amount];                
            switch (nextPos)
            {
                case '@':
                    if(critOcupada(mapa)){
                        printf("Não posso me mover para uma zona crítica!, meu irmão já está em uma!!");
                        break;
                    }

                    prevChar = '@';

                    mapa->contents[pos.first][pos.second+amount] = playerIcon;
                    mapa->contents[pos.first][pos.second] = prevChar;

                    if(isMario){ 
                        mapa->marioPos = std::make_pair(pos.first, pos.second+amount);
                    } else {
                        mapa->luigiPos = std::make_pair(pos.first, pos.second+amount);
                    }

                    break;
                case ' ':
                    prevChar = ' ';

                    mapa->contents[pos.first][pos.second+amount] = playerIcon;
                    mapa->contents[pos.first][pos.second] = prevChar;

                    if(isMario){ 
                        mapa->marioPos = std::make_pair(pos.first, pos.second+amount);
                    } else {
                        mapa->luigiPos = std::make_pair(pos.first, pos.second+amount);
                    }
                    break;
                default:
                    printf("Não posso me mover pra lá!\n");
                    break;
            }
        //}


    }
      
}
