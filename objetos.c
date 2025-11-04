#include <allegro5/allegro.h> 
#include <stdio.h>           
#include <stdlib.h>          
#include <string.h>          
#include "config.h"
#include "recursos.h"
#include "cenas.h"
#include "objetos.h"
#include "input.h"
#include "colisoes.h"

bool hitbox_em_um_retangulo(int posXp, int posYp, int pW, int pH, int posXret, int posYret, int retH, int retW);


void resetar_inimigo(ObjetoMovel* inimigo)
{
    if (cena_atual == CENA_LEVEL_1)
    {
        int direcoes_validas[3] = { BAIXO, ESQUERDA, DIREITA };

        // randomiza direcao toda vez
        inimigo->direcao = direcoes_validas[rand() % 3];

        // randomiza as expressoes toda vez
        int index_expressoes = rand() % total_de_expressoes;

        strcpy_s(inimigo->expressao, sizeof(inimigo->expressao), expressoes[index_expressoes].texto);
        inimigo->inimigo = expressoes[index_expressoes].correta;
        inimigo->w = al_get_text_width(fonte_inimigo, inimigo->expressao);
        inimigo->h = al_get_font_line_height(fonte_inimigo);
        inimigo->vx = VELOCIDADE_INIMIGO + rand() % (int)VELOCIDADE_MAX_INIMIGO;
        inimigo->vy = VELOCIDADE_INIMIGO + rand() % (int)VELOCIDADE_MAX_INIMIGO;

        if (inimigo->direcao == DIREITA) // vai VIR da direita
        {
            inimigo->x = TELA_W;
            inimigo->y = level1Floor + (int)inimigo->h + (rand() % (TELA_H - level1Floor - (int)inimigo->h - (int)personagem.h / 2));
        }
        else if (inimigo->direcao == ESQUERDA) // vai VIR da esquerda
        {
            inimigo->x = 0 - inimigo->w;
		    inimigo->y = level1Floor + (int)inimigo->h + (rand() % (TELA_H - level1Floor - (int)inimigo->h - (int)personagem.h / 2)); // 2*ataque pq quero que ele nasca um pouco acima do chao
        }
        else if (inimigo->direcao == BAIXO) // vai VIR de baixo
        {
            inimigo->y = TELA_H;
            inimigo->x = rand() % (TELA_W - (int)inimigo->w);
        }
    }
    else if(cena_atual == CENA_LEVEL_2)
    {
      

		sortear_fileira();
        fileiras[fileira_ativa].x = 90;
        fileiras[fileira_ativa].h = al_get_bitmap_height(fileiras[fileira_ativa].img);
		fileiras[fileira_ativa].w = al_get_bitmap_width(fileiras[fileira_ativa].img);
        fileiras[fileira_ativa].y = 0 - fileiras[fileira_ativa].h;
        fileiras[fileira_ativa].vy = VELOCIDADE_INIMIGO_FILEIRA;
        fileiras[fileira_ativa].escondido = false;
        fileiras[fileira_ativa].inimigo = true;
    }
}

void atualizar_inimigo()
{
    if(cena_atual == CENA_LEVEL_1)
    {
        for (i = 0; i < MAX_EXPRESSOES; i++)
        {
            if (inimigos[i].direcao == DIREITA)
            {
                inimigos[i].x -= inimigos[i].vx;
                if (inimigos[i].x < 0 - inimigos[i].w)
                {
                    resetar_inimigo(&inimigos[i]);
                }
            }
            else if (inimigos[i].direcao == ESQUERDA)
            {

                inimigos[i].x += inimigos[i].vx;
                if (inimigos[i].x > TELA_W + inimigos[i].w)
                {
                    resetar_inimigo(&inimigos[i]);
                }
            }
            else if (inimigos[i].direcao == BAIXO)
            {
                inimigos[i].y -= inimigos[i].vy;
                if (inimigos[i].y < -2 * inimigos[i].h)
                {
                    resetar_inimigo(&inimigos[i]);
                }
            }
		
        }
    }

    else if(cena_atual == CENA_LEVEL_2)
    {
		fileiras[fileira_ativa].y += fileiras[fileira_ativa].vy;
		if (fileiras[fileira_ativa].y > TELA_H + fileiras[fileira_ativa].h)
        {
			resetar_inimigo(&fileiras[fileira_ativa]);
        }
      
    }

}

void atualizar_personagem(void)
{
    bool andando = false;

    if (estado_tecla[ALLEGRO_KEY_W] || estado_tecla[ALLEGRO_KEY_UP])
    {
        personagem.y -= personagem.vy;
        personagem.direcao = CIMA;
        andando = true;
    }

    if (estado_tecla[ALLEGRO_KEY_S] || estado_tecla[ALLEGRO_KEY_DOWN])
    {
        personagem.y += personagem.vy;
        personagem.direcao = BAIXO;
        andando = true;
    }

    if (estado_tecla[ALLEGRO_KEY_A] || estado_tecla[ALLEGRO_KEY_LEFT])
    {
        personagem.x -= personagem.vx;
        personagem.direcao = ESQUERDA;
        andando = true;
    }

    if (estado_tecla[ALLEGRO_KEY_D] || estado_tecla[ALLEGRO_KEY_RIGHT])
    {
        personagem.x += personagem.vx;
        personagem.direcao = DIREITA;
        andando = true;
    }

    if (andando)
    {
        personagem.anim_contador += (int)(personagem.vx + personagem.vy); // contador recebe velocidade x e y,talvez mudar pq o personagem ta mudando o sprite muito rapido na vertical

        if (personagem.anim_contador >= personagem.anim_max) // se o contador de animacao chegar no limite estipulado na funcao desenhar
        {
            personagem.frame++;           // frame muda
            personagem.anim_contador = 0; // reseta contador

            if (personagem.frame >= personagem.max_frames) // se frame chega no ultimo la da linha
            {
                personagem.frame = 0; // frame volta ao primeiro da linha do sprite sheet
            }
        }
    }
    else
    {
        if (personagem.direcao == DIREITA) // gambiarra pq o sprite sheet do movimento pra direita começa com um sprite andando
        {
            personagem.frame = 1;
        }
        else
        {
            personagem.frame = 0; // se parado frame inicial
        }
        personagem.anim_contador = 0; // se parado contador volta ao zero, evita dele começar num sprite errado dps de ficar parado
    }

    if(cena_atual == CENA_LEVEL_1 || cena_atual == CENA_LEVEL_2 || cena_atual == CENA_LEVEL_3)
    {
        if (personagem.vida <= 0)
        {
            destruir_cena(cena_atual);
            mudar_de_cena(CENA_GAMEOVER);
            printf("GAMEOVER!\n");
        }
    }

	// checa se personagem ta saindo da tela
    checar_colisao_personagem(&personagem);
    
    for(i = 0; i < MAX_EXPRESSOES; i++)
    {
        checar_colisao_personagem_inimigo(&personagem, &inimigos[i]);
	}

    checar_colisao_personagem_inimigo(&personagem, &fileiras[fileira_ativa]);
}

void atualizar_tiro()
{
    double agora = al_get_time();

    if (estado_tecla[ALLEGRO_KEY_SPACE] && agora - ultimo_tiro >= MAX_COOLDOWN)
    {
        for (i = 0; i < MAX_TIROS; i++)
        {
            if (ataque[i].escondido) // se o tiro nao estiver sendo mostrado
            {
                ataque[i].escondido = false; // mostra
                ataque[i].direcao = personagem.direcao; // faz direcao do tiro receber a do personagem
                switch (ataque[i].direcao)
                {
                case CIMA:
                    ataque[i].x = personagem.x + personagem.w / 2 - ataque[i].w / 2;
                    ataque[i].y = personagem.y;
                    break;
                case DIREITA:
                    ataque[i].x = personagem.x + personagem.w;
                    ataque[i].y = personagem.y + personagem.h / 2 - ataque[i].h / 3; // deixei /3 pra ficar mais centrado certo seria /2
                    break;
                case ESQUERDA:
                    ataque[i].x = personagem.x;
                    ataque[i].y = personagem.y + personagem.h / 2 - ataque[i].h / 3; // deixei /3 pra ficar mais centrado certo seria /2
                    break;
                case BAIXO:
                    ataque[i].x = personagem.x + personagem.w / 2 - ataque[i].w / 2;
                    ataque[i].y = personagem.y + personagem.h;
                    break;
                }

                ultimo_tiro = agora; // tempo do ultimo tiro pra usar no cooldown
                break; // só cria 1 tiro
            }
        }
    }

    for (i = 0; i < MAX_TIROS; i++)
    {
        if (ataque[i].escondido) // se ataque nao foi "disparado" ta escondido na tela
            continue; // ignora
        switch (ataque[i].direcao) // se nao, com base na direção
        {
        case DIREITA:
            ataque[i].x += ataque[i].vx;
            if (ataque[i].x > TELA_W + ataque[i].w)
                ataque[i].escondido = true; // se passar da tela esconde
            break;
        case ESQUERDA:
            ataque[i].x -= ataque[i].vx;
            if (ataque[i].x < 0 - ataque[i].w && agora - ultimo_tiro >= MAX_COOLDOWN)
                ataque[i].escondido = true;// se passar da tela esconde
            break;
        case BAIXO:
            ataque[i].y += ataque[i].vy;
            if (ataque[i].y > TELA_H + ataque[i].h && agora - ultimo_tiro >= MAX_COOLDOWN)
                ataque[i].escondido = true;// se passar da tela esconde
            break;
        case CIMA:
            ataque[i].y -= ataque[i].vy;
            if (ataque[i].y < 0 - ataque[i].h && agora - ultimo_tiro >= MAX_COOLDOWN)
                ataque[i].escondido = true;// se passar da tela esconde
            break;
        }
    }
}