#include <stdlib.h>
#include <stdint.h>
#include <signal.h>
#include <unistd.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "vlla.h"
#include "vlla-lib.h"

VLLA* vlla;
lua_State* lstate;

uint32_t vlla_time = 0;

void cleanup() {
    lua_close(lstate);
    vlla_close(vlla);
}

void sig_handler(int signo) {
    if(signo == SIGINT || signo == SIGTERM)
        exit(0);
}

VLLA* get_vlla(void) {
    if(vlla == NULL) {
        printf("VLLA hasn't been initialized.");
        exit(1);
    }

    return vlla;
}

int main(int argc, char *argv[]) {
    // parameter validation
    if(argc != 2) {
        printf("usage: %s <lua file>\n", argv[0]);
        exit(1);
    }

    if(access(argv[1], F_OK) < 0) {
        printf("file does not exist.\n");
        exit(1);
    }

    char* script_fn = argv[1];

    atexit(cleanup);

    if(signal(SIGINT, sig_handler) == SIG_ERR) {
        printf("\ncan't catch SIGINT\n");
        exit(1);
    }

    if(signal(SIGTERM, sig_handler) == SIG_ERR) {
        printf("\ncan't catch SIGTERM\n");
        exit(1);
    }

    lstate = lua_open();

    vlla = vlla_init("/dev/ttyACM0", "/dev/ttyACM1");
    for(int i=0; i < VLLA_WIDTH * VLLA_HEIGHT; i++)
        vlla->pixels[i] = 0;

    vlla_update(vlla);

    openlualibs(lstate);

    int s = luaL_loadfile(lstate, script_fn);

    if(s == 0) {
        s = lua_pcall(lstate, 0, LUA_MULTRET, 0);
        if(s) {
            fprintf(stderr, "Lua error: %s\n", lua_tostring(lstate, -1));
            exit(0);
        }
    } else {
        fprintf(stderr, "Lua load error: %s\n", lua_tostring(lstate, -1));
        exit(0);
    }

    return 0;
}

