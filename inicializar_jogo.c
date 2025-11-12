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

int cena_atual;
int cena_atual_temp;

const int tamanho_quadrante_cutscene = 253;
int cutscene_quadrante_atual;
float alpha_quadrante[NUM_MAX_QUADRANTES];

const int level1Floor = 320;

const int level2Floor = 570;
const int level2Right = 1190;
const int level2Left = 80;

const int level3Floor = 275;

int pontos = 0;

int fileira_ativa = -1;
int pergunta_ativa = 0;
int tamanho_fileira_certa = 110;


ObjetoMovel personagem;
ObjetoMovel inimigos[MAX_EXPRESSOES];
ObjetoMovel ataque[MAX_TIROS];
ObjetoMovel fileiras[MAX_FILEIRAS];

double ultimo_tiro = 0;

bool estado_tecla[ALLEGRO_KEY_MAX];
bool* estado_mouse;
int mouse_x, mouse_y;

ALLEGRO_DISPLAY* display;
ALLEGRO_EVENT_QUEUE* fila_de_evento;
ALLEGRO_TIMER* timer;
ALLEGRO_TIMER* cutscene_timer;

ALLEGRO_FONT* fonte_inimigo;
ALLEGRO_FONT* fonte_score;
ALLEGRO_FONT* fonte_gameOver;
ALLEGRO_FONT* fonte_instrucoes;
ALLEGRO_FONT* fonte_titulo;

ALLEGRO_BITMAP* botao_conclusao;
ALLEGRO_BITMAP* botao_1;
ALLEGRO_BITMAP* botao_2;
ALLEGRO_BITMAP* botao_tecla_wasd;   
ALLEGRO_BITMAP* botao_tecla_space;
ALLEGRO_BITMAP* tela_inicial_imagem;
ALLEGRO_BITMAP* cutscene_1_imagem;
ALLEGRO_BITMAP* level_1_imagem;
ALLEGRO_BITMAP* cutscene_2_imagem;
ALLEGRO_BITMAP* level_2_imagem;
ALLEGRO_BITMAP* cutscene_3_imagem;
ALLEGRO_BITMAP* level_3_imagem;
ALLEGRO_BITMAP* cutscene_4_imagem;
ALLEGRO_BITMAP* game_over_imagem;
ALLEGRO_BITMAP* game_over_botao;
ALLEGRO_BITMAP* explicacao_imagem_1;
ALLEGRO_BITMAP* explicacao_imagem_2;
ALLEGRO_BITMAP* explicacao_imagem_3;
ALLEGRO_BITMAP* final_imagem;

ALLEGRO_SAMPLE* level_1_bgm;
ALLEGRO_SAMPLE_ID level_1_bgm_id;
ALLEGRO_SAMPLE* conclusao_bgm;
ALLEGRO_SAMPLE_ID conclusao_bgm_id;
ALLEGRO_SAMPLE* game_over_bgm;
ALLEGRO_SAMPLE_ID game_over_bgm_id;

ALLEGRO_SAMPLE* botao_som;
ALLEGRO_SAMPLE_ID botao_som_id;
ALLEGRO_SAMPLE* som_cutscene;
ALLEGRO_SAMPLE_ID som_cutscene_id;


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

    if(!al_init_primitives_addon())
    {
        fprintf(stderr, "Erro ao inicializar Primitives Addon!\n");
        exit(-1);
	}
    
    if(!al_install_keyboard())
    {
        fprintf(stderr, "Erro ao inicializar teclado!\n");
        exit(-1);
	}
    
    if (!al_install_mouse())
    {
        fprintf(stderr, "Erro ao inicializar mouse!\n");
        exit(-1);
    }

    if (!al_init_font_addon())
    {
        fprintf(stderr, "Erro ao inicializar Font Addon!\n");
        exit(-1);
    }
    
    if (!al_init_ttf_addon())
    {
        fprintf(stderr, "Erro ao inicializar TTF Addon!\n");
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

    al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA);

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
    if(estado_mouse != NULL)
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
    printf("Iniciando jogo! =D\n\n");

    botao_1 = al_load_bitmap("./assets/botao.png");
    if (!botao_1)
    {
        fprintf(stderr, "Erro ao carregar imagem do botao!\n");
        exit(-1);
    }
    
	botao_2 = al_load_bitmap("./assets/botao_2.png");
    if(!botao_2)
    {
        fprintf(stderr, "Erro ao carregar imagem do botao 2!\n");
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


    // Personagem
    personagem.img = personagem_imagem;
    personagem.w = al_get_bitmap_width(personagem.img) / 4;  // largura do sprite
    personagem.h = al_get_bitmap_height(personagem.img) / 4; // altura do sprite
    personagem.vx = VELOCIDADE_PERSONAGEM;                   // velocidade eixo x do personagem
    personagem.vy = VELOCIDADE_PERSONAGEM;                   // velocidade eixo y do personagem
    personagem.max_frames = 4;                               // sprite sheet de 4 frames pro loop
    personagem.anim_contador = 0;                            // contador que vai receber as velocidades x e y
    personagem.anim_max = 50;                                // indexador para usar velocidade vx e vy como base na velocidade da mudança do sprite
    personagem.sprite_sheet = true;

    // Ataque
    for (i = 0; i < MAX_TIROS; i++)
    {
        ataque[i].img = ataque_imagem;
        ataque[i].w = al_get_bitmap_width(ataque_imagem);
        ataque[i].h = al_get_bitmap_height(ataque_imagem);
        ataque[i].vx = VELOCIDADE_ATAQUE;
        ataque[i].vy = VELOCIDADE_ATAQUE;
        ataque[i].escondido = true;
        ataque[i].sprite_sheet = false;
    }

    mudar_de_cena(CENA_MENU);
}

void inicializar_cena(int cena) 
{
    if(cena == CENA_MENU)
    {
		printf("Iniciando menu\n\n");

        tela_inicial_imagem = al_load_bitmap("./assets/telaInicial.png");
        if (!tela_inicial_imagem)
        {
            fprintf(stderr, "Erro ao carregar imagem da tela inicial!\n");
            exit(-1);
        }

        fonte_gameOver = al_load_ttf_font("./assets/fonteGameOver.ttf", 30, 0);
        if (!fonte_gameOver)
        {
            fprintf(stderr, "Erro ao carregar fonte gameover!\n");
            exit(-1);
        }

		fonte_titulo = al_load_ttf_font("./assets/fonteTitulo.ttf", 80, 0);
        if (!fonte_titulo)
        {
            fprintf(stderr, "Erro ao carregar fonte do titulo!\n");
            exit(-1);
        }
    }
    
    else if(cena == CENA_COMO_JOGAR)
    {
		printf("Iniciando como jogar\n\n");

        fonte_instrucoes = al_load_ttf_font("./assets/fonteGameOver.ttf", 30, 0);
        if (!fonte_instrucoes)
        {
            fprintf(stderr, "Erro ao carregar fonte das instrucoes!\n");
            exit(-1);
        }

		botao_tecla_wasd = al_load_bitmap("./assets/tecla_wasd.png");
        if (!botao_tecla_wasd)
        {
            fprintf(stderr, "Erro ao carregar imagem do botao tecla wasd!\n");
            exit(-1);
        }

		botao_tecla_space = al_load_bitmap("./assets/tecla_espaco.png");
        if(!botao_tecla_space)
        {
            fprintf(stderr, "Erro ao carregar imagem do botao tecla space!\n");
            exit(-1);
		}

    }

    else if(cena == CENA_CUTSCENE1)
    {
        printf("Iniciando cutscene 1\n\n");

		som_cutscene = al_load_sample("./assets/Sound_effect/somcutscene.wav");
        if (!som_cutscene)
        {
            fprintf(stderr, "Erro ao carregar audio: somcutscene.wav\n");
            exit(-1);
        }

        cutscene_1_imagem = al_load_bitmap("./assets/cutscene1.png");
        if (!cutscene_1_imagem)
        {
            fprintf(stderr, "Erro ao carregar imagem da cutscene 1!\n");
            exit(-1);
        }

		cutscene_timer = al_create_timer(2.0 / 1.0); // timer de 1.5 segundos para cada quadrante da cutscene
        if (!cutscene_timer)
        {
            fprintf(stderr, "Erro ao criar timer da cutscene!\n");
            exit(-1);
        }

        al_register_event_source(fila_de_evento, al_get_timer_event_source(cutscene_timer));

	}

    else if (cena == CENA_EXPLICACAO_1)
    {
     
		explicacao_imagem_1 = al_load_bitmap("./assets/explicacao1.png");
        if (!explicacao_imagem_1)
        {
            fprintf(stderr, "Erro ao carregar imagem da explicacao 1!\n");
            exit(-1);
        }

    }

    else if(cena == CENA_LEVEL_1)
    {
        printf("Iniciando level 1\n\n");

        level_1_bgm = al_load_sample("./assets/Background_music/level_1_background.ogg");
        if (!level_1_bgm)
        {
            fprintf(stderr, "Erro ao carregar audio: level_1_background.ogg\n");
            exit(-1);
        }

        level_1_imagem = al_load_bitmap("./assets/backgroundlevel1.png"); // chao de y = 375 ate 720
        if (!level_1_imagem)
        {
            fprintf(stderr, "Erro ao carregar imagem do primeiro mapa!\n");
            exit(-1);
        }

        fonte_gameOver = al_load_ttf_font("./assets/fonteGameOver.ttf", 25, 0);
        if (!fonte_gameOver)
        {
            fprintf(stderr, "Erro ao carregar fonte gameover!\n");
            exit(-1);
        }

		fonte_instrucoes = al_load_ttf_font("./assets/fonteInstrucoes.ttf", 20, 0);
        if(!fonte_instrucoes)
        {
            fprintf(stderr, "Erro ao carregar fonte das instrucoes!\n");
            exit(-1);
		}

        fonte_inimigo = al_load_ttf_font("./assets/fonteInimigo.ttf", 36, 0);
        if (!fonte_inimigo)
        {
            fprintf(stderr, "Erro ao carregar fonte inimigo!\n");
            exit(-1);
        }


    }
    
    else if (cena == CENA_CUTSCENE2)
    {
        printf("Iniciando cutscene 2\n\n");

        cutscene_2_imagem = al_load_bitmap("./assets/cutscene2.png");
        if (!cutscene_2_imagem)
        {
            fprintf(stderr, "Erro ao carregar imagem da cutscene 2!\n");
            exit(-1);
        }

        som_cutscene = al_load_sample("./assets/Sound_effect/somcutscene.wav");
        if (!som_cutscene)
        {
            fprintf(stderr, "Erro ao carregar audio: somcutscene.wav\n");
            exit(-1);
        }

        cutscene_timer = al_create_timer(2.0 / 1.0); // timer de 1.5 segundos para cada quadrante da cutscene
        if (!cutscene_timer)
        {
            fprintf(stderr, "Erro ao criar timer da cutscene!\n");
            exit(-1);
        }

        al_register_event_source(fila_de_evento, al_get_timer_event_source(cutscene_timer));
    }

    else if (cena == CENA_EXPLICACAO_2)
    {
        explicacao_imagem_2 = al_load_bitmap("./assets/explicacao2.png");
        if (!explicacao_imagem_2)
        {
            fprintf(stderr, "Erro ao carregar imagem da explicacao 2!\n");
            exit(-1);
		}
    }
    
    else if(cena == CENA_LEVEL_2)
    {
        printf("Iniciando level 2\n\n");

        level_2_imagem = al_load_bitmap("./assets/level2background.png");
        if (!level_2_imagem)
        {
            fprintf(stderr, "Erro ao carregar fonte gameover!\n");
            exit(-1);
        }

        fileiras[0].img = al_load_bitmap("./assets/Animais/fileira1.png");
        if (!fileiras[0].img)
        {
            fprintf(stderr, "Erro ao carregar imagem da fileira 1!\n");
            exit(-1);
        }

        fileiras[1].img = al_load_bitmap("./assets/Animais/fileira2.png");
        if (!fileiras[1].img)
        {
            fprintf(stderr, "Erro ao carregar imagem da fileira 2!\n");
            exit(-1);
        }

        fileiras[2].img = al_load_bitmap("./assets/Animais/fileira3.png");
        if (!fileiras[2].img)
        {
            fprintf(stderr, "Erro ao carregar imagem da fileira 3!\n");
            exit(-1);
        }

        fileiras[3].img = al_load_bitmap("./assets/Animais/fileira4.png");
        if (!fileiras[3].img)
        {
            fprintf(stderr, "Erro ao carregar imagem da fileira 4!\n");
            exit(-1);
        }

        fileiras[4].img = al_load_bitmap("./assets/Animais/fileira5.png");
        if (!fileiras[4].img)
        {
            fprintf(stderr, "Erro ao carregar imagem da fileira 5!\n");
            exit(-1);
        }

        fileiras[5].img = al_load_bitmap("./assets/Animais/fileira6.png");
        if (!fileiras[5].img)
        {
            fprintf(stderr, "Erro ao carregar imagem da fileira 6!\n");
            exit(-1);
        }

		fileiras[6].img = al_load_bitmap("./assets/Animais/fileira7.png");
        if (!fileiras[6].img)
        {
            fprintf(stderr, "Erro ao carregar imagem da fileira 7!\n");
            exit(-1);
        }

		fileiras[7].img = al_load_bitmap("./assets/Animais/fileira8.png");
        if (!fileiras[7].img)
        {
            fprintf(stderr, "Erro ao carregar imagem da fileira 8!\n");
            exit(-1);
		}

        fonte_instrucoes = al_load_ttf_font("./assets/fonteGameOver.ttf", 20, 0);
        if (!fonte_instrucoes)
        {
            fprintf(stderr, "Erro ao carregar fonte das instrucoes!\n");
            exit(-1);
        }

    }

    else if(cena == CENA_CUTSCENE3)
    {
        printf("Iniciando cutscene 3\n\n");

        cutscene_3_imagem = al_load_bitmap("./assets/cutscene3.png");
        if (!cutscene_3_imagem)
        {
            fprintf(stderr, "Erro ao carregar imagem da cutscene 3!\n");
            exit(-1);
        }

        som_cutscene = al_load_sample("./assets/Sound_effect/somcutscene.wav");
        if (!som_cutscene)
        {
            fprintf(stderr, "Erro ao carregar audio: somcutscene.wav\n");
            exit(-1);
        }

        cutscene_timer = al_create_timer(2.0 / 1.0); // timer de 1.5 segundos para cada quadrante da cutscene
        if (!cutscene_timer)
        {
            fprintf(stderr, "Erro ao criar timer da cutscene!\n");
            exit(-1);
        }

        al_register_event_source(fila_de_evento, al_get_timer_event_source(cutscene_timer));
    }

    else if (cena == CENA_EXPLICACAO_3)
    {
        explicacao_imagem_3 = al_load_bitmap("./assets/explicacao3.png");
        if (!explicacao_imagem_3)
        {
            fprintf(stderr, "Erro ao carregar imagem da explicacao 3!\n");
            exit(-1);
        }
    }

    else if(cena == CENA_LEVEL_3)
    {
        printf("Iniciando level 3\n\n");
        level_3_imagem = al_load_bitmap("./assets/level3background.png");
        if (!level_3_imagem)
        {
            fprintf(stderr, "Erro ao carregar imagem do terceiro mapa!\n");
            exit(-1);
        }
		fonte_instrucoes = al_load_ttf_font("./assets/fonteGameOver.ttf", 45, 0);
        if (!fonte_instrucoes)
        {
            fprintf(stderr, "Erro ao carregar fonte das instrucoes!\n");
            exit(-1);
		}
        fonte_score = al_load_ttf_font("./assets/fonteGameOver.ttf", 35, 0);
        if (!fonte_score)
        {
            fprintf(stderr, "Erro ao carregar fonte das instrucoes 2!\n");
            exit(-1);
        }
		fonte_gameOver = al_load_ttf_font("./assets/fonteGameOver.ttf", 25, 0);
        if (!fonte_gameOver)
        {
            fprintf(stderr, "Erro ao carregar fonte das alternativas!\n");
            exit(-1);
        }
	}

    else if (cena == CENA_CUTSCENE4)
    {
        printf("Iniciando cutscene 4\n\n");
        cutscene_4_imagem = al_load_bitmap("./assets/cutscene4.png");
        if (!cutscene_4_imagem)
        {
            fprintf(stderr, "Erro ao carregar imagem da cutscene 4!\n");
            exit(-1);
        }
        som_cutscene = al_load_sample("./assets/Sound_effect/somcutscene.wav");
        if (!som_cutscene)
        {
            fprintf(stderr, "Erro ao carregar audio: somcutscene.wav\n");
            exit(-1);
        }
        cutscene_timer = al_create_timer(2.0 / 1.0); // timer de 1.5 segundos para cada quadrante da cutscene
        if (!cutscene_timer)
        {
            fprintf(stderr, "Erro ao criar timer da cutscene!\n");
            exit(-1);
        }

        al_register_event_source(fila_de_evento, al_get_timer_event_source(cutscene_timer));
	}

    else if(cena_atual == CENA_FIM_JOGO)
    {
        final_imagem = al_load_bitmap("./assets/telaFinal.png");
        if (!final_imagem)
        {
            fprintf(stderr, "Erro ao carregar imagem do final!\n");
            exit(-1);
		}
        fonte_gameOver = al_load_ttf_font("./assets/fonteGameOver.ttf", 30, 0);
        if (!fonte_gameOver)
        {
            fprintf(stderr, "Erro ao carregar fonte gameover!\n");
            exit(-1);
        }
        fonte_titulo = al_load_ttf_font("./assets/fonteTitulo.ttf", 80, 0);
        if (!fonte_titulo)
        {
            fprintf(stderr, "Erro ao carregar fonte do titulo!\n");
            exit(-1);
        }
    }
    
    else if(cena_atual == CENA_CONCLUSAO)
    {
		botao_conclusao = al_load_bitmap("./assets/conclusao.png");
        if (!botao_conclusao)
        {
            fprintf(stderr, "Erro ao carregar imagem da conclusao!\n");
            exit(-1);
        }

        fonte_gameOver = al_load_ttf_font("./assets/fonteGameOver.ttf", 40, 0);
        if (!fonte_gameOver)
        {
            fprintf(stderr, "Erro ao carregar fonte gameover!\n");
            exit(-1);
        }

		fonte_instrucoes = al_load_ttf_font("./assets/fonteGameOver.ttf", 18, 0);
        if (!fonte_instrucoes)
        {
            fprintf(stderr, "Erro ao carregar fonte gameover!\n");
            exit(-1);
        }

		conclusao_bgm = al_load_sample("./assets/Background_music/conclusao.ogg");
        if (!conclusao_bgm)
        {
            fprintf(stderr, "Erro ao carregar audio: conclusao.ogg\n");
            exit(-1);
		}

    }

    else if(cena == CENA_GAMEOVER)
    {
        printf("Iniciando tela de game over\n\n");

        fonte_gameOver = al_load_ttf_font("./assets/fonteGameOver.ttf", 30, 0);
        if (!fonte_gameOver)
        {
            fprintf(stderr, "Erro ao carregar fonte gameover!\n");
            exit(-1);
        }
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

    }
}

void destruir_cena(int cena)
{
    if (cena == CENA_MENU)
    {
        printf("Destruindo menu\n\n");
        al_destroy_bitmap(tela_inicial_imagem);
        al_destroy_font(fonte_gameOver);
        al_destroy_font(fonte_titulo);
    }

    else if(cena == CENA_COMO_JOGAR)
    {
        printf("Destruindo como jogar\n\n");
        al_destroy_font(fonte_instrucoes);
		al_destroy_bitmap(botao_tecla_wasd);
		al_destroy_bitmap(botao_tecla_space);
    }

    else if (cena == CENA_CUTSCENE1)
    {
        printf("Destruindo cutscene 1\n\n");

        al_destroy_sample(som_cutscene);
        al_destroy_bitmap(cutscene_1_imagem);
        if (cutscene_timer)
        {
            al_unregister_event_source(fila_de_evento, al_get_timer_event_source(cutscene_timer));
            al_destroy_timer(cutscene_timer);
            cutscene_timer = NULL;
        }
    }

    else if (cena == CENA_EXPLICACAO_1)
    {
        printf("Destruindo tutorial\n\n");
        al_destroy_bitmap(explicacao_imagem_1);
	}

    else if (cena == CENA_LEVEL_1)
    {
        printf("Destruindo level 1\n\n");
        al_destroy_bitmap(level_1_imagem);
        al_destroy_sample(level_1_bgm);
        al_destroy_font(fonte_gameOver);
        al_destroy_font(fonte_inimigo);
        al_destroy_font(fonte_instrucoes);
    }
    
    else if (cena == CENA_CUTSCENE2)
    {
        printf("Destruindo cutscene 2\n\n");
		
        al_destroy_bitmap(cutscene_2_imagem);
        al_destroy_sample(som_cutscene);
        if (cutscene_timer)
        {
            al_unregister_event_source(fila_de_evento, al_get_timer_event_source(cutscene_timer));
            al_destroy_timer(cutscene_timer);
            cutscene_timer = NULL;
        }
    }

    else if (cena == CENA_EXPLICACAO_2)
    {
        printf("Destruindo tutorial\n\n");
        al_destroy_bitmap(explicacao_imagem_2);
    }

    else if (cena == CENA_LEVEL_2)
    {
        printf("Destruindo level 2\n\n");
        al_destroy_bitmap(level_2_imagem);
        for(i = 0; i < MAX_FILEIRAS; i++)
        {
            al_destroy_bitmap(fileiras[i].img);
		}
		al_destroy_font(fonte_instrucoes);
    }

    else if(cena == CENA_CUTSCENE3)
    {
        printf("Destruindo cutscene 3\n\n");

        al_destroy_sample(som_cutscene);
        al_destroy_bitmap(cutscene_3_imagem);
        if (cutscene_timer)
        {
            al_unregister_event_source(fila_de_evento, al_get_timer_event_source(cutscene_timer));
            al_destroy_timer(cutscene_timer);
            cutscene_timer = NULL;
        }
    }

    else if (cena == CENA_EXPLICACAO_3)
    {
        printf("Destruindo tutorial\n\n");
        al_destroy_bitmap(explicacao_imagem_3);
    }

    else if (cena == CENA_LEVEL_3)
    {
        printf("Destruindo level 3\n\n");
        al_destroy_bitmap(level_3_imagem);
      
    }

    else if (cena== CENA_CUTSCENE4)
    {
        printf("Destruindo cutscene 4\n\n");
        al_destroy_sample(som_cutscene);
        al_destroy_bitmap(cutscene_4_imagem);
        if (cutscene_timer)
        {
            al_unregister_event_source(fila_de_evento, al_get_timer_event_source(cutscene_timer));
            al_destroy_timer(cutscene_timer);
            cutscene_timer = NULL;
        }
	}

    else if (cena == CENA_CONCLUSAO)
    {
        printf("Destruindo conclusao\n\n");
        al_destroy_bitmap(botao_conclusao);
        al_destroy_font(fonte_gameOver);
		al_destroy_font(fonte_instrucoes);
		al_destroy_sample(conclusao_bgm);
	}

    else if (cena == CENA_GAMEOVER)
    {
        printf("Destruindo game over\n\n");
        al_destroy_bitmap(game_over_imagem);
        al_destroy_sample(game_over_bgm);
        al_destroy_font(fonte_gameOver);
    }
}

void destruir_jogo()
{
    // Globais criadas em inicializar_jogo
    al_destroy_bitmap(botao_1);
    al_destroy_bitmap(botao_2);
    al_destroy_bitmap(personagem_imagem);
    al_destroy_bitmap(ataque_imagem);
    al_destroy_bitmap(vida_imagem);
    al_destroy_sample(botao_som);
    al_destroy_font(fonte_score);

    al_uninstall_audio();
    al_uninstall_keyboard();
    al_uninstall_mouse();
    al_destroy_timer(timer);
    al_destroy_event_queue(fila_de_evento);
    al_destroy_display(display);
    free(estado_mouse);
}