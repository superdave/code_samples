/*
 *  Events.cpp
 *  -BLAM-
 *
 *  Created by David Riley on 11/3/09.
 *  Copyright 2009 Insanely Great Software. All rights reserved.
 *
 */

#include "Events.h"

#include "util.h"

/* Events()
 *
 * Creates a new Events class.
 *
 * Parameters:
 *    mousePos:    The initial mouse position.
 *    queueLength: The length of the event queue.
 */
Events::Events(const Point2D &mousePos,
               unsigned long  queueLength)
: m_mousePos(mousePos)
{
    // Initialize the event queue.
    m_events = new FIFO(queueLength);
}

/* Events()
 *
 * Cleans up an events class (particularly the FIFO).
 */
Events::~Events(void)
{
    // Free up the queue.
    delete m_events;
}

/* postEvent(evt)
 *
 * Posts an event to the FIFO.
 *
 * Parameters:
 *    evt: The event to post.
 *
 * Returns: True if the event was successfully posted, false otherwise.
 */
bool Events::postEvent(Event *evt)
{
    // Just drop the event into the queue.
    return m_events->push(evt);
}

/* getEvent()
 *
 * Retrieves an event from the FIFO, if there are any.
 *
 * Parameters: None.
 *
 * Returns: A pointer to the Event, or NULL if there was none.
 */
Event * Events::getEvent(void)
{
    // Retrieve the event first.
    Event *evt = (Event *)m_events->pop();
    
    // Did we get one?
    if(evt)
    {
        // If it was a movement, log the position and calculate the delta.
        if(evt->type == BLAM_EVENT_MOUSE_MOVED)
        {
            evt->mouseDelta = evt->mousePos - m_mousePos;
            m_mousePos = evt->mousePos;
        } else {
            // Otherwise, set the mouse position and delta in the event.
            evt->mousePos = m_mousePos;
            evt->mouseDelta = Point2D(0, 0);
        }
    }
 
    // Return whatever we got.
    return evt;
}

/* getLastMousePos()
 *
 * Retrieves the last mouse position specified by an event.
 *
 * Parameters: None.
 *
 * Returns: A Point2D specifying the last mouse position.
 */
Point2D Events::getLastMousePos(void) const
{
    return m_mousePos;
}



#pragma mark -
#pragma mark Lua Interface


/* lua_run_event(L, evt)
 *
 * Runs the specific event in the Lua environment.
 *
 * Parameters:
 *    L:   The lua context.
 *    evt: The event to run.
 *
 * Returns: Nothing.
 */
void lua_run_event(lua_State *L,
                   const Event *evt,
                   double time)
{
    // Start by getting the Lua global events table.
    lua_getglobal(L, "Events");
    
    // Determine which event subtable we want.
    switch(evt->type)
    {
        case BLAM_EVENT_KEY_DOWN:
            lua_pushstring(L, "keyDownEvents");
            break;
        case BLAM_EVENT_KEY_UP:
            lua_pushstring(L, "keyUpEvents");
            break;
            
        case BLAM_EVENT_MOUSE_DOWN:
            lua_pushstring(L, "mouseDownEvents");
            break;
        case BLAM_EVENT_MOUSE_UP:
            lua_pushstring(L, "mouseUpEvents");
            break;
            
        case BLAM_EVENT_MOUSE_MOVED:
            lua_pushstring(L, "mouseMovedEvents");
            break;
            
        default:
            lua_pop(L, 1);
            return;
    }

    // Get the event type table.
    lua_gettable(L, 1);
    
    // Create the event to send.
    lua_newtable(L);
    
    // Create the mouse coordinates.
    lua_pushstring(L, "mousePos");
    lua_newtable(L);
    lua_pushstring(L, "x");
    lua_pushinteger(L, evt->mousePos.x);
    lua_settable(L, -3);
    lua_pushstring(L, "y");
    lua_pushinteger(L, evt->mousePos.y);
    lua_settable(L, -3);
    lua_settable(L, -3);
    
    // Create the mouse delta.
    lua_pushstring(L, "mouseDelta");
    lua_newtable(L);
    lua_pushstring(L, "x");
    lua_pushinteger(L, evt->mouseDelta.x);
    lua_settable(L, -3);
    lua_pushstring(L, "y");
    lua_pushinteger(L, evt->mouseDelta.y);
    lua_settable(L, -3);
    lua_settable(L, -3);
    
    // Deposit the button.
    lua_pushstring(L, "mouseButton");
    lua_pushinteger(L, evt->button);
    lua_settable(L, -3);    
    
    // Create the key.
    lua_pushstring(L, "key");
    lua_pushinteger(L, evt->key);
    lua_settable(L, -3);
    
    // Push the time.
    lua_pushnumber(L, time);
    
    // Call it (for now).
    int err = lua_pcall(L, 2, 0, 0);
    
    if(err)
    {
        dprintf("Lua error: %s\n", lua_tolstring(L, -1, NULL));
    }
}
