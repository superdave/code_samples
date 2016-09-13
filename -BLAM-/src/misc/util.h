/*
 *  util.h
 *  -BLAM-
 *
 *  Created by David Riley on 10/28/09.
 *  Copyright 2009 Insanely Great Software. All rights reserved.
 *
 */

#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>

#include "timing.h"

// Debug printf.  Appends a debug message.
#ifdef DEBUG
#define dprintf(...) fprintf(stderr, "***DEBUG " __VA_ARGS__)
#else
#define dprintf(...)
#endif

// A debug printf for when we're being verbose.
#ifdef VERBOSE
#define vdprintf(...) dprintf(__VA_ARGS__)
#else
#define vdprintf(...)
#endif

// An array-counting macro for static arrays.
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))



#endif // UTIL_H
