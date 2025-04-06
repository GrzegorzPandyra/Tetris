#include <stdlib.h>
#include "log.h"
#include "collision.h"
#include <assert.h>
/****************************************************
 * Typedefs
 ****************************************************/

/****************************************************
 * Local variables
 ****************************************************/

/****************************************************
 * Static function declaration
 ****************************************************/
CollisionType check_bottom(const EngineContext* ctx);
CollisionType check_left(const EngineContext* ctx);
CollisionType check_right(const EngineContext* ctx);
/****************************************************
 * API
 ****************************************************/
CollisionType collision_check(const EngineContext* ctx, CollisionType type)
{
    assert(ctx != NULL);
    switch (type)
    {
    case COLLISION_BOTTOM:
        return check_bottom(ctx);
        break;
    case COLLISION_LEFT:
        return check_left(ctx);
        break;
    case COLLISION_RIGHT:
        return check_right(ctx);
        break;
    
    default:
        return COLLISION_NONE;
        break;
    }
}

/****************************************************
 * Private functions
 ****************************************************/
CollisionType check_bottom(const EngineContext* ctx)
{
    assert(ctx != NULL);
    Point p;
    for(int i=0; i<GLOBAL_COLLISION_BLOCK_NUM; i++)
    {
        p.y = ctx->current_brick.collision_blocks[i].y+1;
        p.x = ctx->current_brick.collision_blocks[i].x;

        if(p.y >= ENGINE_GAMEFIELD_HEIGHT)
        {
            stdlog("COLLISION BOTTOM (BTM)");
            return COLLISION_BOTTOM;
        }

        if (ctx->gamefield[p.y][p.x] == GLOBAL_BRICK_SETTLED)
        {
            stdlog("COLLISION BOTTOM (SET)");
            return COLLISION_BOTTOM;
        }
    }
    return COLLISION_NONE;
}

CollisionType check_left(const EngineContext* ctx)
{
    assert(ctx != NULL);
    Point p;
    for(int i=0; i<GLOBAL_COLLISION_BLOCK_NUM; i++)
    {
        p.y = ctx->current_brick.collision_blocks[i].y;
        p.x = ctx->current_brick.collision_blocks[i].x-1;

        if(p.x == 0)
        {
            stdlog("COLLISION LEFT");
            return COLLISION_LEFT;
        }

        if (ctx->gamefield[p.y][p.x] == GLOBAL_BRICK_SETTLED)
        {
            stdlog("COLLISION LEFT");
            return COLLISION_LEFT;
        }
    }
    return COLLISION_NONE;
}

CollisionType check_right(const EngineContext* ctx)
{
    assert(ctx != NULL);
    Point p;
    for(int i=0; i<GLOBAL_COLLISION_BLOCK_NUM; i++)
    {
        p.y = ctx->current_brick.collision_blocks[i].y;
        p.x = ctx->current_brick.collision_blocks[i].x+1;

        if(p.x == ENGINE_GAMEFIELD_WIDTH)
        {
            stdlog("COLLISION RIGHT");
            return COLLISION_RIGHT;
        }

        if (ctx->gamefield[p.y][p.x] == GLOBAL_BRICK_SETTLED)
        {
            stdlog("COLLISION RIGHT");
            return COLLISION_RIGHT;
        }
    }
    return COLLISION_NONE;
}

