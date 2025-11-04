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
    else if(cena_atual == CENA_CONCLUSAO)
    {
		al_stop_sample(&conclusao_bgm_id);
    }

    cena_atual_temp = cena_atual;
    cena_atual = proxima_cena;
    inicializar_cena(cena_atual);
  

    if (cena_atual == CENA_GAMEOVER)
    {
        if (!al_play_sample(game_over_bgm, 0.3, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &game_over_bgm_id))
        {
            perror("falha ao tocar audio: game_over_bgm");
        }
    }
    else if (cena_atual == CENA_CONCLUSAO)
    {
        if (!al_play_sample(conclusao_bgm, 0.2, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &conclusao_bgm_id))
        {
            perror("falha ao tocar audio: conclusao_bgm");
        }
	}

    if(cena_atual == CENA_CUTSCENE1)
    {
        cutscene_quadrante_atual = -1;
		al_start_timer(cutscene_timer);
        for (int i = 0; i < NUM_MAX_QUADRANTES; i++) 
        {
            alpha_quadrante[i] = 0;
        }
	}

    else if (cena_atual == CENA_LEVEL_1)
    {
        if (!al_play_sample(level_1_bgm, 0.2, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &level_1_bgm_id))
        {
            perror("falha ao tocar audio: level_1_bgm");
        }

        pontos = 0;
        personagem.vida = VIDA_INICIAL;
        personagem.escondido = false; // mostra personagem na tela
        personagem.x = TELA_W / 2 - personagem.w / 2; // inicia no centro da tela no eixo x
        personagem.y = (level1Floor + (TELA_H - level1Floor) / 2) - personagem.h / 2; // inicia no centro y do chao do level1
        personagem.direcao = BAIXO;// inicia olhando pra baixo
        personagem.frame = 0;  // inicia no frame 0

        for (i = 0; i < MAX_EXPRESSOES; i++)
        {
            resetar_inimigo(&inimigos[i]); //spawna inimigos
        }
    }

    else if (cena_atual == CENA_CUTSCENE2)
    {
        cutscene_quadrante_atual = -1;
        al_start_timer(cutscene_timer);
        for (int i = 0; i < NUM_MAX_QUADRANTES; i++)
        {
            alpha_quadrante[i] = 0;
        }
    }

    else if (cena_atual == CENA_LEVEL_2)
    {
		pontos = 0;
        personagem.vida = VIDA_INICIAL;
        personagem.escondido = false;
        personagem.x = TELA_W / 2 - personagem.w / 2;
        personagem.y = level2Floor / 2;
        personagem.direcao = CIMA;
        personagem.frame = 0;
        embaralhar_fileiras();
		resetar_inimigo(&fileiras[fileira_ativa]);
        
    }

    else if (cena_atual == CENA_LEVEL_3)
    {
        pontos = 0;
        personagem.vida = VIDA_INICIAL;
        personagem.escondido = false;
        personagem.x = TELA_W / 2 - personagem.w / 2;
        personagem.y = TELA_H / 2 - personagem.h / 2;
        personagem.direcao = DIREITA;
		personagem.frame = 0;
    }

    else if(cena_atual == CENA_CONCLUSAO)
    {
		personagem.vida = personagem.vida; // mantém a vida do personagem
    }
}



void passar_nivel()
{
    double agora = al_get_time();
    static double cooldown_botao = 0;
    if (estado_tecla[ALLEGRO_KEY_P] && agora - cooldown_botao >= 1 && cena_atual != CENA_GAMEOVER)
    {
        cooldown_botao = agora;
        mudar_de_cena(cena_atual + 1);
        destruir_cena(cena_atual - 1);
    }
}
