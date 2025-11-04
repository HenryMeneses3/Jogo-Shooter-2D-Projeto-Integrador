#include <stdbool.h>
#include <allegro5/allegro.h> 
#include "config.h"
#include "recursos.h"
#include "cenas.h"
#include "objetos.h"

bool hitbox_em_um_retangulo(int posXp, int posYp, int pW, int pH, int posXret, int posYret, int retH, int retW)
{
    return posXp + pW > posXret &&
        posYp + pH > posYret &&
        posXp < posXret + retW &&
        posYp < posYret + retH;
}

bool mouse_em_retangulo(int mX, int mY, int retX, int retY, int retW, int retH)
{
    return mX > retX &&
        mX < retX + retW &&
        mY > retY &&
        mY < retY + retH;
}

bool mouse_em_circulo(int mX, int mY, int circX, int circY, int raio)
{
    int dx = mX - circX;
    int dy = mY - circY;
    return (dx * dx + dy * dy) <= (raio * raio);
}

void mouse_apertado(int botao, int x, int y)
{

    if (cena_atual == CENA_MENU)
    {
        if (botao == true)
        {
            bool iniciar = mouse_em_retangulo(x, y, TELA_W / 2 - al_get_bitmap_width(botao_2) - 200 / 2, 600, al_get_bitmap_width(botao_2), al_get_bitmap_height(botao_2));
            bool como_jogar = mouse_em_retangulo(x, y, TELA_W / 2 + 200 / 2, 600, al_get_bitmap_width(botao_2), al_get_bitmap_height(botao_2));
            
            if (iniciar)
            {
                al_play_sample(botao_som, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &botao_som_id);
                destruir_cena(CENA_MENU);
                mudar_de_cena(CENA_CUTSCENE1);
            }
            else if (como_jogar)
            {
                al_play_sample(botao_som, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &botao_som_id);
				destruir_cena(CENA_MENU);
				mudar_de_cena(CENA_COMO_JOGAR);
            }
        }
    }

    else if(cena_atual == CENA_COMO_JOGAR)
    {
        if (botao == true)
        {
            float largura_janela = 300.0;
            float altura_janela = 175.0;
            float botao_fechar_x = TELA_W / 2 + largura_janela - 40;
            float botao_fechar_y = TELA_H / 2 - altura_janela + 10;
            float botao_fechar_tam = 30.0;
            bool fechar = mouse_em_circulo(x, y, botao_fechar_x + botao_fechar_tam / 2, botao_fechar_y + botao_fechar_tam / 2, botao_fechar_tam / 2);
            if (fechar)
            {
                al_play_sample(botao_som, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &botao_som_id);
                destruir_cena(CENA_COMO_JOGAR);
                mudar_de_cena(CENA_MENU);
            }
        }
	}

    else if (cena_atual == CENA_CONCLUSAO)
    {
        if(botao == true)
        {
            float largura_botao_continuar = 129.0;
            float altura_botao_continuar = 86.0;
            float botao_continuar_x = TELA_W / 2 - al_get_bitmap_width(botao_conclusao) / 2 + 125.0;
            float botao_continuar_y = TELA_H / 2 - al_get_bitmap_height(botao_conclusao) / 2 + 336.0;

            bool continuar = mouse_em_retangulo(x, y, botao_continuar_x, botao_continuar_y, largura_botao_continuar, altura_botao_continuar);
            
            if(continuar)
            {
                al_play_sample(botao_som, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &botao_som_id);
                destruir_cena(CENA_CONCLUSAO);
                mudar_de_cena(cena_atual_temp + 1);
            }
        }
    }

	else if (cena_atual == CENA_GAMEOVER)
    {
        if (botao == true)
        {
            bool sim = mouse_em_retangulo(x, y, TELA_W / 2 - al_get_bitmap_width(botao_1) - 20, 400, al_get_bitmap_width(botao_1), al_get_bitmap_height(botao_1));
            bool nao = mouse_em_retangulo(x, y, TELA_W / 2 + 40, 400, al_get_bitmap_width(botao_1), al_get_bitmap_height(botao_1));
            
            if (sim)
            {
                al_play_sample(botao_som, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &botao_som_id);
                destruir_cena(CENA_GAMEOVER);
                mudar_de_cena(cena_atual_temp);
            }

            else if (nao)
            {
                al_play_sample(botao_som, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &botao_som_id);
                destruir_cena(CENA_GAMEOVER);
                mudar_de_cena(CENA_MENU);
                printf("Voltando ao menu\n");
            }

        }
    }
}

void checar_colisao_personagem(ObjetoMovel *personagem)
{

    if (cena_atual == CENA_LEVEL_1)
    {
        // PERSONAGEM PRESO NA TELA LEVEL 1
        if (personagem->x < 0)
            personagem->x = 0; 
        
        else if (personagem->x > TELA_W - personagem->w) 
            personagem->x = TELA_W - personagem->w;
        
        
        if (personagem->y - personagem->h / 2 < level1Floor - personagem->h / 2) 
            personagem->y = level1Floor; 
       
        else if (personagem->y > TELA_H - personagem->h)
            personagem->y = TELA_H - personagem->h;
    }

    else if (cena_atual == CENA_LEVEL_2)
    {
        // PERSONAGEM PRESO NA TELA LEVEL 2
        if (personagem->x < level2Left)
            personagem->x = level2Left;
        
        else if (personagem->x > level2Right - personagem->w)
            personagem->x = level2Right - personagem->w;
        
        
        if (personagem->y + personagem->h > level2Floor)
            personagem->y = level2Floor - personagem->h;

        else if (personagem->y < 0)
            personagem->y = 0;

    }

    else if(cena_atual == CENA_LEVEL_3)
    {
        // PERSONAGEM PRESO NA TELA LEVEL 3
        if (personagem->x < 0) 
            personagem->x = 0; 
       
        else if (personagem->x > TELA_W - personagem->w)
            personagem->x = TELA_W - personagem->w;
       
  
        if (personagem->y < level3Floor - personagem->h / 2) 
            personagem->y = level3Floor - personagem->h / 2;

        else if (personagem->y > TELA_H - personagem->h)
                personagem->y = TELA_H - personagem->h;
    }
}

void checar_colisao_personagem_inimigo(ObjetoMovel* personagem, ObjetoMovel* inimigos)
{
    
    // COLISAO INIMIGO COM PERSONAGEM NO LEVEL 1
    if (cena_atual == CENA_LEVEL_1)
    {
        for (i = 0; i < MAX_EXPRESSOES; i++)
        {
            if (inimigos[i].escondido)
                continue;
            if (hitbox_em_um_retangulo(personagem->x + 12, personagem->y + 13, personagem->w - 12, personagem->h - 13, inimigos[i].x, inimigos[i].y, inimigos[i].h, inimigos[i].w)) // deixei menos 12 pra tentar ficar com um hitbox menor
            {
                    printf("Cuidado, -1 Vida!\n");
                    personagem->vida--;
                
                resetar_inimigo(&inimigos[i]);
            }
        }

        // COLISAO INIMIGO COM ATAQUE NO LEVEL 1
        for (i = 0; i < MAX_TIROS; i++)
        {
            if (ataque[i].escondido) //se o ataque nao ta na tela ou nao foi disparado
                continue;//ignora
            for (j = 0; j < MAX_EXPRESSOES; j++)
            {
                if (hitbox_em_um_retangulo(ataque[i].x - ataque[i].w / 2, ataque[i].y - ataque[i].h / 2, ataque[i].w, ataque[i].h, inimigos[j].x, inimigos[j].y, inimigos[j].h, inimigos[j].w))
                {
                    if (inimigos[j].inimigo)//se a expressao for um inimigo
                    {
                        printf("Boa, +10 Pontos!\n");
                        pontos += 10;
                    }
                    else
                    {
                        printf("Expressao errada, -1 Vida!\n");
                        personagem->vida--;
                    }
                    resetar_inimigo(&inimigos[j]);
                    ataque[i].escondido = true;
                }
            }
        }
        
    }
    if(cena_atual == CENA_LEVEL_2)
    {
        if(fileiras[fileira_ativa].escondido == false)
        {
            if (hitbox_em_um_retangulo(personagem->x + 12, personagem->y + 13, personagem->w - 12, personagem->h - 13, fileiras[fileira_ativa].x, fileiras[fileira_ativa].y, fileiras[fileira_ativa].h, fileiras[fileira_ativa].w)) // deixei menos 12 pra tentar ficar com um hitbox menor
            {
                    printf("Cuidado, -1 Vida!\n");
					personagem->vida--;
                
                resetar_inimigo(&fileiras[fileira_ativa]);
            }
		}

        for (i = 0; i < MAX_TIROS; i++)
        {
            if (ataque[i].escondido) //se o ataque nao ta na tela ou nao foi disparado
                continue;//ignora
            if (hitbox_em_um_retangulo(ataque[i].x - ataque[i].w / 2, ataque[i].y - ataque[i].h / 2, ataque[i].w, ataque[i].h, fileiras[fileira_ativa].x + infofileiras[fileira_ativa].posXcerto * tamanho_fileira_certa, fileiras[fileira_ativa].y, tamanho_fileira_certa, tamanho_fileira_certa))
            {
                resetar_inimigo(&fileiras[fileira_ativa]);
                ataque[i].escondido = true;
                pontos += 1;
            }
            else if (hitbox_em_um_retangulo(ataque[i].x - ataque[i].w / 2, ataque[i].y - ataque[i].h / 2, ataque[i].w, ataque[i].h, fileiras[fileira_ativa].x, fileiras[fileira_ativa].y, fileiras[fileira_ativa].h, fileiras[fileira_ativa].w))
            {
                printf("Errou o animal, -1 Vida!\n");
                personagem->vida--;
                resetar_inimigo(&fileiras[fileira_ativa]);
                ataque[i].escondido = true;
            }
        }
    }
}