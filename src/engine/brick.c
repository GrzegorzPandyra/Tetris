#include <memory.h>
#include <time.h>
#include <stdlib.h>
#include "global.h"
#include "brick.h"
#include "log.h"

#define BRICK_GRID_SIZE 4

/****************************************************
 * Typedefs
 ****************************************************/

/****************************************************
 * Local variables
 ****************************************************/

/****************************************************
 * Static function declaration
 ****************************************************/
static void print(const Brick* brick, char gamefield[ENGINE_GAMEFIELD_HEIGHT][ENGINE_GAMEFIELD_WIDTH], pthread_mutex_t* mtx, char print_char);
static void print_long(const Brick* brick, char gamefield[ENGINE_GAMEFIELD_HEIGHT][ENGINE_GAMEFIELD_WIDTH], char print_char);
/****************************************************
 * API
 ****************************************************/
Brick brick_get_new(void){
    Brick result;
    // result.type = rand()%BT_COUNT;
    result.type = BT_LONG;
    result.x = 1+GLOBAL_MAIN_WIN_WIDTH/2-2;
    result.y = 1;
    result.rotation = 0;
    return result;
}



void brick_move(Brick* brick, char gamefield[ENGINE_GAMEFIELD_HEIGHT][ENGINE_GAMEFIELD_WIDTH], pthread_mutex_t* mtx, int mv_y, int mv_x){
    print(brick, gamefield, mtx, GLOBAL_BRICK_ERASE);
    brick->x += mv_x;
    brick->y += mv_y;
    print(brick, gamefield, mtx, GLOBAL_BRICK_CHAR);
}

/****************************************************
 * Private functions
 ****************************************************/
static void print(const Brick* brick, char gamefield[ENGINE_GAMEFIELD_HEIGHT][ENGINE_GAMEFIELD_WIDTH], pthread_mutex_t* mtx, char print_char){
    pthread_mutex_lock(mtx);
    switch (brick->type)
    {
    case BT_LONG:
        print_long(brick, gamefield, print_char);
        break;
    
    default:
        break;
    }
    pthread_mutex_unlock(mtx);
}

static void print_long(const Brick* brick, char gamefield[ENGINE_GAMEFIELD_HEIGHT][ENGINE_GAMEFIELD_WIDTH], char print_char){

    switch(brick->rotation){
        case 0:
        case 180:
            gamefield[brick->y][brick->x]  = print_char;
            gamefield[brick->y][brick->x+1] = print_char;
            gamefield[brick->y][brick->x+2] = print_char;
            gamefield[brick->y][brick->x+3] = print_char;
            gamefield[brick->y][ENGINE_GAMEFIELD_WIDTH-1] = '\0';
            break;
        case 90:
        case 270:
            gamefield[brick->y][brick->x]   = print_char;
            gamefield[brick->y+1][brick->x] = print_char;
            gamefield[brick->y+2][brick->x] = print_char;
            gamefield[brick->y+3][brick->x] = print_char;
            gamefield[brick->y][ENGINE_GAMEFIELD_WIDTH-1] = '\0';
            break;
        default:
            break;
    }
}