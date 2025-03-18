#include "keymap.h"
#include "global.h"

#define NUM_ELEM(x) (sizeof(x)/sizeof(x[0]))

typedef struct
{
    char key;
    void (*keyhandler)(void);
} KeyMapping;

static void keyhandler_left(void);
static void keyhandler_right(void);
static void keyhandler_down(void);
static void keyhandler_pause(void);
static void keyhandler_exit(void);

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
    {'.', keyhandler_exit}
};

void keymap_map(char c)
{
    
    for(int i=0; i<NUM_ELEM(mapping); ++i)
    {
        if(mapping[i].key == c) mapping[i].keyhandler();
    }
}
static void keyhandler_left(void){}
static void keyhandler_right(void){}
static void keyhandler_down(void){}
static void keyhandler_pause(void){}
static void keyhandler_exit(void){
    shutdown();
}
