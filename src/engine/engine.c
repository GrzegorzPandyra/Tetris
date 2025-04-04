#include <memory.h>
#include <time.h>
#include <stdlib.h>
#include "engine.h"
#include "global.h"
#include "ui.h"

#define BRICK_GRID_SIZE 4
#define ENGINE_TICK_NS 1000*1000*1000 /* 1s */
#define ENGINE_GAMEFIELD_WIDTH  (GLOBAL_MAIN_WIN_WIDTH -2*GLOBAL_MAIN_WIN_BORDER)
#define ENGINE_GAMEFIELD_HEIGHT (GLOBAL_MAIN_WIN_HEIGHT-2*GLOBAL_MAIN_WIN_BORDER)

/****************************************************
 * Typedefs
 ****************************************************/
typedef enum BrickType{
    BT_LONG = 0,
    BT_SQUARE,
    BT_SYMETRICAL,
    BT_S,
    BT_REVERSED_S,
    BT_L,
    BT_REVERSED_L,
    BT_COUNT
} BrickType;

typedef struct Brick {
    int x;
    int y;
    BrickType type;
    int* brick_view;
} Brick;

/****************************************************
 * Local variables
 ****************************************************/
static const int BRICK_VIEWS[BT_COUNT][BRICK_GRID_SIZE] = {
    {8,8,8,8},
    {0,0,12,12},
    {0,0,4,14},
    {0,0,6,12},
    {0,0,12,6},
    {0,0,8,14},
    {0,0,2,14}
};

static struct engine_control_block{
    int score;
    Brick current_brick;
    char gamefield[ENGINE_GAMEFIELD_WIDTH][ENGINE_GAMEFIELD_HEIGHT];
} ecb;

/****************************************************
 * API
 ****************************************************/
void engine_init(void)
{
    ecb.current_brick.x = 1;
    ecb.current_brick.y = 3;
    ecb.current_brick.type = BT_S;
    ecb.current_brick.brick_view = (int*)BRICK_VIEWS[ecb.current_brick.type];
    memset(ecb.gamefield, '\0', sizeof(char)*ENGINE_GAMEFIELD_WIDTH*ENGINE_GAMEFIELD_HEIGHT);
    ui_set_gamefield((char**)ecb.gamefield);
    srand(time(NULL));
    get_new_brick();
}

 void engine_run(void)
{
    struct timespec ts = {0, ENGINE_TICK_NS};
    nanosleep(&ts, NULL);
}

/****************************************************
 * Private functions
 ****************************************************/

 static void get_new_brick(void){
    ecb.current_brick.type = rand()%BT_COUNT;
    ecb.current_brick.brick_view = BRICK_VIEWS[ecb.current_brick.type];
    ecb.current_brick.x = 1+ENGINE_GAMEFIELD_WIDTH/2;
    ecb.current_brick.y = 1;
 }

 static void update_brick(void){
    
    ecb.current_brick.y++;
 }