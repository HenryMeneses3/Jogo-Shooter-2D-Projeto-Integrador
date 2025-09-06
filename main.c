#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "movel.h"
#include "recursos.h"


ObjetoMovel personagem;
ObjetoMovel ataque[MAX_TIROS];




void inicializar_allegro5(void);
void inicializar_jogo(void);
void comecar_loop_de_eventos(void);


int main()
{
    inicializar_allegro5();
    inicializar_jogo();
    comecar_loop_de_eventos();
    return 0;
}