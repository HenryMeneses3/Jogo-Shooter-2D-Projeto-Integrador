#include "config.h"
#include "recursos.h"
#include "cenas.h"
#include "objetos.h"
#include "input.h"
#include "funcoes_principais.h"


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

    if(cena_atual == CENA_MENU)
    {
        al_draw_bitmap(tela_inicial_imagem, 0, 0, 0);
		al_draw_text(fonte_titulo, al_map_rgb(255, 255, 255), TELA_W / 2 - al_get_text_width(fonte_titulo, "Conta-Strike") / 2 + 20, 20, 0, "Conta-Strike");

		al_draw_bitmap(botao_2, TELA_W / 2 - al_get_bitmap_width(botao_2) - 200 / 2, 600, 0);

        al_draw_bitmap(botao_2, TELA_W / 2 + 200 / 2, 600, 0);

		al_draw_textf(fonte_gameOver, al_map_rgb(255, 255, 255), TELA_W / 2 - al_get_bitmap_width(botao_2) - 200 / 2 + (al_get_bitmap_width(botao_2) / 2) - (al_get_text_width(fonte_gameOver, "Iniciar") / 2), 600 + (al_get_bitmap_height(botao_2) / 2) - (al_get_font_line_height(fonte_gameOver) / 2) - 7, 0, "Iniciar");
		al_draw_textf(fonte_gameOver, al_map_rgb(255, 255, 255), TELA_W / 2 + 200 / 2 + (al_get_bitmap_width(botao_2) / 2) - (al_get_text_width(fonte_gameOver, "Como Jogar") / 2), 600 + (al_get_bitmap_height(botao_2) / 2) - (al_get_font_line_height(fonte_gameOver) / 2) - 7, 0, "Como Jogar");
	}

    else if(cena_atual == CENA_COMO_JOGAR)
    {
        float largura_janela = 300.0;
        float altura_janela = 175.0;
        float botao_fechar_x = TELA_W / 2 + largura_janela - 40;
        float botao_fechar_y = TELA_H / 2 - altura_janela + 10;
        float botao_fechar_tam = 30.0;

        // A “janela” central
        al_draw_filled_rounded_rectangle(TELA_W / 2 - largura_janela, TELA_H / 2 - altura_janela, TELA_W/2 + largura_janela, TELA_H / 2 + altura_janela, 20, 20, al_map_rgb(240, 240, 240));

        // Botão fechar (círculo com X)
        al_draw_filled_circle(botao_fechar_x + botao_fechar_tam / 2, botao_fechar_y + botao_fechar_tam / 2, botao_fechar_tam / 2, al_map_rgb(220, 60, 60));
        al_draw_line(botao_fechar_x + 8, botao_fechar_y + 8, botao_fechar_x + botao_fechar_tam - 8, botao_fechar_y + botao_fechar_tam - 8, al_map_rgb(255, 255, 255), 3);
        al_draw_line(botao_fechar_x + botao_fechar_tam - 8, botao_fechar_y + 8, botao_fechar_x + 8, botao_fechar_y + botao_fechar_tam - 8, al_map_rgb(255, 255, 255), 3);

		al_draw_bitmap(botao_tecla_wasd, TELA_W / 2 - largura_janela + 20, TELA_H / 2 - altura_janela + 20, 0);
        al_draw_text(fonte_gameOver, al_map_rgb(0, 0, 0), TELA_W / 2 - largura_janela + al_get_bitmap_width(botao_tecla_wasd) / 2 - al_get_text_width(fonte_gameOver, "PARA ANDAR") / 2 + 20, TELA_H / 2 - altura_janela + al_get_bitmap_height(botao_tecla_wasd) - 20, 0, "PARA ANDAR");

        al_draw_bitmap(botao_tecla_space, TELA_W / 2  + 20, TELA_H / 2 - altura_janela + 20, 0);
        al_draw_text(fonte_gameOver, al_map_rgb(0, 0, 0), TELA_W / 2 + al_get_bitmap_width(botao_tecla_space) / 2 - al_get_text_width(fonte_gameOver, "PARA ATIRAR") / 2 + 20, TELA_H / 2 - altura_janela + al_get_bitmap_height(botao_tecla_space) - 20, 0, "PARA ATIRAR");
    
    }

    else if (cena_atual == CENA_CUTSCENE1)
    {
        
		al_draw_filled_rectangle(0, 0, TELA_W, TELA_H, al_map_rgb(0, 0, 0)); // fundo preto

		for (i = 0; i <= cutscene_quadrante_atual; i++) // desenha quadrantes ja revelados
        {
			int dest_x = (i % 2 == 0) ? (TELA_W / 2 - tamanho_quadrante_cutscene) : (TELA_W / 2); // esquerda ou direita
			int dest_y = (i < 2) ? (TELA_H / 2 - tamanho_quadrante_cutscene) : (TELA_H / 2); // cima ou baixo

            al_draw_tinted_bitmap_region(
                cutscene_1_imagem,
                al_map_rgba_f(1, 1, 1, alpha_quadrante[i]),
                tamanho_quadrante_cutscene * i, 0,
                tamanho_quadrante_cutscene, tamanho_quadrante_cutscene,
                dest_x, dest_y, 0
			); // desenha o quadrante com o alpha atual
        }
    }

    else if (cena_atual == CENA_LEVEL_1)
    {
        al_draw_bitmap(level_1_imagem, 0, 0, 0);



        al_draw_textf(fonte_gameOver, al_map_rgb(255, 255, 255), 400, 130, 0, "PONTOS: %d", pontos);



		al_draw_textf(fonte_instrucoes, al_map_rgb(255, 255, 255), 400, 180, 0, "Alunos, ACERTEM as palavras corretas para ganhar pontos");
        al_draw_textf(fonte_instrucoes, al_map_rgb(255, 255, 255), 400, 210, 0, "Nota para passar: 150 pontos");
        al_draw_textf(fonte_instrucoes, al_map_rgb(255, 255, 255), 570, 250, 0, "Ass: O Professor");
       
      

        for (i = 0; i < MAX_INIMIGOS; i++)
        {
            al_draw_text(fonte_inimigo, al_map_rgb(244, 240, 236), inimigos[i].x, inimigos[i].y, 0, inimigos[i].expressao);
        }

    }

    else if(cena_atual == CENA_LEVEL_2)
    {
        al_draw_bitmap(level_2_imagem, 0, 0, 0);
    }
    
    else if (cena_atual == CENA_LEVEL_3)
    {
        al_draw_bitmap(level_3_imagem, 0, 0, 0);
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

    if (cena_atual == CENA_LEVEL_1 || cena_atual == CENA_LEVEL_2 || cena_atual == CENA_LEVEL_3)
    {
		desenhar_objeto_movel(personagem);

        for (i = 0; i < MAX_TIROS; i++)
        {
            desenhar_objeto_movel(ataque[i]);
        }

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

    }

    al_flip_display();
}