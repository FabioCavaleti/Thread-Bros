#ifndef _H_MAPSGAME
#define _H_MAPSGAME
#include <bits/stdc++.h>

typedef struct gamemap{
    // x = numero de linhas | y = tamanho das linhas
    int xDim,yDim;


    //tupla que define (x,y) da posição de cada irmão no mapa
    std::pair<int,int> marioPos; // como convenção vou adotar mario como 'M'...
    std::pair<int,int> luigiPos; // ... e Luigi como 'L'

    // vetor de zonas criticas '@' que podem conter apenas 1 dos irmãos!
    std::vector<std::pair<int,int>> criticalZones;
    //vetor de de linhas do mapa!
    std::vector<std::string> contents;
}map_t;


map_t *readMap(std::string mapName);
void printMap(map_t *mapa);
bool critOcupada(map_t* mapa);

#endif