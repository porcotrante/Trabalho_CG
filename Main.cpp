#include <iostream>
#include <vector>
#include <cmath>
#include <cfloat> 
#include <SDL2/SDL.h>
#include "./models/headers/ponto.h"
#include "./models/headers/raio.h"
#include "./models/headers/tupla.h"
#include "./models/headers/esfera.h"
#include "./models/headers/objeto.h"
#include "./models/headers/pontoLuminoso.h"
#include "./models/headers/utils.h"
#include "./models/headers/plano.h"
#include "./models/headers/cilindro.h"
#include "./models/headers/cone.h"
#include "./models/headers/triangulo.h"
#include "./models/headers/malha.h"
#include "./models/headers/matriz.h"
using namespace std;

const int NCOL = 500, NLINHA = 500;
const float DIST = 1.0f, WJANELA = 60.0f, HJANELA = 60.0f, DX = WJANELA/NCOL, DY = HJANELA/NLINHA, RAIO = 40.0f, M_ESFERA = 10.0f, M_PLANO = 1.0f, P0Z = 30.0f;
const tupla K_ESFERA(0.7f,0.2f,0.2f), K_ESFERA2(0.2f,0.2f,0.7f), I_FONTE(0.6f, 0.6f, 0.6f), K_D_PLANO1(0.2f, 0.7f, 0.2f), K_D_PLANO2(0.3f, 0.3f, 0.7f), K_E_PLANO(0.0f, 0.0f, 0.0f), I_AMBIENTE(0.1f, 0.1f, 0.1f);
const ponto eye(10.0f, 10.0f, P0Z), at(10.0f, 10.0f, P0Z - DIST), up(10.0f, 11.0f, P0Z - DIST); //cordenadas que definem a câmera

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cerr << "Erro ao inicializar SDL: " << SDL_GetError() << endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Ray Tracing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, NCOL, NLINHA, 0);
    if (!window) {
        cerr << "Erro ao criar janela: " << SDL_GetError() << endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        cerr << "Erro ao criar renderer: " << SDL_GetError() << endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    matriz M = matriz::worldToCamera(eye, at, up);

    pontoLuminoso fonte(10.0f, 10.0f, P0Z, I_FONTE);

    vector<triangulo*> faces = {
        new triangulo(ponto(5.0f, 5.0f, 25.0f), ponto(10.0f, 5.0f, 25.0f), ponto(5.0f, 10.0f, 25.0f), K_ESFERA, K_ESFERA, K_ESFERA, M_ESFERA),
        new triangulo(ponto(10.0f, 10.0f, 25.0f), ponto(10.0f, 5.0f, 25.0f), ponto(5.0f, 10.0f, 25.0f), K_ESFERA, K_ESFERA, K_ESFERA, M_ESFERA),
    };
    
    vector<objeto*> objetos = {
        new malha(faces),
        new plano(ponto(0.0f, 5.0f, 0.0f), tupla(0.0f,1.0f,0.0f), K_D_PLANO1, K_E_PLANO, K_D_PLANO1, M_PLANO),
        new plano(ponto(0.0f, 0.0f, 0.0f), tupla(0.0f,0.0f,1.0f), K_D_PLANO2, K_E_PLANO, K_D_PLANO2, M_PLANO)
    };

    vector<float> distancias(objetos.size());

    bool rodando = true;
    while (rodando) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
                rodando = false;
            }
        }

        for (int y = 0; y < NCOL; y++) {
            float Py = HJANELA / 2.0f - y * DY - DY / 2.0f;
            for (int x = 0; x < NLINHA; x++) {
                float Px = -WJANELA / 2.0f + x * DX + DX / 2.0f;

                tupla pScreen(Px, Py, P0Z - DIST); //cordenadas de mundo
                tupla rayTupla = M.multTupla(pScreen); //projetando das cordenadas de mundo para cordendas de câmera
                ponto rayPonto(rayTupla.element1, rayTupla.element2, rayTupla.element3);

                raio ray(eye, tupla::sub(rayPonto, eye, true));

                int index = -1;
                float menorDistancia = FLT_MAX;
                for (size_t i = 0; i < objetos.size(); i++) {
                    float d = objetos[i]->colisao(ray);
                    if (d != -1000 && d < menorDistancia) {
                        menorDistancia = d;
                        index = static_cast<int>(i);
                    }
                }

                if (index == -1) {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                } else {
                    objeto* obj = objetos[index];
                    tupla aux = ray.getDist().multiplyByScalar(menorDistancia, false);
                    ponto Pi(eye.getCoord().at(0) + aux.element1, eye.getCoord().at(1) + aux.element2, eye.getCoord().at(2) + aux.element3);

                    tupla normal;
                    if (auto* co = dynamic_cast<cone*>(obj)) {
                        tupla dirCone = tupla::sub(co->getVertice(), co->getCentroBase(), true);
                        if (co->colisaoBase) {
                            normal = dirCone.multiplyByScalar(-1, false);
                        } else {
                            matriz M = matriz::identidade().subMatriz(matriz::multComTransposta(dirCone));
                            normal = M.multTupla(tupla::sub(Pi, co->getCentroBase(), false));
                            normal.normalize();
                        }
                        co->colisaoBase = false;
                    }
                    else if (auto ci = dynamic_cast<cilindro*>(obj)) {
                        tupla dirCilindro = tupla::sub(ci->getcentroTopo(), ci->getcentroBase(), true);
                        if (ci->colisaoBase)
                        {
                            normal = dirCilindro.multiplyByScalar(-1, false);
                        } else if (ci->colisaoTopo)
                        {
                            normal = dirCilindro;
                        } else{
                            matriz M = matriz::identidade().subMatriz(matriz::multComTransposta(dirCilindro));
                            normal = M.multTupla(tupla::sub(Pi, ci->getcentroBase(), false));
                            normal.normalize();
                        }
                        ci->colisaoBase = false;
                        ci->colisaoTopo = false;
                    }else if (auto* p = dynamic_cast<plano*>(obj)) {
                        normal = p->getNormal();
                    }else if (auto* m = dynamic_cast<malha*>(obj))
                    {
                        triangulo* t = m->getFaceIntersec();
                        normal = t->getNormal();
                        obj = t;
                    }else if (auto* e = dynamic_cast<esfera*>(obj)) {
                        normal = tupla::sub(Pi, e->getCentro(), true);
                    }

                    tupla cor = utils::calcularCores(menorDistancia, ray, normal, fonte, I_AMBIENTE, obj);
                    cor = utils::calcularSombra(Pi, fonte, obj->getKa(), I_AMBIENTE, cor, objetos);
                    SDL_SetRenderDrawColor(renderer, cor.element1, cor.element2, cor.element3, 255);
                }

                SDL_RenderDrawPoint(renderer, x, y);
            }
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    for (objeto* obj : objetos) delete obj;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}

