#include "player.hpp"
#include "maps.hpp"
#include <bits/stdc++.h>


struct player{
    // se true é o Mario se não só pode ser Luigi
    bool isMario;

    void movePlayer(map_t *mapa,std::string direction,int amount){
        std::pair<int,int> pos;
        if(isMario) pos = mapa->marioPos;
        else pos = mapa->luigiPos;
        if(direction.compare("up") == 0){
            //se a nova posição for válida
            if(pos.first > 0){
                char nextPos = mapa->contents[pos.first-1][pos.second];
                switch (nextPos)
                {
                    case '@':
                        
                        break;
                    case ' ':
                        
                        break;
                    default:
                        
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




};