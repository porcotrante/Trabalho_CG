#ifndef MATRIZ_H
#define MATRIZ_H

#include "./tupla.h"
#include <vector>

using namespace std;
class matriz
{
private:
    tupla linha1;
    tupla linha2;
    tupla linha3;
    tupla linha4;
public:
    matriz(tupla linha1, tupla linha2, tupla linha3);
    matriz(tupla linha1, tupla linha2, tupla linha3, tupla linha4);
    ~matriz();
    vector<tupla> getLinhas();
    static matriz identidade();
    static matriz multComTransposta(tupla tupla);
    static matriz worldToCamera(ponto eye, ponto at, ponto up);
    static matriz cameraToWorld(ponto eye, ponto at, ponto up);
    matriz multMatriz(matriz Matriz);
    matriz addMatriz(matriz Matriz);
    matriz subMatriz(matriz Matriz);
    tupla multTupla(tupla vetorColuna);
};

#endif