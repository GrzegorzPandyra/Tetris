#ifndef GLOBAL_H
#define GLOBAL_H

#define GLOBAL_MAIN_WIN_WIDTH   12
#define GLOBAL_MAIN_WIN_HEIGHT  15
#define GLOBAL_MAIN_WIN_BORDER  1

#define GLOBAL_BRICK_CHAR  '#'
#define GLOBAL_BRICK_SETTLED '='
#define GLOBAL_BRICK_ERASE ' '

#define GLOBAL_COLLISION_BLOCK_NUM 4

#define GLOBAL_LEVEL_UP_THRESHOLD 500
#define GLOBAL_SPEED_UP_PER_LEVEL_MS 100*1000*1000

void shutdown(void);

#endif