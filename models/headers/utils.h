#ifndef UTILS_H
#define UTILS_H
#include "./tupla.h"
#include "./ponto.h"
#include "./pontoLuminoso.h"
#include "./raio.h"
#include "./objeto.h"
#include <vector>

class utils
{
public:
    static tupla calcularDiff(ponto Pi, tupla normal, ponto fonte, tupla K, tupla I_PONTUAL);

    static tupla calcularEspec(ponto Pi, ponto P0, tupla normal, ponto fonte, float REFLEXIVIDADE, tupla K, tupla I_PONTUAL);

    static tupla calcularCores(float T, raio raio, tupla normal, pontoLuminoso fonte, tupla I_am, objeto* objeto);

    static tupla calcularSombra(ponto Pi, pontoLuminoso fonte, tupla Ka,tupla I_am, tupla cores, std::vector<objeto*>& objetos);

    static void clamp(tupla* cores);
};

#endif