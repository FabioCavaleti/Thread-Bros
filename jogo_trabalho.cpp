#include <bits/stdc++.h>
#include "maps.hpp"


int main()
{
    map_t *mapaEscolhido = readMap("mapabasico.txt");
    printMap(mapaEscolhido);
    free(mapaEscolhido);
    return 0;
}