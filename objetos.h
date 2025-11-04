#ifndef OBJETOS_H
#define OBJETOS_H

#include <allegro5/allegro.h>
#include <stdbool.h> 
#include "config.h"


enum 
{
    BAIXO = 0,
    CIMA,
    ESQUERDA,
    DIREITA
};

typedef struct 
{
    float x, y;  // posição
    float w, h;  // largura/altura
    float vx, vy; // velocidade
    int vida; // vida do personagem
    bool escondido; //aparece na tela ou não
    bool sprite_sheet;// vai usar sprite sheet (bitmapregion)
    bool inimigo;// é inimigo ou nao
    ALLEGRO_BITMAP* img; // imagem
    char expressao[MAX_EXPRESSOES * 50];// expressao pros inimigos maximo 50 caracteres
    int frame, max_frames; // contagem de frames
    int direcao;// direcao
    int anim_contador, anim_max; // flag pra mudar frame
	float invencibilidade_timer; // tempo restante de invencibilidade

} ObjetoMovel;


extern ObjetoMovel personagem;
extern ObjetoMovel inimigos[MAX_EXPRESSOES];
extern ObjetoMovel ataque[MAX_TIROS];
extern ObjetoMovel fileiras[MAX_FILEIRAS];

extern int ordem_fileiras[MAX_FILEIRAS];
extern int indice_ordem_atual;
extern int fileira_ativa;

extern int tamanho_fileira_certa;

extern double ultimo_tiro;

extern void desenhar_objeto_movel(ObjetoMovel objeto);
extern void atualizar_personagem(void);
extern void atualizar_inimigo(void);
extern void atualizar_tiro(void);
extern void desenhar_objeto_movel(ObjetoMovel objeto);
extern void resetar_inimigo(ObjetoMovel* inimigo);
extern void sortear_fileira();

typedef struct 
{
    const char* texto;
    bool correta;
} Expressao;

extern Expressao expressoes[];
extern int total_de_expressoes;


typedef struct 
{ 
    char termo[50];
    char Tipo[50];
    int posXcerto;
} Fileira;

extern Fileira infofileiras[];
extern int total_de_fileiras;


#endif
