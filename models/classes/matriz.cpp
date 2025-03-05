#include "../headers/matriz.h"
#include "../headers/ponto.h"

matriz::matriz(tupla linha1, tupla linha2, tupla linha3) : linha1(linha1), linha2(linha2), linha3(linha3){
    this->linha4 = tupla();
}

matriz::matriz(tupla linha1, tupla linha2, tupla linha3, tupla linha4) : linha1(linha1), linha2(linha2), linha3(linha3), linha4(linha4){}

matriz::~matriz(){

}

std::vector<tupla> matriz::getLinhas(){
    std::vector<tupla> linhas = {linha1, linha2, linha3, linha4};

    return linhas;
}

matriz matriz::identidade(){

    tupla linha1(1,0,0,0);
    tupla linha2(0,1,0,0);
    tupla linha3(0,0,1,0);

    return matriz(linha1, linha2, linha3);
}

matriz matriz::multComTransposta(tupla Tupla){
    return matriz(
        tupla(Tupla.element1 * Tupla.element1, Tupla.element1 * Tupla.element2, Tupla.element1 * Tupla.element3, Tupla.element1 * Tupla.element4),
        tupla(Tupla.element2 * Tupla.element1, Tupla.element2 * Tupla.element2, Tupla.element2 * Tupla.element3, Tupla.element2 * Tupla.element4),
        tupla(Tupla.element3 * Tupla.element1, Tupla.element3 * Tupla.element2, Tupla.element3 * Tupla.element3, Tupla.element3 * Tupla.element4),
        tupla(Tupla.element4 * Tupla.element1, Tupla.element4 * Tupla.element2, Tupla.element4 * Tupla.element3, Tupla.element4 * Tupla.element4)
    );
}

matriz matriz::multMatriz(matriz Matriz){
    std::vector<tupla> colunas = Matriz.getLinhas();
    
    tupla coluna1(colunas[0].element1, colunas[1].element1, colunas[2].element1, colunas[3].element1);
    tupla coluna2(colunas[0].element2, colunas[1].element2, colunas[2].element2, colunas[3].element2);
    tupla coluna3(colunas[0].element3, colunas[1].element3, colunas[2].element3, colunas[3].element3);
    tupla coluna4(colunas[0].element4, colunas[1].element4, colunas[2].element4, colunas[3].element4);

    return matriz(
        tupla(linha1.dot(coluna1), linha1.dot(coluna2), linha1.dot(coluna3), linha1.dot(coluna4)),
        tupla(linha2.dot(coluna1), linha2.dot(coluna2), linha2.dot(coluna3), linha2.dot(coluna4)),
        tupla(linha3.dot(coluna1), linha3.dot(coluna2), linha3.dot(coluna3), linha3.dot(coluna4)),
        tupla(linha4.dot(coluna1), linha4.dot(coluna2), linha4.dot(coluna3), linha4.dot(coluna4))
    );
}

matriz matriz::addMatriz(matriz Matriz) {
    std::vector<tupla> linhasOutraMatriz = Matriz.getLinhas();
    return matriz(
        tupla(linha1.element1 + linhasOutraMatriz[0].element1, linha1.element2 + linhasOutraMatriz[0].element2, linha1.element3 + linhasOutraMatriz[0].element3, linha1.element4 + linhasOutraMatriz[0].element4),
        tupla(linha2.element1 + linhasOutraMatriz[1].element1, linha2.element2 + linhasOutraMatriz[1].element2, linha2.element3 + linhasOutraMatriz[1].element3, linha2.element4 + linhasOutraMatriz[1].element4),
        tupla(linha3.element1 + linhasOutraMatriz[2].element1, linha3.element2 + linhasOutraMatriz[2].element2, linha3.element3 + linhasOutraMatriz[2].element3, linha3.element4 + linhasOutraMatriz[2].element4),
        tupla(linha4.element1 + linhasOutraMatriz[3].element1, linha4.element2 + linhasOutraMatriz[3].element2, linha4.element3 + linhasOutraMatriz[3].element3, linha4.element4 + linhasOutraMatriz[3].element4)
    );
}

matriz matriz::subMatriz(matriz Matriz) {
    std::vector<tupla> linhasOutraMatriz = Matriz.getLinhas();
    return matriz(
        tupla(linha1.element1 - linhasOutraMatriz[0].element1, linha1.element2 - linhasOutraMatriz[0].element2, linha1.element3 - linhasOutraMatriz[0].element3, linha1.element4 - linhasOutraMatriz[0].element4),
        tupla(linha2.element1 - linhasOutraMatriz[1].element1, linha2.element2 - linhasOutraMatriz[1].element2, linha2.element3 - linhasOutraMatriz[1].element3, linha2.element4 - linhasOutraMatriz[1].element4),
        tupla(linha3.element1 - linhasOutraMatriz[2].element1, linha3.element2 - linhasOutraMatriz[2].element2, linha3.element3 - linhasOutraMatriz[2].element3, linha3.element4 - linhasOutraMatriz[2].element4),
        tupla(linha4.element1 - linhasOutraMatriz[3].element1, linha4.element2 - linhasOutraMatriz[3].element2, linha4.element3 - linhasOutraMatriz[3].element3, linha4.element4 - linhasOutraMatriz[3].element4)
    );
}

matriz matriz::worldToCamera(ponto eye, ponto at, ponto up){
    tupla camera3 = tupla::sub(eye, at, true);
    tupla vup = tupla::sub(up, eye, false);
    tupla camera1 = vup.cross(camera3, true);
    tupla camera2 = camera3.cross(camera1, false);

    float aux1 = -camera1.dot(tupla::sub(eye, ponto(0,0,0), false));
    float aux2 = -camera2.dot(tupla::sub(eye, ponto(0,0,0), false));
    float aux3 = -camera3.dot(tupla::sub(eye, ponto(0,0,0), false));

    camera1.element4 = aux1;
    camera2.element4 = aux2;
    camera3.element4 = aux3;

    return matriz(camera1, camera2, camera3);
}

matriz matriz::cameraToWorld(ponto eye, ponto at, ponto up){
    tupla camera3 = tupla::sub(eye, at, true);
    tupla vup = tupla::sub(up, eye, false);
    tupla camera1 = vup.cross(camera3, true);
    tupla camera2 = camera3.cross(camera1, false);

    array<float, 3> cordEye = eye.getCoord();

    return matriz(
        tupla(camera1.element1, camera2.element1, camera3.element1, cordEye.at(0)),
        tupla(camera1.element2, camera2.element2, camera3.element2, cordEye.at(1)),
        tupla(camera1.element3, camera2.element3, camera3.element3, cordEye.at(2))
    );
}

tupla matriz::multTupla(tupla vetorColuna) {
    return tupla(
        linha1.dot(vetorColuna),
        linha2.dot(vetorColuna),
        linha3.dot(vetorColuna),
        linha4.dot(vetorColuna)
    );
}