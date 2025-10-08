#include "config.h"
#include "recursos.h"
#include "cenas.h"
#include "objetos.h"
#include "input.h"

void inicializar_cena(cena);

void desenhar_objeto_movel(ObjetoMovel objeto)
{
    if (objeto.escondido)
        return;

    if (objeto.sprite_sheet) // gambiarra pq o personagem principal é de uma spritesheet
    {
        al_draw_bitmap_region(objeto.img, objeto.frame * objeto.w, objeto.direcao * objeto.h, objeto.w, objeto.h, objeto.x, objeto.y, 0);
    }
    else
    {
        al_draw_bitmap(objeto.img, objeto.x, objeto.y, 0);
    }
}


void desenhar_jogo()
{
    if (cena_atual != CENA_GAMEOVER && cena_atual != CENA_MENU)
    {
        al_draw_bitmap(level_1_imagem, 0, 0, 0);

        if (personagem.vida == 3)
        {
            al_draw_bitmap(vida_imagem, 50, 20, 0);
            al_draw_bitmap(vida_imagem, 100, 20, 0);
            al_draw_bitmap(vida_imagem, 150, 20, 0);
        }
        else if (personagem.vida == 2)
        {
            al_draw_bitmap(vida_imagem, 50, 20, 0);
            al_draw_bitmap(vida_imagem, 100, 20, 0);
        }
        else if (personagem.vida == 1)
        {
            al_draw_bitmap(vida_imagem, 50, 20, 0);
        }

        for (i = 0; i < MAX_INIMIGOS; i++)
        {
            al_draw_text(fonte_inimigo, al_map_rgb(244, 240, 236), inimigos[i].x, inimigos[i].y, 0, inimigos[i].expressao);
        }
        for (i = 0; i < MAX_TIROS; i++)
        {
            desenhar_objeto_movel(ataque[i]);
        }

        
        al_draw_textf(fonte_gameOver, al_map_rgb(0, 0, 0), 64, 100, 0, "PONTOS: %d", pontos);
        desenhar_objeto_movel(personagem);
    }

    else if(cena_atual == CENA_LEVEL_2)
    {

    }

    else if (cena_atual == CENA_GAMEOVER)
    {
        al_draw_bitmap(game_over_imagem, 0, 0, 0);
        al_draw_text(fonte_score, al_map_rgb(255, 255, 255), TELA_W / 2 - al_get_text_width(fonte_score, "GAMEOVER") / 2, 200, 0, "GAMEOVER");
        al_draw_text(fonte_gameOver, al_map_rgb(255, 255, 255), TELA_W / 2 - al_get_text_width(fonte_gameOver, "Tentar novamente?") / 2, 275, 0, "Tentar novamente?");
        al_draw_bitmap(botao_1, (TELA_W / 2 - al_get_bitmap_width(botao_1)) - 20, 400, 0);
        al_draw_bitmap(botao_1, TELA_W / 2 + 40, 400, 0);
        al_draw_text(fonte_gameOver, al_map_rgb(255, 255, 255), TELA_W / 2 + al_get_bitmap_width(botao_1) / 2 - (al_get_text_width(fonte_gameOver, "No") / 2) + 40, 400 + (al_get_bitmap_height(botao_1) / 2) - (al_get_font_line_height(fonte_gameOver) / 2) - 7, 0, "No");
        al_draw_text(fonte_gameOver, al_map_rgb(255, 255, 255), (TELA_W / 2 - al_get_bitmap_width(botao_1) / 2) - (al_get_text_width(fonte_gameOver, "Yes") / 2) - 23, 400 + (al_get_bitmap_height(botao_1) / 2) - (al_get_font_line_height(fonte_gameOver) / 2) - 7, 0, "Yes");
    }

    al_flip_display();
}