
#ifndef RECURSOS_H
#define RECURSOS_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

extern ALLEGRO_DISPLAY* display;
extern ALLEGRO_EVENT_QUEUE* fila_de_evento;
extern ALLEGRO_TIMER* timer;
extern ALLEGRO_TIMER* cutscene_timer;

// fontes
extern ALLEGRO_FONT* fonte_inimigo;
extern ALLEGRO_FONT* fonte_score;
extern ALLEGRO_FONT* fonte_gameOver;
extern ALLEGRO_FONT* fonte_instrucoes;
extern ALLEGRO_FONT* fonte_titulo;

// imagens
extern ALLEGRO_BITMAP* botao_1;
extern ALLEGRO_BITMAP* botao_2;
extern ALLEGRO_BITMAP* botao_tecla_wasd;
extern ALLEGRO_BITMAP* botao_tecla_space;
extern ALLEGRO_BITMAP* tela_inicial_imagem;
extern ALLEGRO_BITMAP* cutscene_1_imagem;
extern ALLEGRO_BITMAP* level_1_imagem;
extern ALLEGRO_BITMAP* level_2_imagem;
extern ALLEGRO_BITMAP* level_3_imagem;
extern ALLEGRO_BITMAP* game_over_imagem;
extern ALLEGRO_BITMAP* game_over_botao;
extern ALLEGRO_BITMAP* inimigo_1_imagem;
extern ALLEGRO_BITMAP* inimigo_2_imagem;
extern ALLEGRO_BITMAP* inimigo_3_imagem;
extern ALLEGRO_BITMAP* personagem_imagem;
extern ALLEGRO_BITMAP* vida_imagem;
extern ALLEGRO_BITMAP* ataque_imagem;

// sons
extern ALLEGRO_SAMPLE* level_1_bgm;
extern ALLEGRO_SAMPLE_ID level_1_bgm_id;
extern ALLEGRO_SAMPLE* game_over_bgm;
extern ALLEGRO_SAMPLE_ID game_over_bgm_id;
extern ALLEGRO_SAMPLE* botao_som;
extern ALLEGRO_SAMPLE_ID botao_som_id;

#endif