#include <stdbool.h>
#include <allegro5/allegro.h> 
#include "config.h"
#include "recursos.h"
#include "cenas.h"
#include "objetos.h"

bool hitbox_em_um_retangulo(int posXp, int posYp, int pW, int pH, int posXret, int posYret, int retH, int retW)
{
    return posXp + pW > posXret &&
        posYp + pH > posYret &&
        posXp < posXret + retW &&
        posYp < posYret + retH;
}

bool mouse_em_retangulo(int mX, int mY, int retX, int retY, int retW, int retH)
{
    return mX > retX &&
        mX < retX + retW &&
        mY > retY &&
        mY < retY + retH;
}

void mouse_apertado(int botao, int x, int y)
{

    if (cena_atual == CENA_GAMEOVER)
    {
        if (botao == true)
        {
            bool sim = mouse_em_retangulo(x, y, (TELA_W / 2 - al_get_bitmap_width(botao_1)) - 20, 400, al_get_bitmap_width(botao_1), al_get_bitmap_height(botao_1));
            bool nao = mouse_em_retangulo(x, y, TELA_W / 2 + 40, 400, al_get_bitmap_width(botao_1), al_get_bitmap_height(botao_1));
            if (sim)
            {
                al_play_sample(botao_som, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &botao_som_id);
                destruir_cena(CENA_GAMEOVER);
                mudar_de_cena(CENA_LEVEL_1);
                printf("Reiniciando Level 1\n");
            }
            else if (nao)
            {
                al_play_sample(botao_som, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &botao_som_id);
                destruir_cena(CENA_GAMEOVER);
                mudar_de_cena(CENA_MENU);
                printf("Voltando ao menu\n");
            }
        }
    }
}

void checar_colisao_personagem(ObjetoMovel *personagem)
{

    if (cena_atual == CENA_LEVEL_1)
    {
        // PERSONAGEM PRESO NA TELA LEVEL 1
        if (personagem->x < 0) // se personagem tentar passar da tela pela esquerda
            personagem->x = 0; // posicao x (canto superior esquerdo) volta pra zero, ele meio q teleporta de volta
        else                  // mesma coisa so que pro final da tela
        {
            if (personagem->x > TELA_W - personagem->w) // como x ta no lado esquerdo superior do sprite tive q fazer - a largura do sprite
                personagem->x = TELA_W - personagem->w;
        }
        if (personagem->y - personagem->h / 2 < level1Floor - personagem->h / 2) // variavel daonde o chao começa no level 1,
            personagem->y = level1Floor; // escrevi em cima personagem.y - personagem.h / 2 pra ele passar metade do corpo e dar um efeito legal
        else
        {
            if (personagem->y > TELA_H - personagem->h)
                personagem->y = TELA_H - personagem->h;
        }
    }

    else if (cena_atual == CENA_LEVEL_2)
    {
        // PERSONAGEM PRESO NA TELA LEVEL 2
        if (personagem->x < level2Left)
            personagem->x = level2Left;
        else if (personagem->x > level2Right - personagem->w)
            personagem->x = level2Right - personagem->w;

        if (personagem->y + personagem->h > level2Floor)
            personagem->y = level2Floor - personagem->h;
        else
        {
            if (personagem->y < 0)
                personagem->y = 0;
        }
    }
}

void checar_colisao_personagem_inimigo(ObjetoMovel* personagem, ObjetoMovel* inimigos)
{
    
    // COLISAO INIMIGO COM PERSONAGEM NO LEVEL 1
    if (cena_atual == CENA_LEVEL_1)
    {
        for (i = 0; i < MAX_INIMIGOS; i++)
        {
            if (inimigos[i].escondido)
                continue;
            if (hitbox_em_um_retangulo(personagem->x + 12, personagem->y + 13, personagem->w - 12, personagem->h - 13, inimigos[i].x, inimigos[i].y, inimigos[i].h, inimigos[i].w)) // deixei menos 12 pra tentar ficar com um hitbox menor
            {
                printf("Ai nao po, tomou dano!\n");
                personagem->vida--;
                resetar_inimigo(&inimigos[i]);
            }
        }
    }
}