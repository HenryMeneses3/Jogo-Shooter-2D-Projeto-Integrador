#include "recursos.h"
#include "input.h"

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
            }
            break;

        case ALLEGRO_EVENT_KEY_DOWN:
            estado_tecla[evento.keyboard.keycode] = true;
            // tecla_apertada(evento.keyboard.keycode);
            break;

        case ALLEGRO_EVENT_KEY_UP:
            estado_tecla[evento.keyboard.keycode] = false;
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