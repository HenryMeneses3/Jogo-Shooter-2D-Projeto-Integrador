#include "recursos.h"
#include "movel.h"


void inicializar_cena(cena);

void desenhar_objeto_movel(ObjetoMovel objeto)
{
    if (objeto.escondido)
        return;

    if (objeto.sprite_sheet)
    {
        al_draw_bitmap_region(objeto.imagem, objeto.frame * objeto.w, objeto.direcao * objeto.h, objeto.w, objeto.h, objeto.x, objeto.y, 0);
    }
    else
    {
        al_draw_bitmap(objeto.imagem, objeto.x, objeto.y, 0);
    }
}

void desenhar_jogo()
{
    if (cena_atual == CENA_LEVEL_1)
    {
        al_draw_bitmap(level_1_imagem, 0, 0, 0);
        desenhar_objeto_movel(personagem);

        for (i = 0; i < MAX_TIROS; i++)
        {
            desenhar_objeto_movel(ataque[i]);
        }

    }
    al_flip_display();
}