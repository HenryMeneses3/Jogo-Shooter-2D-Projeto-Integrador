#include "recursos.h"
#include "movel.h"
#include "input.h"

double ultimo_ataque = 0;
bool estado_tecla[ALLEGRO_KEY_MAX];

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
        personagem.anim_contador += (personagem.vx + personagem.vy); // contador recebe velocidade x e y,talvez mudar pq o personagem ta mudando o sprite muito rapido na vertical

        if (personagem.anim_contador >= personagem.anim_max) // se o contador de animacao chegar no limite estipulado na funcao desenhar
        {
            personagem.frame++;           // frame muda
            personagem.anim_contador = 0; // reseta contador

            if (personagem.frame >= personagem.max_frames) // se frame chega no ultimo la da linha do spritesheet
            {
                personagem.frame = 0; // frame volta ao primeiro da linha do sprite sheet
            }
        }
    }
    else
    {
        if (personagem.direcao == DIREITA) // gambiarra pq o sprite sheet do movimento pra direita começa com um sprite animado dele andando
        {
            personagem.frame = 1; // o frame vai pra segunda coluna que é o sprite dele parado
        }
        else
        {
            personagem.frame = 0; // se parado frame inicial
        }
        personagem.anim_contador = 0; // se parado contador volta ao zero, evita dele começar num sprite errado dps de ficar parado
    }

    // PRENDER NA TELA
    if (cena_atual == CENA_LEVEL_1)
    {
        if (personagem.x < 0) // se personagem tentar passar da tela pela esquerda
            personagem.x = 0; // posicao x (canto superior esquerdo) volta pra zero, ele "teleporta" de volta
        else if (personagem.x > TELA_W - personagem.w)  // se personagem tentar passar da tela pela direita
            personagem.x = TELA_W - personagem.w; // posicao x (canto superior esquerdo) volta pra final da tela, ele "teleporta" de volta

        if (personagem.y - personagem.h / 2 < level1Chao - personagem.h / 2) // escrevi personagem.y - personagem.h / 2 pra ele passar metade do corpo e dar um efeito legal
            personagem.y = level1Chao;
        else if (personagem.y > TELA_H - personagem.h)
            personagem.y = TELA_H - personagem.h;
    }

}

void atualizar_tiro()
{
    double agora = al_get_time();

    if (estado_tecla[ALLEGRO_KEY_SPACE] && agora - ultimo_ataque >= MAX_COOLDOWN) // se a tecla foi pressionada e o ultimo ataque ainda nao foi menor que o cooldown
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

                ultimo_ataque = agora; // tempo do ultimo tiro pra usar no cooldown e nessa propria função
                break; // só cria 1 tiro
            }
        }
    }

    for (i = 0; i < MAX_TIROS; i++)
    {
        if (ataque[i].escondido) // se ataque nao foi disparado "ta escondido" na tela
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
            if (ataque[i].x < 0 - ataque[i].w)
                ataque[i].escondido = true;// se passar da tela esconde
            break;
        case BAIXO:
            ataque[i].y += ataque[i].vy;
            if (ataque[i].y > TELA_H + ataque[i].h)
                ataque[i].escondido = true;// se passar da tela esconde
            break;
        case CIMA:
            ataque[i].y -= ataque[i].vy;
            if (ataque[i].y < 0 - ataque[i].h)
                ataque[i].escondido = true;// se passar da tela esconde
            break;
        }
    }
}

void atualizar_jogo(void)
{
    atualizar_personagem();
    atualizar_tiro();
}