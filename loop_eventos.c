#include "config.h"
#include "recursos.h"
#include "cenas.h"
#include "objetos.h"
#include "input.h"
#include "colisoes.h"
#include "funcoes_principais.h"

void comecar_loop_de_eventos(void)
{
    ALLEGRO_EVENT evento;
    bool acabou = false;

    int redraws = 0;

    while (!acabou)
    {
        al_wait_for_event(fila_de_evento, &evento);

        switch (evento.type)
        {
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            acabou = true;
            break;

        case ALLEGRO_EVENT_TIMER:
            if (evento.timer.source == timer)
            {
                redraws++;

                if (cena_atual == CENA_CUTSCENE1)
                {
					if (cutscene_quadrante_atual >= 0 && alpha_quadrante[cutscene_quadrante_atual] < 1.0) //fade in
                    {
						if (alpha_quadrante[cutscene_quadrante_atual] >= 1.0) //garante que n passe de 1.0
                            alpha_quadrante[cutscene_quadrante_atual] = 1.0;

						alpha_quadrante[cutscene_quadrante_atual] += (1.0 / FPS) * (1.0 / 2.0); // fade in em 2 segundos
                    }
                    redraws = 1;
                }
            }
			if (evento.timer.source == cutscene_timer) // timer da cutscene 2 segundos
            {
                if (cena_atual == CENA_CUTSCENE1)
                {
					cutscene_quadrante_atual++;// avança para o próximo quadrante
                    al_play_sample(som_cutscene, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &som_cutscene_id);

					if (cutscene_quadrante_atual >= NUM_MAX_QUADRANTES) // se passou do último quadrante, termina a cutscene
                    {
                        al_stop_timer(cutscene_timer);
                        destruir_cena(CENA_CUTSCENE1);
                        mudar_de_cena(CENA_LEVEL_1);
                    }
                }
            }
            break;

        case ALLEGRO_EVENT_KEY_DOWN:
            estado_tecla[evento.keyboard.keycode] = true;
            // tecla_apertada(evento.keyboard.keycode);
            break;

        case ALLEGRO_EVENT_KEY_UP:
            estado_tecla[evento.keyboard.keycode] = false;
            break;

        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            estado_mouse[evento.mouse.button] = true;
            mouse_apertado(evento.mouse.button, evento.mouse.x, evento.mouse.y);
            break;

        case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
            estado_mouse[evento.mouse.button] = false;
            break;

        case ALLEGRO_EVENT_MOUSE_AXES:
            if (evento.mouse.dx != 0 && evento.mouse.dy != 0)
            {
                mouse_x = evento.mouse.x;
                mouse_y = evento.mouse.y;
            }
            break;
        }

        if (redraws > 0 && al_is_event_queue_empty(fila_de_evento))
        {
            redraws = 0;
            desenhar_jogo();
            atualizar_jogo();
        }
    }
}