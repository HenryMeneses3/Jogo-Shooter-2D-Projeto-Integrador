#include <stdbool.h>
#include <allegro5/allegro.h> 
#include "config.h"
#include "recursos.h"
#include "cenas.h"

void mudar_de_cena(int proxima_cena);
void destruir_cena(int cena);

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