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

#define ENGINE_TICK_NS 1000*1000*999 /* 1s */
/****************************************************
 * Typedefs
 ****************************************************/

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
    memset(ecb.ctx.gamefield, ' ',  sizeof(char)*ENGINE_GAMEFIELD_WIDTH*ENGINE_GAMEFIELD_HEIGHT);
    for(int i=0; i<ENGINE_GAMEFIELD_HEIGHT; i++){
        ecb.ctx.gamefield[i][ENGINE_GAMEFIELD_WIDTH-1] = '\0';
    }
    pthread_mutex_unlock(&ecb.ctx.gamefield_mtx);
    srand(time(NULL));
    ecb.ctx.current_brick = brick_get_new();
    ui_set_gamefield(ecb.ctx.gamefield);
    //keymap_set_current_brick(&ecb.ctx.current_brick);
    ecb.init_complete = true;
}

 void engine_run(void)
{
    brick_move(&ecb.ctx, 1, 0);

    struct timespec ts = {0, ENGINE_TICK_NS};
    nanosleep(&ts, NULL);
}

EngineContext* engine_get_context(void)
{
    return &ecb.ctx;
}

/****************************************************
 * Private functions
 ****************************************************/
