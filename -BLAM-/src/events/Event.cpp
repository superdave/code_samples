/*
 *  Event.cpp
 *  -BLAM-
 *
 *  Created by David Riley on 11/11/09.
 *  Copyright 2009 Insanely Great Software. All rights reserved.
 *
 */

#include "Event.h"

#include "util.h"

static const char *ASCIIKeyDescriptions[] =
{
"NUL",
"SOH",
"STX",
"ETX",
"EOT",
"ENQ",
"ACK",
"BEL",
"Backspace",
"Tab",
"Line Feed",
"Vertical Tab",
"Form Feed",
"Enter",
"SO",
"SI",
"DLE",
"DC1",
"DC2",
"DC3",
"DC4",
"NAK",
"SYN",
"ETB",
"CAN",
"EM",
"SUB",
"Escape",
"FS",
"GS",
"RS",
"US",
"Space",
     "!", "\"", "#", "$", "%", "&", "'", "(", ")", "*", "+", "'", "-", ".", "/",
"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", ":", ";", "<", "=", ">", "?",
"@", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O",
"P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "[", "\\", "]", "^", "_",
"`", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o",
"p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "{", "|", "}", "~",
"Delete"
};

static const char *functionKeyDescriptions[] =
{
"Left Shift",
"Right Shift",
"Left Control",
"Right Control",
"Left Command",
"Right Command",
"Left Option/Alt",
"Right Option/Alt",
"Left Arrow",
"Right Arrow",
"Down Arrow",
"Up Arrow",
"Print Screen",
"Scroll Lock",
"Pause",
"SysReq",
"Break",
"F1",
"F2",
"F3",
"F4",
"F5",
"F6",
"F7",
"F8",
"F9",
"F10",
"F11",
"F12",
"F13",
"F14",
"F15",
"Insert",
"Delete",
"Home",
"End",
"Page Up",
"Page Down",
"Reset",
"Stop",
"Menu",
"User",
"System",
"Print",
"Help"
};

const char *describe_key(uint16_t key)
{
    if(key < ARRAY_SIZE(ASCIIKeyDescriptions))
        return ASCIIKeyDescriptions[key];

    if(key >= BLAM_KEY_SPECIAL_FLAG)
    {
        key &= ~BLAM_KEY_SPECIAL_FLAG;
        if(key < ARRAY_SIZE(functionKeyDescriptions))
            return functionKeyDescriptions[key];
    }
    
    return "Unknown";
}

