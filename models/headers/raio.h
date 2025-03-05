#ifndef RAIO_H
#define RAIO_H

#include "ponto.h"
#include "tupla.h"
#include <array>

class raio
{
private:
    ponto P0;
    tupla dist;

public:
    raio(ponto P0, tupla dist);
    ponto getP0();
    tupla getDist();
    ~raio();
};

#endif