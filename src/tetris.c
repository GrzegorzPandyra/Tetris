#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "ui/ui.h"
#include "input/input.h"
#include "global.h"
#include "log.h"
#include "engine.h"
#define THREAD_SLEEP_NS 1000*1000*100 /* 100ms */


static void* run_ui_thread(void* ptr);
static void* run_engine_thread(void* ptr);

int main(int argc, char** argv)
{
    ui_init();
    input_init();
    engine_init();

    pthread_t threads[2];
    pthread_create(&threads[0], NULL, run_ui_thread,     NULL);
    pthread_create(&threads[1], NULL, run_engine_thread, NULL);
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    
    return 0;    
}

void shutdown(void)
{
    stdlog("Shutdown");
    exit(0);
}

static void* run_ui_thread(void* ptr)
{
    struct timespec ts = {0, THREAD_SLEEP_NS};
    while(1)
    {
        ui_run();
        input_run();
        nanosleep(&ts, NULL);
    }
    return NULL;
}

static void* run_engine_thread(void* ptr)
{
    while(1)
    {
        engine_run();
        
    }
    return NULL;
}