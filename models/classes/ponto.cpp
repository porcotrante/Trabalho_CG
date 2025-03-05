#include "../headers/ponto.h"
#include "../headers/matriz.h"
#include "../headers/tupla.h"
#include <array>

ponto::ponto(float x, float y, float z){
    this->x = x;
    this->y = y;
    this->z = z;
    this->aux = 1;
};

std::array<float, 3> ponto::getCoord() const {
    return {this->x, this->y, this->z};
}

ponto::~ponto() {

}