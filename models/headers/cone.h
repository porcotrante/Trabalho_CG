#ifndef CONE_H
#define CONE_H

#include "./ponto.h"
#include "objeto.h"

class cone : public objeto {
private:
    ponto centroBase;
    ponto vertice;
    float radius;
public:
    bool colisaoBase;
    cone(ponto centroBase, ponto vertice, float radius, tupla Kd, tupla Ke, tupla Ka, float M);
    ~cone();
    ponto getCentroBase();
    ponto getVertice();
    float getRadius();
    float colisao(raio ray) override;
};

#endif