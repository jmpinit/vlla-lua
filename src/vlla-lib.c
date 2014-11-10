#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "vlla.h"

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

uint8_t r = 255;
uint8_t g = 255;
uint8_t b = 255;

uint32_t rgb(uint8_t r, uint8_t g, uint8_t b) {
    return (r << 16) | (g << 8) | b;
}

// LIBRARY SOURCE

int vlla_lib_palette(lua_State *L) {
    if( lua_type(L, 1) == LUA_TNUMBER &&
        lua_type(L, 2) == LUA_TNUMBER &&
        lua_type(L, 3) == LUA_TNUMBER) {

        // == get args ==
        int rawr = (int)lua_tointeger(L, 1);
        int rawg = (int)lua_tointeger(L, 2);
        int rawb = (int)lua_tointeger(L, 3);

        if(rawr >= 0 && rawr <= 255)
            r = rawr;
        if(rawg >= 0 && rawg <= 255)
            g = rawg;
        if(rawb >= 0 && rawb <= 255)
            b = rawb;
    } else {
        return luaL_error(L, "%s: arguments should be r, g, and b integers.", __func__);
    }

    return 0;
}

int vlla_lib_point(lua_State *L) {
    if( lua_type(L, 1) == LUA_TNUMBER &&
        lua_type(L, 2) == LUA_TNUMBER) {

        // == get args ==
        int px = (int)lua_tointeger(L, 1);
        int py = (int)lua_tointeger(L, 2);

        // == execute ==
        VLLA* vlla = get_vlla();
        if(px >= 0 && py >= 0 && px < VLLA_WIDTH && py < VLLA_HEIGHT) {
            vlla->pixels[py*VLLA_WIDTH+px] = rgb(r, g, b);
        }
    } else {
        return luaL_error(L, "%s: argument should be x and y integers.", __func__);
    }

    return 0;
}

int vlla_lib_refresh(lua_State *L) {
    vlla_update(get_vlla());
    return 0;
}

// LIBRARY INITIALIZATION

static const luaL_reg vlla_lib[] = {
    { "palette",   vlla_lib_palette },
    { "point",     vlla_lib_point },
    { "refresh",   vlla_lib_refresh },
    { NULL,             NULL }
};

int luaopen_vlla_lib(lua_State *L) {
    luaL_openlib(L, "vlla", vlla_lib, 0);
    return 1;
}

void openlualibs(lua_State *l) {
    static const luaL_reg lualibs[] =
    {
        { "base",       luaopen_base },
        { "math",       luaopen_math },
        { "vlla",	luaopen_vlla_lib },
        { NULL,         NULL }
    };

    const luaL_reg *lib;

    for(lib = lualibs; lib->func != NULL; lib++) {
        lib->func(l);
        lua_settop(l, 0);
    }
}
