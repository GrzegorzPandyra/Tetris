#include <ncurses.h>
#include <string.h>
#include "ui.h"
#include "global.h"
#include "brick.h"
#include "log.h"

#define WIN_MAIN_X 10
#define WIN_MAIN_Y 10
#define WIN_MAIN_WIDTH  GLOBAL_MAIN_WIN_WIDTH
#define WIN_MAIN_HEIGHT GLOBAL_MAIN_WIN_HEIGHT

#define WIN_SCORE_X     (WIN_MAIN_X+WIN_MAIN_WIDTH+2)
#define WIN_SCORE_Y      WIN_MAIN_Y
#define WIN_SCORE_WIDTH  14
#define WIN_SCORE_HEIGHT 3

#define WIN_NEXT_X      WIN_SCORE_X
#define WIN_NEXT_Y     (WIN_SCORE_Y+WIN_SCORE_HEIGHT)
#define WIN_NEXT_WIDTH  WIN_SCORE_WIDTH
#define WIN_NEXT_WIDTH_NO_BORDER  (WIN_SCORE_WIDTH-2)
#define WIN_NEXT_HEIGHT 5
#define WIN_NEXT_BRICK_ROWS 2
#define WIN_NEXT_BRICK_OFFSET_X (WIN_NEXT_WIDTH_NO_BORDER/WIN_NEXT_BRICK_ROWS-2)
#define WIN_NEXT_BRICK_OFFSET_Y 2

#define WIN_MENU_X      WIN_NEXT_X
#define WIN_MENU_Y     (WIN_NEXT_Y+WIN_NEXT_HEIGHT)
#define WIN_MENU_WIDTH  WIN_SCORE_WIDTH
#define WIN_MENU_HEIGHT 7

#define WIN_LEVEL_X      WIN_MAIN_X
#define WIN_LEVEL_Y     (WIN_MAIN_Y-3)
#define WIN_LEVEL_WIDTH  WIN_MAIN_WIDTH
#define WIN_LEVEL_HEIGHT 3

#define NULLCHAR_INDEX 1

#define NUM_ELEM(x) (sizeof(x)/sizeof(x[0]))

/****************************************************
 * Typedefs
 ****************************************************/
typedef void (*VoidCbk)(void);
typedef enum 
{
    WIN_ID_MAIN,
    WIN_ID_SCORE,
    WIN_ID_NEXT,
    WIN_ID_MENU,
    WIN_ID_LEVEL
} WindowId;
typedef struct 
{
    WindowId id;
    WINDOW* win;
    uint8_t x;
    uint8_t y;
    uint8_t width;
    uint8_t height;
    VoidCbk handler;
} Window;

/****************************************************
 * Function declarations
 ****************************************************/
static void print_all(void);
static void create_all_windows(void);
static void print_main_window(void);
static void print_score_window(void);
static void print_next_window(void);
static void print_menu_window(void);
static void print_level_window(void);

/****************************************************
 * Local variables
 ****************************************************/
static Window win[] = 
{
    {WIN_ID_MAIN,  NULL, WIN_MAIN_X,  WIN_MAIN_Y,  WIN_MAIN_WIDTH,  WIN_MAIN_HEIGHT,  print_main_window},
    {WIN_ID_SCORE, NULL, WIN_SCORE_X, WIN_SCORE_Y, WIN_SCORE_WIDTH, WIN_SCORE_HEIGHT, print_score_window},
    {WIN_ID_NEXT,  NULL, WIN_NEXT_X,  WIN_NEXT_Y,  WIN_NEXT_WIDTH,  WIN_NEXT_HEIGHT,  print_next_window},
    {WIN_ID_MENU,  NULL, WIN_MENU_X,  WIN_MENU_Y,  WIN_MENU_WIDTH,  WIN_MENU_HEIGHT,  print_menu_window},
    {WIN_ID_LEVEL, NULL, WIN_LEVEL_X, WIN_LEVEL_Y, WIN_LEVEL_WIDTH, WIN_LEVEL_HEIGHT, print_level_window}
};
static char (*gamefield)[ENGINE_GAMEFIELD_WIDTH+ENGINE_GAMEFIELD_NULLCHAR_INDEX] = NULL;

/****************************************************
 * API
 ****************************************************/
void ui_init(void)
{
    initscr();
    noecho();
    nodelay(stdscr, TRUE);
    scrollok(stdscr, TRUE);
    create_all_windows();
}

void ui_run(void)
{
    print_all();
}

void ui_set_gamefield(void* addr)
{
    gamefield = addr;
}

/****************************************************
 * Private functions
 ****************************************************/
static void create_all_windows(void)
{
    for(int i=0; i<NUM_ELEM(win); ++i)
    {
        win[i].win = newwin(win[i].height, win[i].width, win[i].y, win[i].x);
    }
}

static void print_all(void)
{
    /* Print gamefield */
    for(int i=0; i<(WIN_MAIN_HEIGHT-2); i++)
    {
        if(gamefield != NULL)
            mvwprintw(win[WIN_ID_MAIN].win, i+1, 1, "%s", gamefield[i]);
        else
            stdlog("gamefield is NULL");
    }

    /* Print windows */
    for(int i=0; i<NUM_ELEM(win); ++i)
    {
        if(win[i].handler != NULL)
        {
            win[i].handler();
            wrefresh(win[i].win);
        }
    }
}

static void print_main_window(void)
{
    box(win[WIN_ID_MAIN].win, 0, 0);
}

static void print_score_window(void)
{
    int score = engine_get_game_context()->score;
    box(win[WIN_ID_SCORE].win, 0, 0);
    mvwprintw(win[WIN_ID_SCORE].win, 0, 4, "Score");
    mvwprintw(win[WIN_ID_SCORE].win, 1, 2, "%d", score);
}

static void print_next_window(void)
{
    /* Setup window */
    box(win[WIN_ID_NEXT].win, 0, 0);
    mvwprintw(win[WIN_ID_NEXT].win, 0, 2, "Next brick");

    /* Prep buffer */
    char buff[WIN_NEXT_BRICK_ROWS][WIN_NEXT_WIDTH_NO_BORDER+NULLCHAR_INDEX] = {0};
    memset(buff, ' ', sizeof(buff));
    buff[0][WIN_NEXT_WIDTH_NO_BORDER] = '\0';
    buff[1][WIN_NEXT_WIDTH_NO_BORDER] = '\0';

    /* Get collision data */
    EngineContext* ctx = engine_get_engine_context();
    const Point* ptr = brick_get_collision_data(ctx->next_brick.type);

    /* Set buffer */
    for(int i=0; i<GLOBAL_COLLISION_BLOCK_NUM; i++)
    {
        buff[ptr->y][ptr->x+WIN_NEXT_BRICK_OFFSET_X] = GLOBAL_BRICK_CHAR;
        ptr++;
    }

    /* Print buffer */
    mvwprintw(win[WIN_ID_NEXT].win, WIN_NEXT_BRICK_OFFSET_Y,   1, "%s", buff[0]);
    mvwprintw(win[WIN_ID_NEXT].win, WIN_NEXT_BRICK_OFFSET_Y+1, 1, "%s", buff[1]);
}

static void print_menu_window(void)
{
    box(win[WIN_ID_MENU].win, 0, 0);
    mvwprintw(win[WIN_ID_MENU].win, 0, 5, "Menu");

    mvwprintw(win[WIN_ID_MENU].win, 1, 1, "[1] Start");
    mvwprintw(win[WIN_ID_MENU].win, 2, 1, "[P] Pause");
    mvwprintw(win[WIN_ID_MENU].win, 3, 1, "[5] Save");
    mvwprintw(win[WIN_ID_MENU].win, 4, 1, "[9] Load");
    mvwprintw(win[WIN_ID_MENU].win, 5, 1, "[.] Exit");
}

static void print_level_window(void)
{
    box(win[WIN_ID_LEVEL].win, 0, 0);
    mvwprintw(win[WIN_ID_LEVEL].win, 0, 3, "Level");

    GameContext* gctx = engine_get_game_context();

    mvwprintw(win[WIN_ID_LEVEL].win, 1, 2, "== %d ==", gctx->level);
}