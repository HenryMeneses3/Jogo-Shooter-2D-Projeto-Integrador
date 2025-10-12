#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "config.h"
#include "recursos.h"
#include "cenas.h"
#include "objetos.h"
#include "input.h"


int main()
{
    srand(time(NULL));
    inicializar_allegro5();
    inicializar_jogo();
    comecar_loop_de_eventos();
    destruir_jogo();
    return 0;
}