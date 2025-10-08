#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "config.h"
#include "recursos.h"
#include "cenas.h"
#include "objetos.h"
#include "input.h"



void atualizar_jogo(void);

void atualizar_jogo(void) 
{
    atualizar_personagem();
    atualizar_tiro();
    atualizar_inimigo();

    if (cena_atual == CENA_LEVEL_1) 
    {
        if (personagem.vida <= 0)
        {
            destruir_cena(cena_atual);
            mudar_de_cena(CENA_GAMEOVER);
            printf("GAMEOVER!\n");
        }
        if (pontos >= 150)
            mudar_de_cena(CENA_LEVEL_2);
    }
}


int main()
{
    srand(time(NULL));
    inicializar_allegro5();
    inicializar_jogo();
    comecar_loop_de_eventos();
    destruir_jogo();
    return 0;
}