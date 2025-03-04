#include "../headers/utils.h"
#include <cmath>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cfloat> 
#include "../headers/cilindro.h"
using namespace std;
tupla utils::calcularDiff(ponto Pi, tupla normal, ponto fonte, tupla Kdif, tupla I_PONTUAL){
    tupla luz = tupla::sub(fonte, Pi, true); 

    float luminosidade = fmaxf(0.0f, normal.dot(luz));

    tupla I_dif(Kdif.element1 * I_PONTUAL.element1 * luminosidade, 
    Kdif.element2 * I_PONTUAL.element2 * luminosidade,
    Kdif.element3 * I_PONTUAL.element3 * luminosidade);

    return I_dif;
}

tupla utils::calcularEspec(ponto Pi, ponto P0, tupla normal, ponto fonte, float REFLEXIVIDADE, tupla Kesp, tupla I_PONTUAL){
    tupla luz = tupla::sub(fonte, Pi, true);
    
    tupla reflexo = normal.multiplyByScalar(normal.dot(luz), false);
    reflexo = reflexo.multiplyByScalar(2, false);
    reflexo = tupla::subTupla(reflexo, luz, false);
    
    reflexo.normalize();

    tupla visao = tupla::sub(P0, Pi, true);

    float reflexao = powf(fmax(0.0f, reflexo.dot(visao)), REFLEXIVIDADE);

    tupla I_Espec(Kesp.element1 * I_PONTUAL.element1 * reflexao, 
    Kesp.element2 * I_PONTUAL.element2 * reflexao,
    Kesp.element3 * I_PONTUAL.element3 * reflexao);

    return I_Espec;
}

tupla utils::calcularCores(float T, raio raio, tupla normal, pontoLuminoso luz, tupla I_am, objeto* objeto ){
    ponto P0 = raio.getP0();
    tupla aux = raio.getDist().multiplyByScalar(T, false);

    ponto Pi(P0.getCoord().at(0) + aux.element1, P0.getCoord().at(1) + aux.element2, P0.getCoord().at(2)  + aux.element3);
    ponto pontoLuz(luz.getCoord().at(0), luz.getCoord().at(1), luz.getCoord().at(2));

    tupla I_dif = utils::calcularDiff(Pi, normal, pontoLuz, objeto->getKd(), luz.getIntensidade());
    tupla I_espec = utils::calcularEspec(Pi, P0, normal, pontoLuz, objeto->getM(), objeto->getKe(), luz.getIntensidade());

    tupla Ka(objeto->getKa().element1 * I_am.element1, 
    objeto->getKa().element2 * I_am.element2,
    objeto->getKa().element3 * I_am.element3);

    tupla cores = tupla::addTupla(Ka, I_dif, false);
    cores = tupla::addTupla(cores, I_espec, false);
    cores = cores.multiplyByScalar(255, false);

                    
    utils::clamp(&cores);

    return cores;
}

tupla utils::calcularSombra(ponto Pi, pontoLuminoso fonte, tupla Ka, tupla I_am, tupla cores, std::vector<objeto*>& objetos){
    tupla dist = tupla::sub(fonte, Pi, false);
    float comprimento = sqrt(pow(dist.element1, 2.0f) + pow(dist.element2, 2.0f) + pow(dist.element3, 2.0f));

    raio raio(Pi, tupla::sub(fonte, Pi, true));

    float t = -1000;

    for (int i = 0; i < objetos.size(); i++)
    {
         
        float aux = objetos[i]->colisao(raio);
        
        if ((t == -1000 && aux != -1000) || (t != -1000 && aux != -1000 && aux < t))
        {
            t = aux;
        }      
    }
    
    if (t == -1000 || t > comprimento || t < 1)
    {
        return cores;
    }

    tupla FinalKa(Ka.element1 * I_am.element1, 
    Ka.element2 * I_am.element2,
    Ka.element3 * I_am.element3);

    FinalKa = FinalKa.multiplyByScalar(255, false);
                    
    utils::clamp(&FinalKa);

    return FinalKa;
}

void utils::clamp(tupla* cores){
    if (cores->element1 > 255)
    {
        cores->element1 = 255;
    }

    if (cores->element2 > 255)
    {
        cores->element2 = 255;
    }

    if (cores->element3 > 255)
    {
        cores->element3 = 255;
    }
}