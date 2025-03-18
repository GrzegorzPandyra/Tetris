#include <pthread.h>
#include <time.h>
#include <stdbool.h>
#include "ui/ui.h"
#include "input/input.h"
#include "global.h"
#include "log.h"
#define THREAD_SLEEP_NS 1000*1000*100


static void* run_ui_thread(void* ptr);
static void* run_input_thread(void* ptr);

static volatile bool go_to_exit = false;

int main(int argc, char** argv)
{
    ui_init();
    input_init();

    pthread_t threads[2];
    // pthread_create(&threads[0], NULL, run_ui_thread,    NULL);
    pthread_create(&threads[1], NULL, run_input_thread, NULL);
    while(!go_to_exit);
    
    return 0;    
}

void shutdown(void)
{
    stdlog("Shutdown");
    go_to_exit = true;
}

static void* run_ui_thread(void* ptr)
{
    struct timespec ts = {0, THREAD_SLEEP_NS};
    while(1)
    {
        ui_run();
        nanosleep(&ts, NULL);
    }
    return NULL;
}

static void* run_input_thread(void* ptr)
{
    struct timespec ts = {0, THREAD_SLEEP_NS};
    while(1)
    {
        input_run();
        nanosleep(&ts, NULL);
    }
    return NULL;
}