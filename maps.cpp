#include "maps.hpp"
#include <bits/stdc++.h>



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

            //identificando a ocorrência de zonas críticas
            std::size_t critY = linha.find('@');
            while (critY != std::string::npos) 
            {
                newMap->criticalZones.push_back(std::make_pair(newMap->xDim-1,(int)critY));
                critY = linha.find('@',critY + 1);
            }
            

        }
    }else
    {
        return NULL;
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
    printf("Mario pos: ( %d, %d )\tLuigi pos: ( %d, %d )\n",mapa->marioPos.first,mapa->marioPos.second,
                                                            mapa->luigiPos.first,mapa->luigiPos.second);    
    printf("Critcal Zones: %ld\n",mapa->criticalZones.size());
    for (int i = 0; i < mapa->criticalZones.size(); i++)
    {
        printf("Critical zone %d = ( %d , %d )\n",i,mapa->criticalZones[i].first,mapa->criticalZones[i].second);
    }
    
}

bool critOcupada(map_t* mapa){
    for (int i = 0; i < mapa->criticalZones.size(); i++)
    {
        int coordX = mapa->criticalZones[i].first;
        int coordY = mapa->criticalZones[i].second;
        if(mapa->contents[coordX][coordY]=='L' || mapa->contents[coordX][coordY]=='M') return true;
    }
    return false;
}