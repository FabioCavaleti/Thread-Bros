#ifndef _H_PLAYER
#define _H_PLAYER
#include <bits/stdc++.h>
#include "maps.hpp"

class Player {
    bool isMario;
    char playerIcon;
  public:
    Player(bool isMario);
    void movePlayer(map_t *mapa, std::string direction, int amount);
};


#endif