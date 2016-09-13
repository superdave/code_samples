/*
 *  lua_bridge.cpp
 *  -BLAM-
 *
 *  Created by David Riley on 10/24/09.
 *  Copyright 2009 Insanely Great Software. All rights reserved.
 *
 */

#include "lua_bridge.h"

void * check_type(lua_State *L, int index, const char *name)
{
	// First, make sure it's a userdata.
	luaL_checktype(L, index, LUA_TUSERDATA);
	
	// Next, make sure it has the right metatable (indicating that it's the
	// right type).
	lua_getmetatable(L, index);
	if(!lua_equal(L, lua_upvalueindex(1), -1))
		luaL_typerror(L, index, name);
	
	// Pop the metatable off the stack.
	lua_pop(L, 1);
	
	// Return the Sprite pointer.
	return (void *)lua_touserdata(L, index);
}


int lua_bridge_export_lib(lua_State      *L,
                          const char     *libName,
                          const luaL_reg *methods,
                          const luaL_reg *metas,
                          const LuaBridgeItem *upvalues,
                          const char     *desc)
{
    lua_getfield(L, LUA_GLOBALSINDEX, "print");
	lua_pushfstring(L,
					"Loading library \"%s\"...",
					libName);
    lua_call(L, 1, 0);
	
	// Load up the name.
	//lua_pushstring(L, libName);
	
	// Create tables for the metatable and the methods.
	lua_newtable(L);
	int methods_table = lua_gettop(L);
	lua_newtable(L);
	int meta_table = lua_gettop(L);
	
	// Create the index metamethod so our objects can be indexed by method name.
	// We have to do this in code instead of in the table of metamethods because
	// the index is actually a table, not a function.
	lua_pushstring(L, "__index");
	lua_pushvalue(L, methods_table);
	lua_settable(L, meta_table);
	lua_pushstring(L, "__metatable");
	lua_pushvalue(L, methods_table);
	lua_settable(L, meta_table);
	
	lua_pushvalue(L, meta_table);
	lua_setmetatable(L, methods_table);
	
	// Fill in the real metatable with the metamethods from our table here.  No
	// name so that it gets put on the stack, and no upvalues.
	luaL_openlib(L, NULL, metas, 0);
	
    int num_upvalues = 1;
    // Go through the upvalues and drop any items passed in.
    if(upvalues)
    {
        while(upvalues->t != LUA_BRIDGE_END)
        {
            switch(upvalues->t)
            {
                case LUA_BRIDGE_NUMBER:
                    lua_pushnumber(L, upvalues->d.number);
                    break;
                case LUA_BRIDGE_INTEGER:
                    lua_pushinteger(L, upvalues->d.integer);
                    break;
                case LUA_BRIDGE_STRING:
                    lua_pushstring(L, upvalues->d.string);
                    break;
                case LUA_BRIDGE_USERDATA:
                    lua_pushlightuserdata(L, upvalues->d.userdata);
                    break;
            }
            
            num_upvalues++;
            upvalues++;
        }
    }
            
	
    // Fill in the methods.  No name still, so we use the stack, but specify one
	// upvalue (which will be the metatable because it's at the top of the
	// stack).
	luaL_openlib(L, NULL, methods, num_upvalues);
	
	// Store the actual table in the global table.
	lua_setglobal(L, libName);
		
	// Print out any description string we might have.
	if(desc)
    {
        lua_getfield(L, LUA_GLOBALSINDEX, "print");
        lua_pushfstring(L, desc);
        lua_call(L, 1, 0);
	}
    
	return 0;
}    
    
