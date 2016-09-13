/*
 *  Events.h
 *  -BLAM-
 *
 *  Created by David Riley on 11/3/09.
 *  Copyright 2009 Insanely Great Software. All rights reserved.
 *
 */

#ifndef EVENTS_H
#define EVENTS_H

#include "Event.h"

#include "FIFO.h"

#include "lua_bridge.h"

class Events
{
public:
    /* Events()
     *
     * Creates a new Events class.
     *
     * Parameters:
     *    mousePos:    The initial mouse position.
     *    queueLength: The length of the event queue.
     */
    Events(const Point2D &mousePos,
           unsigned long  queueLength);
    
    /* Events()
     *
     * Cleans up an events class (particularly the FIFO).
     */
    ~Events(void);
    
    /* postEvent(evt)
     *
     * Posts an event to the FIFO.
     *
     * Parameters:
     *    evt: The event to post.
     *
     * Returns: True if the event was successfully posted, false otherwise.
     */
    bool postEvent(Event *evt);
    
    /* getEvent()
     *
     * Retrieves an event from the FIFO, if there are any.
     *
     * Parameters: None.
     *
     * Returns: A pointer to the Event, or NULL if there was none.
     */
    Event * getEvent(void);
    
    /* getLastMousePos()
     *
     * Retrieves the last mouse position specified by an event.
     *
     * Parameters: None.
     *
     * Returns: A Point2D specifying the last mouse position.
     */
    Point2D getLastMousePos(void) const;
    
protected:
    // Our pending events.
    FIFO    *m_events;
    
    // The last mouse position.
    Point2D  m_mousePos;
    
};


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
                   double time);

#endif // EVENTS_H
