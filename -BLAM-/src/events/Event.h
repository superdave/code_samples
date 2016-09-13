/*
 *  Event.h
 *  -BLAM-
 *
 *  Created by David Riley on 11/10/09.
 *  Copyright 2009 Insanely Great Software. All rights reserved.
 *
 */

#ifndef BLAM_EVENT_H
#define BLAM_EVENT_H

#include <stdint.h>

#include "Object.h"
#include "geometry.h"

enum BLAM_EventType
{
    BLAM_EVENT_NONE,
    BLAM_EVENT_MOUSE_MOVED,
    BLAM_EVENT_MOUSE_DOWN,
    BLAM_EVENT_MOUSE_UP,
    BLAM_EVENT_KEY_DOWN,
    BLAM_EVENT_KEY_UP
};

enum
{
    BLAM_KEY_BS          = 0x008,
    BLAM_KEY_BACKSPACE   = 0x008,
    BLAM_KEY_ESC         = 0x01B,
    BLAM_KEY_ESCAPE      = 0x01B,
    BLAM_KEY_SPACE       = 0x020,
    BLAM_KEY_DEL         = 0x07F,
    BLAM_KEY_DELETE      = 0x07F,
    BLAM_KEY_SPECIAL_FLAG= 0x100,
    BLAM_KEY_LEFT_SHIFT  = 0x100,
    BLAM_KEY_RIGHT_SHIFT = 0x101,
    BLAM_KEY_LEFT_CTRL   = 0x102,
    BLAM_KEY_RIGHT_CTRL  = 0x103,
    BLAM_KEY_LEFT_CMD    = 0x104,
    BLAM_KEY_LEFT_ALT    = 0x104,
    BLAM_KEY_RIGHT_CMD   = 0x105,
    BLAM_KEY_RIGHT_ALT   = 0x105,
    BLAM_KEY_LEFT_OPT    = 0x106,
    BLAM_KEY_RIGHT_OPT   = 0x107,
    BLAM_KEY_LEFT_ARROW  = 0x108,
    BLAM_KEY_RIGHT_ARROW = 0x109,
    BLAM_KEY_DOWN_ARROW  = 0x10A,
    BLAM_KEY_UP_ARROW    = 0x10B,
    BLAM_KEY_PRINT_SCREEN= 0x10C,
    BLAM_KEY_SCROLL_LOCK = 0x10D,
    BLAM_KEY_PAUSE       = 0x10E,
    BLAM_KEY_SYSREQ      = 0x10F,
    BLAM_KEY_BREAK       = 0x110,
    BLAM_KEY_F1          = 0x111,
    BLAM_KEY_F2          = 0x112,
    BLAM_KEY_F3          = 0x113,
    BLAM_KEY_F4          = 0x114,
    BLAM_KEY_F5          = 0x115,
    BLAM_KEY_F6          = 0x116,
    BLAM_KEY_F7          = 0x117,
    BLAM_KEY_F8          = 0x118,
    BLAM_KEY_F9          = 0x119,
    BLAM_KEY_F10         = 0x11A,
    BLAM_KEY_F11         = 0x11B,
    BLAM_KEY_F12         = 0x11C,
    BLAM_KEY_F13         = 0x11D,
    BLAM_KEY_F14         = 0x11E,
    BLAM_KEY_F15         = 0x11F,
    BLAM_KEY_INSERT      = 0x120,
    BLAM_KEY_FWD_DELETE  = 0x121,
    BLAM_KEY_HOME        = 0x122,
    BLAM_KEY_END         = 0x123,
    BLAM_KEY_PGUP        = 0x124,
    BLAM_KEY_PAGE_UP     = 0x124,
    BLAM_KEY_PGDN        = 0x125,
    BLAM_KEY_PAGE_DOWN   = 0x125,
    BLAM_KEY_RESET       = 0x126,
    BLAM_KEY_STOP        = 0x127,
    BLAM_KEY_MENU        = 0x128,
    BLAM_KEY_USER        = 0x129,
    BLAM_KEY_SYSTEM      = 0x12A,
    BLAM_KEY_PRINT       = 0x12B,
    BLAM_KEY_HELP        = 0x12C,
    BLAM_KEY_UNKNOWN
};

const char *describe_key(uint16_t key);

class Event : public Object
{
public:
    Point2D mousePos;
    Point2D mouseDelta;
            
    BLAM_EventType type;
    
    uint16_t key;
    uint16_t button;
    
    Event(BLAM_EventType  type,
          const Point2D  &mousePos,
          const Vector2D &mouseDelta = Point2D(0, 0),
          uint16_t        key = 0,
          uint16_t        button = 0)
    : type(type), mousePos(mousePos), mouseDelta(mouseDelta), key(key), button(button)
    {
    }
};

#endif // EVENT_H
