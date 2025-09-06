#include "recursos.h"
#include "movel.h"

const int level1Chao;

void mudar_de_cena(int proxima_cena)
{
    cena_atual = proxima_cena;
    inicializar_cena(cena_atual);


    if (cena_atual == CENA_LEVEL_1 || cena_atual == CENA_LEVEL_2 || cena_atual == CENA_LEVEL_3)
    {
        //PERSONAGEM
        personagem.imagem = personagem_imagem;                      // direciona imagem carregada pra struct
        personagem.w = al_get_bitmap_width(personagem.imagem) / 4;  // largura do sprite
        personagem.h = al_get_bitmap_height(personagem.imagem) / 4; // altura do sprite
        personagem.vx = VELOCIDADE_PERSONAGEM;                      // velocidade eixo x do personagem
        personagem.vy = VELOCIDADE_PERSONAGEM;                      // velocidade eixo y do personagem
        personagem.max_frames = 4;                                  // sprite sheet de 4 frames pro loop
        personagem.anim_contador = 0;                               // contador que vai receber as velocidades x e y
        personagem.anim_max = 50;                                   // indexador para usar velocidade vx e vy como base na velocidade da mudança do sprite
        personagem.sprite_sheet = true;                             // vai desenhar com bitmapregion
        personagem.escondido = false;                               // mostra personagem na tela

        //ATAQUE
        for (i = 0; i < MAX_TIROS; i++)
        {
            ataque[i].imagem = ataque_imagem;                    // direciona imagem carregada pra struct
            ataque[i].w = al_get_bitmap_width(ataque_imagem);    // largura do ataque
            ataque[i].h = al_get_bitmap_height(ataque_imagem);   // altura do ataque
            ataque[i].vx = VELOCIDADE_ATAQUE;                    // velocidade eixo x do ataque
            ataque[i].vy = VELOCIDADE_ATAQUE;                    // velocidade eixo y do ataque
            ataque[i].escondido = true;                          // ataque começa escondido ate ser disparado
            ataque[i].sprite_sheet = false;                      // vai carregar so o png com load bitmap
        }

        if (cena_atual == CENA_LEVEL_1)
        {
            personagem.escondido = false;                 // mostra personagem na tela
            personagem.x = TELA_W / 2 - personagem.w / 2; // inicia no centro da tela no eixo x
            personagem.y = (level1Chao + (TELA_H - level1Chao) / 2) - personagem.h / 2; // inicia no centro y do chao do level1
            personagem.direcao = 0;                      // inicia olhando pra baixo
            personagem.frame = 0;                        // inicia no frame 0
        }
    }
}