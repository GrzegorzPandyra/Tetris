#ifndef BRICK_DEF_H
#define BRICK_DEF_H

#include "global.h"

/****************************************************
 * Typedefs
 ****************************************************/
typedef enum BrickType
{
    BT_LONG = 0,
    BT_SQUARE,
    BT_SYMETRICAL,
    BT_S1,
    BT_S2,
    BT_L1,
    BT_L2,
    BT_COUNT
} BrickType;

typedef struct Point
{
    int x;
    int y;
} Point;

typedef struct Brick
{
    int x;
    int y;
    int rotation;
    Point collision_blocks[GLOBAL_COLLISION_BLOCK_NUM];
    BrickType type;
} Brick;

/****************************************************
 * API
 ****************************************************/
#endif
