#ifndef PONTO_H
#define PONTO_H

#include <array>

class ponto
{
private:
    float x;
    float y;
    float z;
    float aux;
public:
    ponto(float x, float y, float z);

    std::array<float, 3> getCoord() const;

    ~ponto();
};

#endif