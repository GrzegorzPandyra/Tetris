#ifndef ENGINE_H
#define ENGINE_H

#include <pthread.h>
#include "global.h"
#include "brick_def.h"

#define ENGINE_GAMEFIELD_NULLCHAR_INDEX 1
#define ENGINE_GAMEFIELD_WIDTH  (GLOBAL_MAIN_WIN_WIDTH -2*GLOBAL_MAIN_WIN_BORDER)
#define ENGINE_GAMEFIELD_HEIGHT (GLOBAL_MAIN_WIN_HEIGHT-2*GLOBAL_MAIN_WIN_BORDER)

typedef enum GameStatus
{
    GS_INIT,
    GS_RUNNING,
    GS_PAUSED,
    GS_GAME_OVER
} GameStatus;

typedef struct EngineContext
{
    Brick current_brick;
    Brick next_brick;
    char gamefield[ENGINE_GAMEFIELD_HEIGHT][ENGINE_GAMEFIELD_WIDTH+ENGINE_GAMEFIELD_NULLCHAR_INDEX];
    pthread_mutex_t gamefield_mtx;
} EngineContext;

typedef struct GameContext
{
    int score;
    int level;
    GameStatus status;
} GameContext;

void engine_init(void);
void engine_restart(void);
void engine_run(void);
EngineContext* engine_get_engine_context(void);
GameContext* engine_get_game_context(void);
void engine_check_full_rows(void);

#endif
