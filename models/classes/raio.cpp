#include "../headers/raio.h"
#include <cmath>
#include <fstream>
#include <iostream>
raio::raio(ponto P0, tupla dist) : P0(P0), dist(dist){
    this->P0 = P0;
    this->dist = dist;
};

ponto raio::getP0(){
    return this->P0;
}

tupla raio::getDist(){
    return this->dist;
}

raio::~raio() {
    
};