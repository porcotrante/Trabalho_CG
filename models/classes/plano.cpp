#include "../headers/plano.h"
#include <iostream>

plano::plano(ponto Pi, tupla Normal, tupla Kd, tupla Ke, tupla Ka, float M) : Pi(Pi), Normal(Normal),  objeto(Kd, Ke, Ka, M) {
}

ponto plano::getPi(){
    return this-> Pi;
}

tupla plano::getNormal(){
    return this->Normal;
}

float plano::colisao(raio raio) {
    tupla n = this->Normal;
    tupla dif = tupla::sub(raio.getP0(), this->Pi, false);

    float aux1 = dif.dot(n);
    float aux2 = raio.getDist().dot(n);

    if (std::abs(aux2) < 1e-6) {
        return -1000;  
    }

    float t = -(aux1 / aux2);

    if (t < 1) {
        return -1000;
    }

    return t;
}

plano::~plano(){}