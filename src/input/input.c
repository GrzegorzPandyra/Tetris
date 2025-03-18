#include <ncurses.h>
#include "input.h"
#include "keymap.h"



void input_init(void)
{
    noecho();
}

void input_run(void)
{
    char c = getch();
    cbreak();
    keymap_map(c);
}

