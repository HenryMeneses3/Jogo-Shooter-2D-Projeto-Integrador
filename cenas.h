#ifndef CENAS_H
#define CENAS_H

enum {
    CENA_MENU = 1,
    CENA_LEVEL_1,
    CENA_LEVEL_2,
    CENA_LEVEL_3,
    CENA_GAMEOVER,
    CENA_CONFIG
};

extern int cena_atual;
extern void mudar_de_cena(int proxima_cena);
extern void inicializar_cena(int cena);
extern void destruir_cena(int cena);

#endif