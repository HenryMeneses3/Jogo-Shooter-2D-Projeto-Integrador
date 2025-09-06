#include <stdlib.h>
#include <stdio.h>
#include "recursos.h"

int i, j;

const int FPS = 60;
const int TELA_W = 1280;
const int TELA_H = 720;
const int level1Chao = 320;
int cena_atual;

ALLEGRO_DISPLAY* display;
ALLEGRO_EVENT_QUEUE* fila_de_evento;
ALLEGRO_TIMER* timer;

ALLEGRO_BITMAP* level_1_imagem;

ALLEGRO_BITMAP* personagem_imagem;
ALLEGRO_BITMAP* ataque_imagem;

void inicializar_allegro5(void)
{
    if (!al_init())
    {
        fprintf(stderr, "Erro ao inicializar Allegro!\n");
        exit(-1);
    }

    // Inicializa addons que vamos usar
    if (!al_init_image_addon())
    {
        fprintf(stderr, "Erro ao inicializar Image Addon!\n");
        exit(-1);
    }

    if (!al_init_primitives_addon())
    {
        fprintf(stderr, "Erro ao inicializar Primitives Addon!\n");
        exit(-1);
    }

    if (!al_install_keyboard())
    {
        fprintf(stderr, "Erro ao instalar teclado!\n");
        exit(-1);
    }

    // criar display do jogo
    display = al_create_display(TELA_W, TELA_H);
    if (!display)
    {
        fprintf(stderr, "Erro ao criar display!\n");
        exit(-1);
    }
    al_set_window_title(display, "Conta-Strike");
    al_set_window_position(display, 300, 300);

    // timer de update
    timer = al_create_timer(1.0f / FPS);
    if (!timer)
    {
        fprintf(stderr, "Erro ao criar timer!\n");
        al_destroy_display(display);
        exit(-1);
    }

    // inicializar fila de eventos
    fila_de_evento = al_create_event_queue();
    if (!fila_de_evento)
    {
        fprintf(stderr, "Erro ao criar fila de eventos!\n");
        al_destroy_display(display);
        al_destroy_timer(timer);
        exit(-1);
    }

    // registrar eventos do display, timer, mouse e teclado para fila de eventos.
    al_register_event_source(fila_de_evento, al_get_display_event_source(display));
    al_register_event_source(fila_de_evento, al_get_timer_event_source(timer));
    al_register_event_source(fila_de_evento, al_get_keyboard_event_source());

    //inicializa timer
    al_start_timer(timer);
}

void inicializar_jogo(void)
{
    personagem_imagem = al_load_bitmap("./assets/personagem.png");
    if (!personagem_imagem)
    {
        fprintf(stderr, "Erro ao carregar imagem do personagem!\n");
        exit(-1);
    }

    ataque_imagem = al_load_bitmap("./assets/ataque.png");
    if (!ataque_imagem)
    {
        fprintf(stderr, "Erro ao carregar imagem do ataque!\n");
        exit(-1);
    }

    mudar_de_cena(CENA_LEVEL_1);
}

void inicializar_cena(int cena)
{
    if (cena == CENA_LEVEL_1)
    {
        level_1_imagem = al_load_bitmap("./assets/level1.png");
        if (!level_1_imagem)
        {
            fprintf(stderr, "Erro ao carregar imagem do primeiro mapa!\n");
            exit(-1);
        }
    }
}
