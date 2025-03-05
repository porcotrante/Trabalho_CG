#ifndef PONTO_H
#define PONTO_H

#include <array>

class ponto
{
public:
    float x;
    float y;
    float z;
    float aux;
    ponto(float x, float y, float z);

    std::array<float, 3> getCoord() const;

    ~ponto();
};

#endif