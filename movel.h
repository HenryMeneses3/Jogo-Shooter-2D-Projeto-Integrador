#ifndef MOVEL_H
#define MOVEL_H

#include <allegro5/allegro.h>
#include "recursos.h"

enum {
    BAIXO = 0,
    CIMA,
    ESQUERDA,
    DIREITA
};

typedef struct
{
    float x, y;  // posição
    float w, h;  // largura/altura
    float vx, vy; // velocidade
    bool escondido; //aparece na tela ou não
    bool sprite_sheet;// vai usar sprite sheet (bitmapregion)
    ALLEGRO_BITMAP* imagem; // imagem
    int frame, max_frames; // contagem de frames
    int direcao;// direcao
    int anim_contador, anim_max; // flag pra mudar frame
} ObjetoMovel;

extern ObjetoMovel personagem;
extern ObjetoMovel ataque[MAX_TIROS];
extern double ultimo_ataque;

#endif