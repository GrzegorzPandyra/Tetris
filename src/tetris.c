#include <pthread.h>
#include <time.h>
#include "ui/ui.h"
#define THREAD_SLEEP_NS 1000*1000*100

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

int main(int argc, char** argv)
{
    ui_init();

    pthread_t threads[1];
    pthread_create(&threads[0], NULL, run_ui_thread, NULL);
    while(1);
    return 0;    
}