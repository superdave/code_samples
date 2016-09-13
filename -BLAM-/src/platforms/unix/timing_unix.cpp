/*
 *  timing_unix.cpp
 *  -BLAM-
 *
 *  Created by David Riley on 11/15/09.
 *  Copyright 2009 Insanely Great Software. All rights reserved.
 *
 */

#include <sys/time.h>

#include "timing.h"
#include "util.h"

double get_current_time(void)
{
    struct timeval tv;
    
    int err = gettimeofday(&tv, NULL);
    if(err) printf("WTF?\n");
    
    double curTime = (double)tv.tv_sec;
    curTime += (tv.tv_usec / 1000000.0);
    
    return curTime;
}
