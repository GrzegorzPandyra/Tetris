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

/****************************************************
 * Local variables
 ****************************************************/

static struct engine_control_block{
    int score;
    EngineContext ctx;
    bool init_complete;
} ecb;

/****************************************************
 * API
 ****************************************************/
void engine_init(void)
{
    ecb.init_complete = false;
    pthread_mutex_lock(&ecb.ctx.gamefield_mtx);
    memset(ecb.ctx.gamefield, ' ',  sizeof(char)*(ENGINE_GAMEFIELD_WIDTH+ENGINE_GAMEFIELD_NULLCHAR_INDEX)*ENGINE_GAMEFIELD_HEIGHT);
    for(int i=0; i<ENGINE_GAMEFIELD_HEIGHT; i++){
        ecb.ctx.gamefield[i][ENGINE_GAMEFIELD_WIDTH] = '\0';
    }
    pthread_mutex_unlock(&ecb.ctx.gamefield_mtx);
    srand(time(NULL));
    brick_get_new(&ecb.ctx);
    ui_set_gamefield(ecb.ctx.gamefield);
    ecb.init_complete = true;
}

 void engine_run(void)
{
    CollisionType collisionStatus = collision_check(&ecb.ctx, COLLISION_BOTTOM);
    if(collisionStatus == COLLISION_BOTTOM)
    {
        brick_settle(&ecb.ctx);
        brick_get_new(&ecb.ctx);
    } 
    else 
    {
        brick_move(&ecb.ctx, 1, 0);
    }
    engine_check_full_rows();

    struct timespec ts = {0, ENGINE_TICK_NS};
    nanosleep(&ts, NULL);
}

EngineContext* engine_get_context(void)
{
    return &ecb.ctx;
}

void engine_check_full_rows(void)
{
    for(int i=ENGINE_GAMEFIELD_HEIGHT; i>0; i--)
    {
        for(int j=0; j<ENGINE_GAMEFIELD_WIDTH; j++)
        {
            if(ecb.ctx.gamefield[i][j] != GLOBAL_BRICK_SETTLED) break;
            if(j == ENGINE_GAMEFIELD_WIDTH-1)
            {
                ecb.score += 100;
                shift_down(i);
            }
        }
    }
}

int engine_get_score(void)
{
    return ecb.score;
}

/****************************************************
 * Private functions
 ****************************************************/

static void shift_down(int row)
{
    stdlog("SHIFT DOWN");
    for(; row>0; row--)
    {
        memcpy(ecb.ctx.gamefield[row], ecb.ctx.gamefield[row-1], sizeof(char)*ENGINE_GAMEFIELD_WIDTH);
    }
}