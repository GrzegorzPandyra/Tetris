#include <memory.h>
#include <time.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include "engine.h"
#include "ui.h"
#include "brick.h"
#include "log.h"

#define ENGINE_TICK_NS 1000*1000*999 /* 1s */
/****************************************************
 * Typedefs
 ****************************************************/
/****************************************************
 * Local variables
 ****************************************************/

static struct engine_control_block{
    int score;
    Brick current_brick;
    char gamefield[ENGINE_GAMEFIELD_HEIGHT][ENGINE_GAMEFIELD_WIDTH];
    pthread_mutex_t gamefield_mtx;
    bool init_complete;
} ecb;

/****************************************************
 * API
 ****************************************************/
void engine_init(void)
{
    ecb.init_complete = false;
    pthread_mutex_lock(&ecb.gamefield_mtx);
    memset(ecb.gamefield, ' ',  sizeof(char)*ENGINE_GAMEFIELD_WIDTH*ENGINE_GAMEFIELD_HEIGHT);
    for(int i=0; i<ENGINE_GAMEFIELD_HEIGHT; i++){
        ecb.gamefield[i][ENGINE_GAMEFIELD_WIDTH-1] = '\0';
    }
    pthread_mutex_unlock(&ecb.gamefield_mtx);
    srand(time(NULL));
    ecb.current_brick = brick_get_new();
    ui_set_gamefield(ecb.gamefield);
    ecb.init_complete = true;
}

 void engine_run(void)
{
    brick_move(&ecb.current_brick, ecb.gamefield, &ecb.gamefield_mtx, 1, 0);
    
    struct timespec ts = {0, ENGINE_TICK_NS};
    nanosleep(&ts, NULL);
}

/****************************************************
 * Private functions
 ****************************************************/
