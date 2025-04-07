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
static const Point COLLISION_BOUNDS[BT_COUNT*GLOBAL_COLLISION_BLOCK_NUM][GLOBAL_COLLISION_BLOCK_NUM] = 
{
    {{0,0}, {1,0 }, {2,0 }, {3,0 }}, /* 0   long */
    {{0,0}, {0,1 }, {0,2 }, {0,3 }}, /* 90  long */
    {{0,0}, {1,0 }, {2,0 }, {3,0 }}, /* 180 long */
    {{0,0}, {0,1 }, {0,2 }, {0,3 }}, /* 270 long */
    {{0,0}, {0,1 }, {1,0 }, {1,1 }}, /* 0   Square */
    {{0,0}, {0,1 }, {1,0 }, {1,1 }}, /* 90  Square */
    {{0,0}, {0,1 }, {1,0 }, {1,1 }}, /* 180 Square */
    {{0,0}, {0,1 }, {1,0 }, {1,1 }}, /* 270 Square */
    {{0,0}, {-1,1}, {0,1 }, {1,1 }}, /* 0   Symetrical */
    {{0,0}, {0,1 }, {0,2 }, {1,1 }}, /* 90  Symetrical */
    {{0,0}, {1,0 }, {2,0 }, {1,1 }}, /* 180 Symetrical */
    {{0,0}, {0,1 }, {0,2 }, {-1,1}}, /* 270 Symetrical */
    {{0,0}, {1,0 }, {-1,1}, {0,1 }}, /* 0   S1 */
    {{0,0}, {0,1 }, {1,1 }, {1,2 }}, /* 90  S1 */
    {{0,0}, {1,0 }, {-1,1}, {0,1 }}, /* 180 S1 */
    {{0,0}, {0,1 }, {1,1 }, {1,2 }}, /* 270 S1 */
    {{0,0}, {1,0 }, {1,1 }, {2,1 }}, /* 0   S2 */
    {{0,0}, {0,1 }, {-1,1}, {-1,2}}, /* 90  S2 */
    {{0,0}, {1,0 }, {1,1 }, {2,1 }}, /* 180 S2 */
    {{0,0}, {0,1 }, {-1,1}, {-1,2}}, /* 270 S2 */
    {{0,0}, {0,1 }, {1,1 }, {2,1 }}, /* 0   L1 */
    {{0,0}, {0,1 }, {0,2 }, {-1,2}}, /* 90  L1 */
    {{0,0}, {1,0 }, {2,0 }, {2,1 }}, /* 180 L1 */
    {{0,0}, {1,0 }, {0,1 }, {0,2 }}, /* 270 L1 */
    {{0,0}, {-2,1}, {-1,1}, {0,1 }}, /* 0   L2 */
    {{0,0}, {1,0 }, {1,1 }, {1,2 }}, /* 90  L2 */
    {{0,0}, {1,0 }, {2,0 }, {0,1 }}, /* 180 L2 */
    {{0,0}, {0,1 }, {0,2 }, {1,2 }}, /* 270 L2 */
};
/****************************************************
 * Static function declaration
 ****************************************************/
static void print(EngineContext* ctx, char print_char);
static void update_collision_bounds(EngineContext* ctx);
/****************************************************
 * API
 ****************************************************/
void brick_get_new(EngineContext* ctx)
{
    ctx->current_brick.type     = ctx->next_brick.type;
    ctx->current_brick.x        = ctx->next_brick.x;
    ctx->current_brick.y        = ctx->next_brick.y;
    ctx->current_brick.rotation = ctx->next_brick.rotation;
    ctx->next_brick.type        = rand()%BT_COUNT;
    ctx->next_brick.x           = GLOBAL_MAIN_WIN_WIDTH/2-2;
    ctx->next_brick.y           = 0;
    ctx->next_brick.rotation    = 0;
    update_collision_bounds(ctx);
}



void brick_move(EngineContext* ctx, int mv_y, int mv_x)
{
    print(ctx, GLOBAL_BRICK_ERASE);
    (ctx->current_brick).x += mv_x;
    (ctx->current_brick).y += mv_y;
    update_collision_bounds(ctx);
    print(ctx, GLOBAL_BRICK_CHAR);
}

void brick_rotate(EngineContext* ctx)
{
    print(ctx, GLOBAL_BRICK_ERASE);
    (ctx->current_brick).rotation += KEYMAP_ROTATION_CONST_DEG;
    (ctx->current_brick).rotation %= 360;
    print(ctx, GLOBAL_BRICK_CHAR);
}

void brick_settle(EngineContext* ctx)
{
    print(ctx, GLOBAL_BRICK_SETTLED);
}

const Point* brick_get_collision_data(int type)
{
    return &COLLISION_BOUNDS[type*GLOBAL_COLLISION_BLOCK_NUM][0];
}

/****************************************************
 * Private functions
 ****************************************************/
static void update_collision_bounds(EngineContext* ctx)
{
    int idx = (int)(ctx->current_brick.type*GLOBAL_COLLISION_BLOCK_NUM) + (ctx->current_brick.rotation / 90);
    const Point* pt = COLLISION_BOUNDS[idx];
    for(int i=0; i<GLOBAL_COLLISION_BLOCK_NUM; i++)
    {
        ctx->current_brick.collision_blocks[i].x = ctx->current_brick.x + pt->x;
        ctx->current_brick.collision_blocks[i].y = ctx->current_brick.y + pt->y;
        pt++;
    }
}

static void print(EngineContext* ctx, char print_char){
    pthread_mutex_lock(&(ctx->gamefield_mtx));

    int idx = (int)(ctx->current_brick.type*GLOBAL_COLLISION_BLOCK_NUM) + (ctx->current_brick.rotation / 90);
    const Point* pt = COLLISION_BOUNDS[idx];
    for(int i=0; i<GLOBAL_COLLISION_BLOCK_NUM; i++)
    {
        ctx->gamefield[ctx->current_brick.y+pt->y][ctx->current_brick.x+pt->x] = print_char;
        pt++;
    }
    
    ctx->gamefield[ctx->current_brick.y][ENGINE_GAMEFIELD_WIDTH] = '\0';
    update_collision_bounds(ctx);
    pthread_mutex_unlock(&(ctx->gamefield_mtx));
}