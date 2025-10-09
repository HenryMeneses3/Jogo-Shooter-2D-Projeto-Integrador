#ifndef CONFIG_H
#define CONFIG_H

#include <allegro5/allegro.h>

#define LEVEL_INICIAL 1
#define MAX_INIMIGOS 4
#define MAX_TIROS 100
#define MAX_COOLDOWN 0.5
#define VELOCIDADE_INIMIGO 2.5
#define VELOCIDADE_MAX_INIMIGO 4.5
#define VELOCIDADE_ATAQUE 15
#define VELOCIDADE_PERSONAGEM 5
#define VIDA_INICIAL 3
#define MAX_SCORE 10

extern int i;
extern int j;
extern const int FPS;
extern const int TELA_W;
extern const int TELA_H;
extern const int level1Floor;
extern const int level2Floor;
extern const int level2Right;
extern const int level2Left;

extern int pontos;

#endif