#include <memory.h>
#include <time.h>
#include <stdlib.h>
#include "global.h"
#include "brick.h"
#include "log.h"

#define KEYMAP_ROTATION_CONST_DEG 90

/****************************************************
 * Typedefs
 ****************************************************/

/****************************************************
 * Local variables
 ****************************************************/

/****************************************************
 * Static function declaration
 ****************************************************/
static void print(EngineContext* ctx, char print_char);
static void print_long(EngineContext* ctx, char print_char);
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



void brick_move(EngineContext* ctx, int mv_y, int mv_x){
    print(ctx, GLOBAL_BRICK_ERASE);
    (ctx->current_brick).x += mv_x;
    (ctx->current_brick).y += mv_y;
    print(ctx, GLOBAL_BRICK_CHAR);
}

void brick_rotate(EngineContext* ctx){
    print(ctx, GLOBAL_BRICK_ERASE);
    (ctx->current_brick).rotation += KEYMAP_ROTATION_CONST_DEG;
    print(ctx, GLOBAL_BRICK_CHAR);
}

/****************************************************
 * Private functions
 ****************************************************/
static void print(EngineContext* ctx, char print_char){
    pthread_mutex_lock(&(ctx->gamefield_mtx));
    switch ((ctx->current_brick).type)
    {
    case BT_LONG:
        print_long(ctx, print_char);
        break;
    
    default:
        break;
    }
    pthread_mutex_unlock(&(ctx->gamefield_mtx));
}

static void print_long(EngineContext* ctx, char print_char){

    Brick* brick = &(ctx->current_brick);
    switch(brick->rotation){
        case 0:
        case 180:
            ctx->gamefield[brick->y][brick->x]   = print_char;
            ctx->gamefield[brick->y][brick->x+1] = print_char;
            ctx->gamefield[brick->y][brick->x+2] = print_char;
            ctx->gamefield[brick->y][brick->x+3] = print_char;
            ctx->gamefield[brick->y][ENGINE_GAMEFIELD_WIDTH-1] = '\0';
            break;
        case 90:
        case 270:
            ctx->gamefield[brick->y][brick->x]   = print_char;
            ctx->gamefield[brick->y+1][brick->x] = print_char;
            ctx->gamefield[brick->y+2][brick->x] = print_char;
            ctx->gamefield[brick->y+3][brick->x] = print_char;
            ctx->gamefield[brick->y][ENGINE_GAMEFIELD_WIDTH-1] = '\0';
            break;
        default:
            break;
    }
}