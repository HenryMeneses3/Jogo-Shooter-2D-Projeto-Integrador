#ifndef CENAS_H
#define CENAS_H

enum {
    CENA_MENU = 1,
    CENA_CUTSCENE1,
    CENA_COMO_JOGAR,
    CENA_CONFIG,
    CENA_LEVEL_1,
    CENA_LEVEL_2,
    CENA_LEVEL_3,
    CENA_GAMEOVER
};

extern int cena_atual;
extern int cena_atual_temp;
extern void mudar_de_cena(int proxima_cena);
extern void inicializar_cena(int cena);
extern void destruir_cena(int cena);
extern void passar_nivel();

#endif