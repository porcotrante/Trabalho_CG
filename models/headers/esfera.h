#ifndef ESFERA_H
#define ESFERA_H
#include "ponto.h"
#include "tupla.h"
#include "objeto.h"

class esfera : public objeto
{
private:
    ponto centro;
    float radius;
public:
    esfera(ponto centro, float radius, tupla Kd, tupla Ke, tupla Ka, float M);
    ponto getCentro();
    float getRaio();
    float colisao(raio raio) override;
    ~esfera();
};

#endif