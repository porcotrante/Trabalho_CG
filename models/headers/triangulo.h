#ifndef TRIANGULO_H
#define TRIANGULO_H

#include "ponto.h"
#include "objeto.h"
#include "raio.h"

class triangulo : public objeto
{
private:
    ponto v1;
    ponto v2;
    ponto v3;
    tupla normal;
    tupla calcNormal();
public:
    triangulo(ponto v1, ponto v2, ponto v3, tupla Kd, tupla Ke, tupla Ka, float M);
    ~triangulo();
    ponto getV1();
    ponto getV2();
    ponto getV3();
    tupla getNormal();
    float colisao(raio ray) override;
};

#endif