/*
 *  lua_bridge.h
 *  -BLAM-
 *
 *  Created by David Riley on 10/24/09.
 *  Copyright 2009 Insanely Great Software. All rights reserved.
 *
 */

#ifndef LUA_BRIDGE_H
#define LUA_BRIDGE_H

extern "C" {
    
#include "lua.h"
#include "lualib.h"
#include "lapi.h"
#include "lauxlib.h"

};

#include <new>
    
enum LuaBridgeType
{
    LUA_BRIDGE_NUMBER,
    LUA_BRIDGE_INTEGER,
    LUA_BRIDGE_STRING,
    LUA_BRIDGE_USERDATA,
    LUA_BRIDGE_END
};

typedef struct
{
    LuaBridgeType t;
    
    union __data
    {
        lua_Number   number;
        lua_Integer  integer;
        const char  *string;
        void        *userdata;
        
        __data(lua_Number   n)  : number(n) {}
        __data(lua_Integer  i)  : integer(i) {}
        __data(const char *str) : string(str) {}
        __data(void       *ud)  : userdata(ud) {}
    } d;
} LuaBridgeItem;

#define LUA_BRIDGE_ITEM(type, item) {type, item}
#define LUA_BRIDGE_ITEM_END {LUA_BRIDGE_END, NULL}
    
#define LUA_BRIDGE_FUNC(lib, name) static int lua_##lib##_##name(lua_State *L)
#define LUA_BRIDGE_ENTRY(lib, name) {#name, lua_##lib##_##name}

#define LUA_BRIDGE_EXPORT_LIB(lib, name, methods, metas, ...)\
extern "C" {\
int luaopen_ ## lib ## _ ## name (lua_State *L)\
{\
    return lua_bridge_export_lib(L, #name, methods, metas, ## __VA_ARGS__);\
}\
}

void * check_type(lua_State *L, int index, const char *name);

int lua_bridge_export_lib(lua_State      *L,
                          const char     *libName,
                          const luaL_Reg *methods,
                          const luaL_Reg *metas,
                          const LuaBridgeItem *upvalues = NULL,
                          const char     *desc = NULL);
                           


#endif // LUA_BRIDGE_H
