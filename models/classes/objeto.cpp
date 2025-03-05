#include "../headers/objeto.h"

tupla objeto::getKd(){
    return this->Kd;
}

tupla objeto::getKe(){
    return this->Ke;
}

tupla objeto::getKa(){
    return this->Ka;
}

float objeto::getM(){
    return this->M;
}

objeto::objeto(){}

objeto::objeto(tupla Kd, tupla Ke, tupla Ka, float M) : Kd(Kd), Ke(Ke), Ka(Ka) {
    this->Kd = Kd;
    this->Ke = Ke;
    this->Ka = Ka;
    this->M = M;
}