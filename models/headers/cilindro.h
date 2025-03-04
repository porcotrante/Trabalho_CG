#ifndef CILINDRO_H
#define CILINDRO_H

#include "./ponto.h"
#include "objeto.h"

class cilindro : public objeto{
private:
    ponto centroBase;
    ponto centroTopo;
    float radius;
public:
    bool colisaoBase;
    bool colisaoTopo;
    cilindro(ponto centroBase, ponto centroTopo, float radius, tupla Kd, tupla Ke, tupla Ka, float M);
    ~cilindro();
    ponto getcentroBase();
    ponto getcentroTopo();
    float getRaio();
    float colisao(raio ray) override;
};


#endif