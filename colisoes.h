#ifndef COLISOES_H
#define COLISOES_H
#include "objetos.h"
#include "stdbool.h"

extern void checar_colisao_personagem(ObjetoMovel* personagem);
extern void checar_colisao_personagem_inimigo(ObjetoMovel* personagem, ObjetoMovel* inimigo);
extern void mouse_apertado(int botao, int x, int y);
bool mouse_em_retangulo(int mX, int mY, int retX, int retY, int retW, int retH);
bool mouse_em_circulo(int mX, int mY, int circX, int circY, int raio);
bool hitbox_em_um_retangulo(int posXp, int posYp, int pW, int pH, int posXret, int posYret, int retH, int retW);
void resetar_personagem_nivel_3(ObjetoMovel* personagem);
void checar_colisao_personagem_pressure_plate(ObjetoMovel* personagem);


#endif