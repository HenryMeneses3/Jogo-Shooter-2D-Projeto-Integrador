#ifndef RECURSOS_H
#define RECURSOS_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#define VELOCIDADE_ATAQUE 15
#define VELOCIDADE_PERSONAGEM 5
#define MAX_TIROS 3
#define MAX_COOLDOWN 0.2
#define LEVEL_INICIAL 1

extern int i;
extern int j;
extern const int FPS;
extern const int TELA_W;
extern const int TELA_H;

enum 
{
    CENA_MENU = 1,
    CENA_LEVEL_1,
    CENA_LEVEL_2,
    CENA_LEVEL_3,
    CENA_GAMEOVER
};

extern int cena_atual;

extern const int level1Chao;

extern ALLEGRO_DISPLAY* display;
extern ALLEGRO_EVENT_QUEUE* fila_de_evento;
extern ALLEGRO_TIMER* timer;


extern ALLEGRO_BITMAP* level_1_imagem;

extern ALLEGRO_BITMAP* ataque_imagem;

extern ALLEGRO_BITMAP* personagem_imagem;

#endif