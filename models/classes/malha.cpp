#include "../headers/malha.h"
#include <cfloat>

malha::malha(vector<triangulo*> faces) : faces(faces) {
    // Calcula a normal média das faces da malha
    normal = tupla(0, 0, 0);
}

malha::~malha() {
}

tupla malha::getNormal() {
    return normal;
}

triangulo* malha::getFaceIntersec(){
    return faces[intersecI];
}

float malha::colisao(raio ray) {
    float menorDistancia = FLT_MAX;
    intersecI = -1;
    
    for (size_t i = 0; i < faces.size(); i++) {
        float distancia = faces[i]->colisao(ray);
        if (distancia > 0 && distancia < menorDistancia) {
            menorDistancia = distancia;
            intersecI = static_cast<int>(i);
        }
    }
    
    return (intersecI != -1) ? menorDistancia : -1000.0f;
}