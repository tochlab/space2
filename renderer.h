#ifndef SPACE2_RENDERER_H
#define SPACE2_RENDERER_H

#include "starsystem.h"

int render_init();
void render_clear();
void system_render(SystemObjects *ss);
void zoom_inc();
void zoom_dec();

#endif //SPACE2_RENDERER_H
