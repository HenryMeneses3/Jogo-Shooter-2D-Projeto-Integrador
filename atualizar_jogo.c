#include <stdlib.h>
#include <stdio.h>
#include "config.h"
#include "recursos.h"
#include "cenas.h"
#include "objetos.h"
#include "funcoes_principais.h"

void atualizar_jogo(void)
{
    atualizar_personagem();
    atualizar_tiro();

    passar_nivel();

    if (cena_atual == CENA_LEVEL_1)
    {
        atualizar_inimigo();
        
        if (pontos >= MAX_SCORE)
        {
            destruir_cena(cena_atual);
            mudar_de_cena(CENA_CONCLUSAO);
        }
    }
    else if(cena_atual == CENA_LEVEL_2)
    {
        atualizar_inimigo();
    }
    else if(cena_atual == CENA_LEVEL_3)
    {
        if(pergunta_ativa >= MAX_PERGUNTAS && personagem.vida > 0)
        {
            destruir_cena(cena_atual);
			mudar_de_cena(CENA_CONCLUSAO);
        }
	}

}
