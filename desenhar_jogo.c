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

    if (cena_atual == CENA_MENU)
    {
        al_draw_bitmap(tela_inicial_imagem, 0, 0, 0);
        al_draw_text(fonte_titulo, al_map_rgb(255, 255, 255), TELA_W / 2 - al_get_text_width(fonte_titulo, "Conta-Strike") / 2 + 20, 20, 0, "Conta-Strike");

        al_draw_bitmap(botao_2, TELA_W / 2 - al_get_bitmap_width(botao_2) - 200 / 2, 600, 0);

        al_draw_bitmap(botao_2, TELA_W / 2 + 200 / 2, 600, 0);

        al_draw_textf(fonte_gameOver, al_map_rgb(255, 255, 255), TELA_W / 2 - al_get_bitmap_width(botao_2) - 200 / 2 + (al_get_bitmap_width(botao_2) / 2) - (al_get_text_width(fonte_gameOver, "Iniciar") / 2), 600 + (al_get_bitmap_height(botao_2) / 2) - (al_get_font_line_height(fonte_gameOver) / 2) - 7, 0, "Iniciar");
        al_draw_textf(fonte_gameOver, al_map_rgb(255, 255, 255), TELA_W / 2 + 200 / 2 + (al_get_bitmap_width(botao_2) / 2) - (al_get_text_width(fonte_gameOver, "Como Jogar") / 2), 600 + (al_get_bitmap_height(botao_2) / 2) - (al_get_font_line_height(fonte_gameOver) / 2) - 7, 0, "Como Jogar");
    }

    else if (cena_atual == CENA_COMO_JOGAR)
    {
        float largura_janela = 300.0;
        float altura_janela = 175.0;
        float botao_fechar_x = TELA_W / 2 + largura_janela - 40;
        float botao_fechar_y = TELA_H / 2 - altura_janela + 10;
        float botao_fechar_tam = 30.0;

        // A “janela” central
        al_draw_filled_rounded_rectangle(TELA_W / 2 - largura_janela, TELA_H / 2 - altura_janela, TELA_W / 2 + largura_janela, TELA_H / 2 + altura_janela, 20, 20, al_map_rgb(240, 240, 240));

        // Botão fechar (círculo com X)
        al_draw_filled_circle(botao_fechar_x + botao_fechar_tam / 2, botao_fechar_y + botao_fechar_tam / 2, botao_fechar_tam / 2, al_map_rgb(220, 60, 60));
        al_draw_line(botao_fechar_x + 8, botao_fechar_y + 8, botao_fechar_x + botao_fechar_tam - 8, botao_fechar_y + botao_fechar_tam - 8, al_map_rgb(255, 255, 255), 3);
        al_draw_line(botao_fechar_x + botao_fechar_tam - 8, botao_fechar_y + 8, botao_fechar_x + 8, botao_fechar_y + botao_fechar_tam - 8, al_map_rgb(255, 255, 255), 3);

        al_draw_bitmap(botao_tecla_wasd, TELA_W / 2 - largura_janela + 20, TELA_H / 2 - altura_janela + 20, 0);
        al_draw_text(fonte_instrucoes, al_map_rgb(0, 0, 0), TELA_W / 2 - largura_janela + al_get_bitmap_width(botao_tecla_wasd) / 2 - al_get_text_width(fonte_instrucoes, "PARA ANDAR") / 2 + 20, TELA_H / 2 - altura_janela + al_get_bitmap_height(botao_tecla_wasd) - 20, 0, "PARA ANDAR");

        al_draw_bitmap(botao_tecla_space, TELA_W / 2 + 20, TELA_H / 2 - altura_janela + 20, 0);
        al_draw_text(fonte_instrucoes, al_map_rgb(0, 0, 0), TELA_W / 2 + al_get_bitmap_width(botao_tecla_space) / 2 - al_get_text_width(fonte_instrucoes, "PARA ATIRAR") / 2 + 20, TELA_H / 2 - altura_janela + al_get_bitmap_height(botao_tecla_space) - 20, 0, "PARA ATIRAR");

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

    else if (cena_atual == CENA_EXPLICACAO_1)
    {
        al_draw_bitmap(explicacao_imagem_1, 0, 0, 0);
    }

    else if (cena_atual == CENA_LEVEL_1)
    {
        al_draw_bitmap(level_1_imagem, 0, 0, 0);



        al_draw_textf(fonte_gameOver, al_map_rgb(255, 255, 255), 390, 130, 0, "PONTOS: %d", pontos);


        al_draw_textf(fonte_instrucoes, al_map_rgb(255, 255, 255), 390, 170, 0, "Nota para passar: %d pontos", MAX_SCORE);
        al_draw_textf(fonte_instrucoes, al_map_rgb(255, 255, 255), 390, 190, 0, "Lembre da aula de hoje ->");
        al_draw_textf(fonte_instrucoes, al_map_rgb(255, 255, 255), 570, 265, 0, "Ass: O Professor");





        for (i = 0; i < MAX_EXPRESSOES; i++)
        {
            al_draw_text(fonte_inimigo, al_map_rgb(244, 240, 236), inimigos[i].x, inimigos[i].y, 0, inimigos[i].expressao);
        }

    }

    else if (cena_atual == CENA_CUTSCENE2)
    {

        al_draw_filled_rectangle(0, 0, TELA_W, TELA_H, al_map_rgb(0, 0, 0)); // fundo preto

        for (i = 0; i <= cutscene_quadrante_atual; i++) // desenha quadrantes ja revelados
        {
            int dest_x = (i % 2 == 0) ? (TELA_W / 2 - tamanho_quadrante_cutscene) : (TELA_W / 2); // esquerda ou direita
            int dest_y = (i < 2) ? (TELA_H / 2 - tamanho_quadrante_cutscene) : (TELA_H / 2); // cima ou baixo

            al_draw_tinted_bitmap_region(
                cutscene_2_imagem,
                al_map_rgba_f(1, 1, 1, alpha_quadrante[i]),
                tamanho_quadrante_cutscene * i, 0,
                tamanho_quadrante_cutscene, tamanho_quadrante_cutscene,
                dest_x, dest_y, 0
            ); // desenha o quadrante com o alpha atual
        }
    }

    else if (cena_atual == CENA_EXPLICACAO_2)
    {
        al_draw_bitmap(explicacao_imagem_2, 0, 0, 0);
    }

    else if (cena_atual == CENA_LEVEL_2)
    {
        al_draw_bitmap(level_2_imagem, 0, 0, 0);

        al_draw_bitmap(fileiras[fileira_ativa].img, fileiras[fileira_ativa].x, fileiras[fileira_ativa].y, 0);

        char texto1[100]; // cria um buffer de texto
        snprintf(texto1, sizeof(texto1), "Acerte o animal - %s: %s", infofileiras[fileira_ativa].Tipo, infofileiras[fileira_ativa].termo);

        char texto2[100];
        snprintf(texto2, sizeof(texto2), "Dica: %s", infofileiras[fileira_ativa].dica);


        al_draw_text(fonte_instrucoes, al_map_rgb(255, 255, 255), TELA_W / 2 - al_get_text_width(fonte_instrucoes, texto1) / 2, 500, 0, texto1);

        al_draw_text(fonte_instrucoes, al_map_rgb(255, 255, 255), TELA_W / 2 - al_get_text_width(fonte_instrucoes, texto2) / 2, 530, 0, texto2);

    }

    else if (cena_atual == CENA_CUTSCENE3)
    {
        al_draw_filled_rectangle(0, 0, TELA_W, TELA_H, al_map_rgb(0, 0, 0)); // fundo preto

        for (i = 0; i <= cutscene_quadrante_atual; i++) // desenha quadrantes ja revelados
        {
            int dest_x = (i % 2 == 0) ? (TELA_W / 2 - tamanho_quadrante_cutscene) : (TELA_W / 2); // esquerda ou direita
            int dest_y = (i < 2) ? (TELA_H / 2 - tamanho_quadrante_cutscene) : (TELA_H / 2); // cima ou baixo

            al_draw_tinted_bitmap_region(
                cutscene_3_imagem,
                al_map_rgba_f(1, 1, 1, alpha_quadrante[i]),
                tamanho_quadrante_cutscene * i, 0,
                tamanho_quadrante_cutscene, tamanho_quadrante_cutscene,
                dest_x, dest_y, 0
            ); // desenha o quadrante com o alpha atual
        }
    }

    else if (cena_atual == CENA_EXPLICACAO_3)
    {
        al_draw_bitmap(explicacao_imagem_3, 0, 0, 0);
    }

    else if (cena_atual == CENA_LEVEL_3)
    {
        al_draw_bitmap(level_3_imagem, 0, 0, 0);

        char texto1[100];
        snprintf(texto1, sizeof(texto1), "Pergunta %d:", pergunta_ativa + 1);

        char pergunta[100];
        snprintf(pergunta, sizeof(pergunta), "%s", perguntas[pergunta_ativa].pergunta);

        // Guarda as alternativas
        char alternativa1[100];
        char alternativa2[100];
        char alternativa3[100];
        char alternativa4[100];

        snprintf(alternativa1, sizeof(alternativa1), "%s", perguntas[pergunta_ativa].opcoes[0]);
        snprintf(alternativa2, sizeof(alternativa2), "%s", perguntas[pergunta_ativa].opcoes[1]);
        snprintf(alternativa3, sizeof(alternativa3), "%s", perguntas[pergunta_ativa].opcoes[2]);
        snprintf(alternativa4, sizeof(alternativa4), "%s", perguntas[pergunta_ativa].opcoes[3]);

        int largura_tela = 98;
        int altura_tela = 58;

        // === TELA 1: X - 100 | Y - 400 ===
        al_draw_textf(fonte_gameOver, al_map_rgb(255, 255, 255),
            100 + largura_tela / 2 - al_get_text_width(fonte_gameOver, alternativa1) / 2,
            400 + altura_tela / 2 - al_get_font_line_height(fonte_gameOver) / 2,
            0, alternativa1);

        // === TELA 2: X - 375 | Y - 275 ===
        al_draw_textf(fonte_gameOver, al_map_rgb(255, 255, 255),
            375 + largura_tela / 2 - al_get_text_width(fonte_gameOver, alternativa2) / 2,
            275 + altura_tela / 2 - al_get_font_line_height(fonte_gameOver) / 2,
            0, alternativa2);

        // === TELA 3: X - (TELA_W - largura_tela - 375) | Y - 275 ===
        al_draw_textf(fonte_gameOver, al_map_rgb(255, 255, 255),
            TELA_W - largura_tela - 375 + largura_tela / 2 - al_get_text_width(fonte_gameOver, alternativa3) / 2,
            275 + altura_tela / 2 - al_get_font_line_height(fonte_gameOver) / 2,
            0, alternativa3);

        // === TELA 4: X - (TELA_W - largura_tela - 100) | Y - 400 ===
        al_draw_textf(fonte_gameOver, al_map_rgb(255, 255, 255),
            TELA_W - largura_tela - 100 + largura_tela / 2 - al_get_text_width(fonte_gameOver, alternativa4) / 2,
            400 + altura_tela / 2 - al_get_font_line_height(fonte_gameOver) / 2,
            0, alternativa4);

        // Texto da pergunta
        al_draw_textf(fonte_instrucoes, al_map_rgb(255, 255, 255),
            TELA_W / 2 - al_get_text_width(fonte_instrucoes, texto1) / 2,
            70, 0, texto1);


        al_draw_textf(fonte_score, al_map_rgb(255, 255, 255),
            TELA_W / 2 - al_get_text_width(fonte_score, pergunta) / 2,
            TELA_H - al_get_font_line_height(fonte_score) - 70,
            0, pergunta);
    }

    else if(cena_atual == CENA_CUTSCENE4)
    {
        al_draw_filled_rectangle(0, 0, TELA_W, TELA_H, al_map_rgb(0, 0, 0)); // fundo preto
        for (i = 0; i <= cutscene_quadrante_atual; i++) // desenha quadrantes ja revelados
        {
            int dest_x = (i % 2 == 0) ? (TELA_W / 2 - tamanho_quadrante_cutscene) : (TELA_W / 2); // esquerda ou direita
            int dest_y = (i < 2) ? (TELA_H / 2 - tamanho_quadrante_cutscene) : (TELA_H / 2); // cima ou baixo
            al_draw_tinted_bitmap_region(
                cutscene_4_imagem,
                al_map_rgba_f(1, 1, 1, alpha_quadrante[i]),
                tamanho_quadrante_cutscene * i, 0,
                tamanho_quadrante_cutscene, tamanho_quadrante_cutscene,
                dest_x, dest_y, 0
            ); // desenha o quadrante com o alpha atual
        }
	}

    else if(cena_atual == CENA_FIM_JOGO)
    {
		al_draw_bitmap(final_imagem, 0, 0, 0);

		al_draw_textf(fonte_titulo, al_map_rgb(255, 255, 255), TELA_W / 2 - al_get_text_width(fonte_titulo, "Parabens") / 2, 100, 0, "Parabens!");
        al_draw_textf(fonte_gameOver, al_map_rgb(255, 255, 255), TELA_W / 2 - al_get_text_width(fonte_gameOver, "Voce conquistou seu diploma") / 2, 250, 0, "Voce conquistou seu diploma");

        al_draw_bitmap(botao_2, TELA_W / 2 - al_get_bitmap_width(botao_2) / 2, 650, 0);

		al_draw_text(fonte_gameOver, al_map_rgb(255, 255, 255), TELA_W / 2 - al_get_bitmap_width(botao_2) / 2 + (al_get_bitmap_width(botao_2) / 2) - (al_get_text_width(fonte_gameOver, "Voltar") / 2), 650 + (al_get_bitmap_height(botao_2) / 2) - (al_get_font_line_height(fonte_gameOver) / 2) - 7, 0, "Voltar");
    }

    else if (cena_atual == CENA_CONCLUSAO)
    {
        al_draw_bitmap(botao_conclusao, TELA_W / 2 - al_get_bitmap_width(botao_conclusao) / 2, TELA_H / 2 - al_get_bitmap_height(botao_conclusao) / 2, 0);

        if (cena_atual_temp == CENA_LEVEL_1)
        {
            al_draw_textf(fonte_gameOver, al_map_rgb(255, 255, 255), TELA_W / 2 - al_get_text_width(fonte_gameOver, "Conseguiu!") / 2, 200, 0, "Conseguiu!");
            al_draw_textf(fonte_instrucoes, al_map_rgb(255, 255, 255), TELA_W / 2 - al_get_text_width(fonte_instrucoes, "Voce passou de nivel com %d vida(s)!") / 2 + 10, 280, 0, "Voce passou de nivel com %d vida(s)!", personagem.vida);
            al_draw_textf(fonte_instrucoes, al_map_rgb(255, 255, 255), TELA_W / 2 - al_get_text_width(fonte_instrucoes, "Clique no botao para passar.") / 2 + 10, 320, 0, "Clique no botao para passar.");
        }
        else if (cena_atual_temp == CENA_LEVEL_2 || cena_atual_temp == CENA_LEVEL_3)
        {
            al_draw_textf(fonte_gameOver, al_map_rgb(255, 255, 255), TELA_W / 2 - al_get_text_width(fonte_gameOver, "Conseguiu!") / 2, 200, 0, "Conseguiu!");
            al_draw_textf(fonte_instrucoes, al_map_rgb(255, 255, 255), TELA_W / 2 - al_get_text_width(fonte_instrucoes, "Voce passou de nivel com %d vida(s)!") / 2 + 10, 280, 0, "Voce passou de nivel com %d vida(s)!", personagem.vida);
            al_draw_textf(fonte_instrucoes, al_map_rgb(255, 255, 255), TELA_W / 2 - al_get_text_width(fonte_instrucoes, "Voce acertou %d/8 corretamente!") / 2 + 10, 320, 0, "Voce acertou % d / 8 corretamente!", pontos);
            al_draw_textf(fonte_instrucoes, al_map_rgb(255, 255, 255), TELA_W / 2 - al_get_text_width(fonte_instrucoes, "Clique no botao para passar.") / 2 + 10, 360, 0, "Clique no botao para passar.");
        }
    }


    else if (cena_atual == CENA_GAMEOVER)
    {

        al_draw_bitmap(game_over_imagem, 0, 0, 0);

        al_draw_text(fonte_score, al_map_rgb(255, 255, 255), TELA_W / 2 - al_get_text_width(fonte_score, "GAMEOVER") / 2, 200, 0, "GAMEOVER");

        al_draw_text(fonte_gameOver, al_map_rgb(255, 255, 255), TELA_W / 2 - al_get_text_width(fonte_gameOver, "Tentar novamente?") / 2, 275, 0, "Tentar novamente?");

        al_draw_bitmap(botao_1, (TELA_W / 2 - al_get_bitmap_width(botao_1)) - 20, 400, 0);
        al_draw_bitmap(botao_1, TELA_W / 2 + 40, 400, 0);

        al_draw_text(fonte_gameOver, al_map_rgb(255, 255, 255), TELA_W / 2 + al_get_bitmap_width(botao_1) / 2 - (al_get_text_width(fonte_gameOver, "Nao") / 2) + 40, 400 + (al_get_bitmap_height(botao_1) / 2) - (al_get_font_line_height(fonte_gameOver) / 2) - 7, 0, "Nao");
        al_draw_text(fonte_gameOver, al_map_rgb(255, 255, 255), (TELA_W / 2 - al_get_bitmap_width(botao_1) / 2) - (al_get_text_width(fonte_gameOver, "Sim") / 2) - 23, 400 + (al_get_bitmap_height(botao_1) / 2) - (al_get_font_line_height(fonte_gameOver) / 2) - 7, 0, "Sim");
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