#include <stdlib.h>
#include <stdio.h>
#include "config.h"
#include "recursos.h"
#include "cenas.h"
#include "objetos.h"
#include "input.h"

int i, j;

const int FPS = 60;
const int TELA_W = 1280;
const int TELA_H = 720;
const int level1Floor = 320;
int cena_atual;

int pontos = 0;

ObjetoMovel personagem;
ObjetoMovel inimigos[MAX_INIMIGOS];
ObjetoMovel ataque[MAX_TIROS];
double ultimo_tiro = 0;

bool estado_tecla[ALLEGRO_KEY_MAX];
bool* estado_mouse;
int mouse_x, mouse_y;

ALLEGRO_DISPLAY* display;
ALLEGRO_EVENT_QUEUE* fila_de_evento;
ALLEGRO_TIMER* timer;

ALLEGRO_FONT* fonte_inimigo;
ALLEGRO_FONT* fonte_score;
ALLEGRO_FONT* fonte_gameOver;

ALLEGRO_BITMAP* botao_1;
ALLEGRO_BITMAP* tela_inicial_imagem;
ALLEGRO_BITMAP* level_1_imagem;
ALLEGRO_BITMAP* level_2_imagem;
ALLEGRO_BITMAP* level_3_imagem;
ALLEGRO_BITMAP* game_over_imagem;
ALLEGRO_BITMAP* game_over_botao;

ALLEGRO_SAMPLE* level_1_bgm;
ALLEGRO_SAMPLE_ID level_1_bgm_id;
ALLEGRO_SAMPLE* game_over_bgm;
ALLEGRO_SAMPLE_ID game_over_bgm_id;

ALLEGRO_SAMPLE* botao_som;
ALLEGRO_SAMPLE_ID botao_som_id;

ALLEGRO_BITMAP* inimigo_1_imagem;
ALLEGRO_BITMAP* inimigo_2_imagem;
ALLEGRO_BITMAP* inimigo_3_imagem;

ALLEGRO_BITMAP* personagem_imagem;
ALLEGRO_BITMAP* vida_imagem;
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

    if (!al_install_audio())
    {
        fprintf(stderr, "Erro ao inicializar áudio!\n");
        exit(-1);
    }

    if (!al_init_acodec_addon())
    {
        fprintf(stderr, "Erro ao inicializar audio codec!\n");
        exit(-1);
    }

    if (!al_reserve_samples(16))
    {
        fprintf(stderr, "Erro ao reservar samples!\n");
        exit(-1);
    }

    al_init_primitives_addon();
    al_install_keyboard();
    al_install_mouse();
    al_init_font_addon();
    al_init_ttf_addon();

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

    const unsigned int botoes_mouse = al_get_mouse_num_buttons();
    estado_mouse = malloc((botoes_mouse + 1) * sizeof(bool));

    memset(estado_mouse, false, (botoes_mouse + 1) * sizeof(bool));

    // registrar eventos do display, timer, mouse e teclado para fila de eventos.
    al_register_event_source(fila_de_evento, al_get_display_event_source(display));
    al_register_event_source(fila_de_evento, al_get_timer_event_source(timer));
    al_register_event_source(fila_de_evento, al_get_keyboard_event_source());
    al_register_event_source(fila_de_evento, al_get_mouse_event_source());

    al_start_timer(timer);
}

void inicializar_jogo()
{
    printf("Iniciando jogo! =D\n");

    fonte_inimigo = al_load_ttf_font("./assets/Fonte_inimigo.ttf", 26, 0);
    if (!fonte_inimigo)
    {
        fprintf(stderr, "Erro ao carregar fonte inimigo!\n");
        exit(-1);
    }

    botao_1 = al_load_bitmap("./assets/botao.png");
    if (!botao_1)
    {
        fprintf(stderr, "Erro ao carregar imagem do botao!\n");
        exit(-1);
    }

    botao_som = al_load_sample("./assets/Sound_effect/botao.ogg");
    if (!botao_som)
    {
        fprintf(stderr, "Erro ao carregar audio: botao.ogg\n");
        exit(-1);
    }

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

    vida_imagem = al_load_bitmap("./assets/vida.png");
    if (!vida_imagem)
    {
        fprintf(stderr, "Erro ao carregar imagem da vida!\n");
        exit(-1);
    }

    fonte_score = al_load_ttf_font("./assets/PixelOperatorMonoHB8.ttf", 50, 0);
    if (!fonte_score)
    {
        fprintf(stderr, "Erro ao carregar fonte score!\n");
        exit(-1);
    }

    mudar_de_cena(CENA_LEVEL_1);
}

void inicializar_cena(int cena) 
{
    if(cena == CENA_MENU)
    {
    }

    else if(cena == CENA_LEVEL_1)
    {
        level_1_bgm = al_load_sample("./assets/Background_music/level_1_background.ogg");
        if (!level_1_bgm)
        {
            fprintf(stderr, "Erro ao carregar audio: level_1_background.ogg\n");
            exit(-1);
        }

        level_1_imagem = al_load_bitmap("./assets/level1background.png"); // chao de y = 375 ate 720
        if (!level_1_imagem)
        {
            fprintf(stderr, "Erro ao carregar imagem do primeiro mapa!\n");
            exit(-1);
        }

        fonte_gameOver = al_load_ttf_font("./assets/fonteGameOver.ttf", 30, 0);
        if (!fonte_gameOver)
        {
            fprintf(stderr, "Erro ao carregar fonte gameover!\n");
            exit(-1);
        }
    }

    else if(cena == CENA_GAMEOVER)
    {
        game_over_imagem = al_load_bitmap("./assets/GameOver.png");
        if (!game_over_imagem)
        {
            fprintf(stderr, "Erro ao carregar imagem de game over!\n");
            exit(-1);
        }

        game_over_bgm = al_load_sample("./assets/Background_music/gameover.ogg");
        if (!game_over_bgm)
        {
            fprintf(stderr, "Erro ao carregar audio: gameover.ogg\n");
            exit(-1);
        }

        fonte_gameOver = al_load_ttf_font("./assets/fonteGameOver.ttf", 30, 0);
        if (!fonte_gameOver)
        {
            fprintf(stderr, "Erro ao carregar fonte gameover!\n");
            exit(-1);
        }

    }
}

void destruir_jogo()
{
    al_uninstall_audio();
    al_uninstall_keyboard();
    al_uninstall_mouse();
    al_destroy_font(fonte_score);
    al_destroy_font(fonte_gameOver);
    al_destroy_timer(timer);
    al_destroy_event_queue(fila_de_evento);
    al_destroy_display(display);
    free(estado_mouse);
}