#include <stdio.h>
#include <string.h>
#include "rw.h"
#include "log.h"

#define RW_SAVE_NAME "save"

/****************************************************
 * API
 ****************************************************/
void rw_save(EngineContext* ectx, GameContext* gctx)
{
    if((ectx == NULL) || (gctx == NULL)) return;

    stdlog("Saving...");
    FILE* file = fopen(RW_SAVE_NAME, "w");
    int saved_bytes = 0;

    char ectx_buff[sizeof(EngineContext)];
    memcpy((void*)ectx_buff, (const void*)ectx, sizeof(EngineContext));
    saved_bytes += fwrite(ectx_buff, 1, (int)sizeof(EngineContext), file);

    char gctx_buff[sizeof(GameContext)] = {0};
    memcpy((void*)gctx_buff, (const void*)gctx, sizeof(GameContext));
    saved_bytes += fwrite(gctx_buff, 1, (int)sizeof(GameContext), file);
    fclose(file);

    if(saved_bytes != ((int)sizeof(GameContext) + (int)sizeof(EngineContext))) stdlog("Save corrupted!");
    else stdlog("Save succesful!");
    
}

void rw_load(EngineContext* ectx, GameContext* gctx)
{
    if((ectx == NULL) || (gctx == NULL)) return;

    stdlog("Loading...");
    
    FILE* file = fopen(RW_SAVE_NAME, "r");
    if(file == NULL)
    {
        stdlog("Load failed!");
        return;
    }
    fread(ectx, 1, sizeof(EngineContext), file);
    fread(gctx, 1, sizeof(GameContext), file);
    fclose(file);

    stdlog("Load succesful!");
}

