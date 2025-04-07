#ifndef BRICK_H
#define BRICK_H

#include <pthread.h>
#include "brick_def.h"
#include "engine.h"
/****************************************************
 * Typedefs
 ****************************************************/

/****************************************************
 * API
 ****************************************************/
void brick_get_new(EngineContext* ctx);
void brick_move(EngineContext* ctx, int mv_y, int mv_x);
void brick_rotate(EngineContext* ctx);
void brick_settle(EngineContext* ctx);
const Point* brick_get_collision_data(int type);

#endif
