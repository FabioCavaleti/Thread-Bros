#ifndef _H_MAPSGAME
#define _H_MAPSGAME
#include <bits/stdc++.h>

typedef struct gamemap map_t;
map_t *readMap(std::string mapName);
void printMap(map_t *mapa);

#endif