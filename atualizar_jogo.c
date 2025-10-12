#include <stdlib.h>
#include <stdio.h>
#include "config.h"
#include "recursos.h"
#include "cenas.h"
#include "objetos.h"

void atualizar_jogo(void)
{
    atualizar_personagem();
    atualizar_tiro();

    passar_nivel();

    if (cena_atual == CENA_LEVEL_1)
    {
        atualizar_inimigo();
        
        if (pontos >= 150)
        {
            destruir_cena(cena_atual);
            mudar_de_cena(CENA_LEVEL_2);
            printf("Fase 2!\n");
        }
    }

}
