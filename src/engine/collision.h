#ifndef COLLISION_H
#define COLLISION_H

#include "engine.h"

typedef enum CollisionType {
    COLLISION_BOTTOM,
    COLLISION_LEFT,
    COLLISION_RIGHT,
    COLLISION_NONE
} CollisionType;

CollisionType collision_check(const EngineContext* ctx, CollisionType type);

#endif
