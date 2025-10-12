#ifndef CONFIG_H
#define CONFIG_H

#include <allegro5/allegro.h>

#define LEVEL_INICIAL 1
#define MAX_INIMIGOS 6
#define MAX_TIROS 100
#define MAX_COOLDOWN 0.5
#define TEMPO_INVENCIBILIDADE 0.5f
#define VELOCIDADE_INIMIGO 3.0
#define VELOCIDADE_MAX_INIMIGO 3.7
#define VELOCIDADE_ATAQUE 15
#define VELOCIDADE_PERSONAGEM 5
#define VIDA_INICIAL 3
#define MAX_SCORE 10

extern int i;
extern int j;
extern int redraws;
/*
extern float cutscene_alpha;
extern int cutscene_quadrante_atual;
extern int max_quadrantes_cutscene;
*/
extern const int FPS;
extern const int TELA_W;
extern const int TELA_H;
extern const int tamanho_quadrante_cutscene;
extern const int level1Floor;
extern const int level2Floor;
extern const int level2Right;
extern const int level2Left;
extern const int level3Floor;

extern int pontos;

#endif