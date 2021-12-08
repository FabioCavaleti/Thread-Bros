#include "maps.hpp"
#include <bits/stdc++.h>

struct gamemap{
    // x = numero de linhas | y = tamanho das linhas
    int xDim,yDim;


    //tupla que define (x,y) da posição de cada irmão no mapa
    std::pair<int,int> marioPos; // como convenção vou adotar mario como M...
    std::pair<int,int> luigiPos; // ... e Luigi como L

    // vetor de zonas criticas que podem conter apenas 1 dos irmãos!
    std::vector<int> criticalZones;
    //vetor de de linhas do mapa!
    std::vector<std::string> contents;
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

            //identificando a posição dos irmão na linha!
            std::size_t posYM = linha.find('M');
            std::size_t posYL = linha.find('L');
            if(posYL != std::string::npos) newMap->luigiPos = std::make_pair(newMap->xDim-1,(int)posYL);
            if(posYM != std::string::npos) newMap->marioPos = std::make_pair(newMap->xDim-1,(int)posYM);

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
    printf("Mario pos: ( %d, %d )\tLuigi pos: ( %d, %d )\n",mapa->marioPos.first,mapa->marioPos.second,mapa->luigiPos.first,mapa->luigiPos.second);
}