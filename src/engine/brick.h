#ifndef BRICK_H
#define BRICK_H

#include <pthread.h>
#include "engine.h"
/****************************************************
 * Typedefs
 ****************************************************/
typedef enum BrickType{
    BT_LONG = 0,
    BT_SQUARE,
    BT_SYMETRICAL,
    BT_S1,
    BT_S2,
    BT_L1,
    BT_L2,
    BT_COUNT
} BrickType;


typedef struct Brick {
    int x;
    int y;
    int rotation;
    BrickType type;
} Brick;

/****************************************************
 * API
 ****************************************************/
Brick brick_get_new(void);
void brick_move(Brick* brick, char gamefield[ENGINE_GAMEFIELD_HEIGHT][ENGINE_GAMEFIELD_WIDTH], pthread_mutex_t* mtx, int mv_y, int mv_x);

#endif
