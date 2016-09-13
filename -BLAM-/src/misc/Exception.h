/*
 *  Exception.h
 *  -BLAM-
 *
 *  Created by David Riley on 10/25/09.
 *  Copyright 2009 Insanely Great Software. All rights reserved.
 *
 */

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <stdlib.h>
#include <stdio.h>

#include <string.h>

#define EXCEPTION_MAX_WHY 4096

#define RAISE_EXCEPTION(e, ...)\
{ \
char why_str[EXCEPTION_MAX_WHY]; \
snprintf(why_str, EXCEPTION_MAX_WHY, ## __VA_ARGS__); \
throw e(why_str, __FILE__, __LINE__); \
}

#define ASSERT_EXCEPTION(cond, e, ...)\
if(!(cond)) RAISE_EXCEPTION(e, ## __VA_ARGS__)

#define DECLARE_EXCEPTION(name) \
class name : public Exception \
{ \
public: \
    name(const char *why, const char *file, unsigned int line) \
    : Exception(why, file, line) \
    { \
         type = #name; \
    } \
};


class Exception
{
public:
    Exception(const char *why, const char *file, unsigned int line)
    : type("Exception"), file(file), line(line)
    {
        char *whyStr = new char [strlen(why)];
        strcpy(whyStr, why);
        this->why = whyStr;
    }
    
    virtual ~Exception(void)
    {
        delete [] why;
    }
    
    const char *type;
    const char *why;
    const char *file;
    const unsigned int line;
};

DECLARE_EXCEPTION(FileException);
DECLARE_EXCEPTION(UnknownTypeException);
DECLARE_EXCEPTION(GLException);
DECLARE_EXCEPTION(LuaException);

#endif // EXCEPTION_H
