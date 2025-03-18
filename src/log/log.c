#include <ncurses.h>
#include "log.h"

void stdlog(char* str)
{
    wprintw(stdscr, "%s\n", str);
    wrefresh(stdscr);
}