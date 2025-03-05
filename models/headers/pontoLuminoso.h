#ifndef PONTOLUMINOSO_H
#define PONTOLUMINOSO_H

#include "./ponto.h"
#include "./tupla.h"

class pontoLuminoso : public ponto
{
private:
    tupla intensidade;
public:
    pontoLuminoso(float x, float y, float z, tupla intensidade);
    ~pontoLuminoso();
    tupla getIntensidade();
};

#endif