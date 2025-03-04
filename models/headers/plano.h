#ifndef PLANO_H
#define PLANO_H
#include "ponto.h"
#include "tupla.h"
#include "objeto.h"
#include "raio.h"

class plano : public objeto
{
private:
    ponto Pi;
    tupla Normal;
public:
    plano(ponto Pi, tupla Normal, tupla Kd, tupla Ke, tupla Ka, float M);
    ponto getPi();
    tupla getNormal();
    float colisao(raio raio) override;
    ~plano();
};

#endif