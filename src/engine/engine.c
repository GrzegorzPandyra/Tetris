#include <memory.h>
#include <time.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include "engine.h"
#include "ui.h"
#include "brick.h"
#include "log.h"
#include "keymap.h"
#include "collision.h"

#define ENGINE_TICK_NS 1000*1000*999 /* 1s */
/****************************************************
 * Typedefs
 ****************************************************/

 /****************************************************
 * Private functions
 ****************************************************/
 static void shift_down(int row);
 static void check_level_up(void);
 static bool check_game_over(EngineContext* ectx);
/****************************************************
 * Local variables
 ****************************************************/

static struct engine_control_block{
    GameContext gctx;
    EngineContext ectx;
} ecb;

/****************************************************
 * API
 ****************************************************/
void engine_init(void)
{
    srand(time(NULL));
    pthread_mutex_lock(&ecb.ectx.gamefield_mtx);
    memset(ecb.ectx.gamefield, ' ',  sizeof(char)*(ENGINE_GAMEFIELD_WIDTH+ENGINE_GAMEFIELD_NULLCHAR_INDEX)*ENGINE_GAMEFIELD_HEIGHT);
    for(int i=0; i<ENGINE_GAMEFIELD_HEIGHT; i++){
        ecb.ectx.gamefield[i][ENGINE_GAMEFIELD_WIDTH] = '\0';
    }
    pthread_mutex_unlock(&ecb.ectx.gamefield_mtx);
    ui_set_gamefield(ecb.ectx.gamefield);

    ecb.gctx.score = 0;
    ecb.gctx.level = 1;
    ecb.gctx.status = GS_INIT;

    brick_get_new(&ecb.ectx);
}

 void engine_run(void)
{
    if(ecb.gctx.status == GS_RUNNING)
    {
        CollisionType collisionStatus = collision_check(&ecb.ectx, COLLISION_BOTTOM);
        if(collisionStatus == COLLISION_BOTTOM)
        {
            brick_settle(&ecb.ectx);
            check_game_over(&ecb.ectx);
            brick_get_new(&ecb.ectx);
        } 
        else 
        {
            brick_move(&ecb.ectx, 1, 0);
        }
        engine_check_full_rows();
    }

    struct timespec ts = {0, ENGINE_TICK_NS-GLOBAL_SPEED_UP_PER_LEVEL_MS*ecb.gctx.level};
    nanosleep(&ts, NULL);
}

void engine_restart(void)
{
    engine_init();
}

EngineContext* engine_get_engine_context(void)
{
    return &ecb.ectx;
}

GameContext* engine_get_game_context(void)
{
    return &ecb.gctx;
}

void engine_check_full_rows(void)
{
    for(int i=ENGINE_GAMEFIELD_HEIGHT; i>0; i--)
    {
        for(int j=0; j<ENGINE_GAMEFIELD_WIDTH; j++)
        {
            if(ecb.ectx.gamefield[i][j] != GLOBAL_BRICK_SETTLED) break;
            if(j == ENGINE_GAMEFIELD_WIDTH-1)
            {
                ecb.gctx.score += 100;
                check_level_up();
                shift_down(i);
            }
        }
    }
}

/****************************************************
 * Private functions
 ****************************************************/

static void shift_down(int row)
{
    stdlog("SHIFT DOWN");
    for(; row>0; row--)
    {
        memcpy(ecb.ectx.gamefield[row], ecb.ectx.gamefield[row-1], sizeof(char)*ENGINE_GAMEFIELD_WIDTH);
    }
}

static void check_level_up(void)
{
    if((ecb.gctx.score%GLOBAL_LEVEL_UP_THRESHOLD) == 0) ecb.gctx.level++;
}

static bool check_game_over(EngineContext* ectx)
{
    if(ectx->current_brick.y  <= 0)
    {
        stdlog("GAME OVER");
        engine_get_game_context()->status = GS_GAME_OVER;
        return true;
    }
    return false;
}