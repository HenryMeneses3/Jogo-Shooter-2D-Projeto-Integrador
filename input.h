#ifndef INPUT_H
#define INPUT_H

#include <allegro5/allegro.h>

extern bool estado_tecla[ALLEGRO_KEY_MAX];
extern bool* estado_mouse;
extern int mouse_x, mouse_y;

#endif