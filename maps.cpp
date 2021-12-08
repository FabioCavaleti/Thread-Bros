#include "maps.hpp"
#include <bits/stdc++.h>

struct gamemap{
    int xDim,yDim;// x = numero de linhas | y = tamanho das linhas
    std::vector<std::string> contents;//vetor de de linhas do mapa!
};

map_t *readMap(std::string mapName){
    // alocando um novo mapa
    map_t *newMap = new gamemap;
    newMap->contents.clear();
    newMap->xDim = 0;
    newMap->yDim = 0;

    //lendo do arquivo cada linha do mapa
    std::ifstream mapFile;
    mapFile.open(mapName);
    std::string linha;
    if( mapFile.is_open() )
    {
        while ( getline(mapFile,linha) )
        {
            //adicionando a linha ao mapa
            newMap->yDim = linha.size();
            newMap->xDim ++;
            newMap->contents.push_back(linha);
        }
    }

    return newMap;
}

void printMap(map_t *mapa){
    if(mapa->contents.size() == 0) std::cout << "Empty Map!\n";
    else    
    for (auto &&linha : mapa->contents)
    {
        std::cout << linha << std::endl;
    }
}