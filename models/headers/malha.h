#ifndef MALHA_H
#define MALHA_H

#include "objeto.h"
#include "triangulo.h"
#include <vector>

using namespace std;
class malha : public objeto
{
private:
    vector<triangulo*> faces;
    tupla normal;
    int intersecI; //índice da face que interceptou o raio
public:
    malha(vector<triangulo*> faces);
    ~malha();
    tupla getNormal();
    triangulo* getFaceIntersec();
    float colisao(raio ray) override;
};

#endif