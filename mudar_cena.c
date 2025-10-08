#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "config.h"
#include "recursos.h"
#include "cenas.h"
#include "objetos.h"
#include "input.h"

void mudar_de_cena(int proxima_cena)
{

    if (cena_atual == CENA_LEVEL_1)
    {
        al_stop_sample(&level_1_bgm_id);

    }
    else if (cena_atual == CENA_GAMEOVER)
    {
        al_stop_sample(&game_over_bgm_id);
    }

    cena_atual = proxima_cena;
    inicializar_cena(cena_atual);

    if (cena_atual == CENA_LEVEL_1)
    {
        if (!al_play_sample(level_1_bgm, 0.2, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &level_1_bgm_id))
        {
            perror("falha ao tocar audio: level_1_bgm");
        }
    }

    else if (cena_atual == CENA_GAMEOVER)
    {
        if (!al_play_sample(game_over_bgm, 0.3, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &game_over_bgm_id))
        {
            perror("falha ao tocar audio: game_over_bgm");
        }
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


    if (cena_atual == CENA_LEVEL_1)
    {
        personagem.escondido = false; // mostra personagem na tela
        personagem.vida = VIDA_INICIAL; // define a vida
        personagem.x = TELA_W / 2 - personagem.w / 2; // inicia no centro da tela no eixo x
        personagem.y = (level1Floor + (TELA_H - level1Floor) / 2) - personagem.h / 2; // inicia no centro y do chao do level1
        personagem.direcao = 0;// inicia olhando pra baixo
        personagem.frame = 0;  // inicia no frame 0

        for (i = 0; i < MAX_INIMIGOS; i++)
        {
            resetar_inimigo(&inimigos[i]); //spawna inimigos
        }
    }
}

void destruir_cena(int cena)
{
    if (cena == CENA_LEVEL_1)
    {
        printf("Destruindo level 1\n");
        al_destroy_bitmap(level_1_imagem);
        al_destroy_sample(level_1_bgm);
        al_destroy_font(fonte_gameOver);
    }

    else if (cena == CENA_LEVEL_2)
    {

    }

    else if (cena == CENA_GAMEOVER)
    {
        printf("Destruindo game over\n");
        al_destroy_bitmap(game_over_imagem);
        al_destroy_sample(game_over_bgm);
        al_destroy_font(fonte_gameOver);
    }
}
