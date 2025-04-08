#include "keymap.h"
#include "global.h"
#include "brick.h"
#include "engine.h"
#include "assert.h"
#include "collision.h"
#include "rw.h"

#define NUM_ELEM(x) (sizeof(x)/sizeof(x[0]))

/****************************************************
 * Typedefs
 ****************************************************/
typedef struct
{
    char key;
    void (*keyhandler)(void);
} KeyMapping;

/****************************************************
 * Private functions declarations
 ****************************************************/
static void keyhandler_left(void);
static void keyhandler_right(void);
static void keyhandler_down(void);
static void keyhandler_pause(void);
static void keyhandler_rotate(void);
static void keyhandler_exit(void);
static void keyhandler_start(void);
static void keyhandler_save(void);
static void keyhandler_load(void);

/****************************************************
 * Private variables
 ****************************************************/
static KeyMapping mapping[] = 
{
    {'a', keyhandler_left},
    {'A', keyhandler_left},
    {'d', keyhandler_right},
    {'D', keyhandler_right},
    {'s', keyhandler_down},
    {'S', keyhandler_down},
    {'p', keyhandler_pause},
    {'P', keyhandler_pause},
    {'r', keyhandler_rotate},
    {'R', keyhandler_rotate},
    {'.', keyhandler_exit},
    {'1', keyhandler_start},
    {'5', keyhandler_save},
    {'9', keyhandler_load}
};

/****************************************************
 * Public functions
 ****************************************************/
void keymap_map(char c)
{
    
    for(int i=0; i<NUM_ELEM(mapping); ++i)
    {
        if(mapping[i].key == c) mapping[i].keyhandler();
    }
}

/****************************************************
 * Private functions
 ****************************************************/
static void keyhandler_left(void)
{
    GameContext* gctx = engine_get_game_context();
    if(gctx->status != GS_RUNNING) return;

    EngineContext* ctx = engine_get_engine_context();
    assert(ctx != NULL);
    CollisionType collisionStatus = collision_check(ctx, COLLISION_LEFT);
    if(collisionStatus != COLLISION_LEFT)
    {
        brick_move(ctx, 0, -1);
    }
}

static void keyhandler_right(void)
{
    GameContext* gctx = engine_get_game_context();
    if(gctx->status != GS_RUNNING) return;

    EngineContext* ctx = engine_get_engine_context();
    assert(ctx != NULL);
    CollisionType collisionStatus = collision_check(ctx, COLLISION_RIGHT);
    if(collisionStatus != COLLISION_RIGHT)
    {
        brick_move(ctx, 0, 1);
    } 
}

static void keyhandler_down(void)
{
    GameContext* gctx = engine_get_game_context();
    if(gctx->status != GS_RUNNING) return;

    EngineContext* ctx = engine_get_engine_context();
    assert(ctx != NULL);
    CollisionType collisionStatus = collision_check(ctx, COLLISION_BOTTOM);
    if(collisionStatus == COLLISION_BOTTOM)
    {
        brick_settle(ctx);
        brick_get_new(ctx);
    } 
    else 
    {
        brick_move(ctx, 1, 0);
    }
    engine_check_full_rows();
}

static void keyhandler_pause(void)
{
    GameContext* gctx = engine_get_game_context();

    if(gctx->status == GS_GAME_OVER) return;

    if(gctx->status != GS_PAUSED) gctx->status = GS_PAUSED;
    else gctx->status = GS_RUNNING;
}

static void keyhandler_rotate(void)
{
    GameContext* gctx = engine_get_game_context();
    if(gctx->status != GS_RUNNING) return;

    EngineContext* ctx = engine_get_engine_context();
    assert(ctx != NULL);
    brick_rotate(ctx);
}

static void keyhandler_exit(void){
    shutdown();
}

static void keyhandler_start(void)
{
    GameContext* ectx = engine_get_game_context();
    if(ectx->status == GS_INIT) ectx->status = GS_RUNNING;
    else engine_restart();
}

static void keyhandler_save(void)
{
    rw_save(engine_get_engine_context(), engine_get_game_context());
}

static void keyhandler_load(void)
{
    rw_load(engine_get_engine_context(), engine_get_game_context());
}
