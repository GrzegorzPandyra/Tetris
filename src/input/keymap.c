#include "keymap.h"
#include "global.h"
#include "brick.h"
#include "engine.h"
#include "assert.h"
#include "collision.h"

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
    {'.', keyhandler_exit}
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
    EngineContext* ctx = engine_get_context();
    assert(ctx != NULL);
    CollisionType collisionStatus = collision_check(ctx, COLLISION_LEFT);
    if(collisionStatus == COLLISION_LEFT)
    {
        
    } 
    else 
    {
        brick_move(ctx, 0, -1);
    }
}

static void keyhandler_right(void)
{
    EngineContext* ctx = engine_get_context();
    assert(ctx != NULL);
    CollisionType collisionStatus = collision_check(ctx, COLLISION_RIGHT);
    if(collisionStatus == COLLISION_RIGHT)
    {

    } 
    else 
    {
        brick_move(ctx, 0, 1);
    }
}

static void keyhandler_down(void)
{
    EngineContext* ctx = engine_get_context();
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
static void keyhandler_pause(void){}
static void keyhandler_rotate(void)
{
    EngineContext* ctx = engine_get_context();
    assert(ctx != NULL);
    brick_rotate(ctx);
}
static void keyhandler_exit(void){
    shutdown();
}
