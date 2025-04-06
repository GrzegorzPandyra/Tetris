#ifndef ENGINE_H
#define ENGINE_H

#include "global.h"

#define ENGINE_GAMEFIELD_WIDTH  (GLOBAL_MAIN_WIN_WIDTH -2*GLOBAL_MAIN_WIN_BORDER+1)
#define ENGINE_GAMEFIELD_HEIGHT (GLOBAL_MAIN_WIN_HEIGHT-2*GLOBAL_MAIN_WIN_BORDER)

void engine_init(void);
void engine_run(void);

#endif
