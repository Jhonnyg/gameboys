#ifndef DEBUG_H_
#define DEBUG_H_

#ifdef DEBUG

#include <gb/drawing.h>
#include <stdlib.h>

#define NOT_REACHED ASSERT_MSG(FALSE, "UNREACHABLE")

#define ASSERT(cond) ASSERT_MSG(cond, "ASSERTION ERROR")

#define ASSERT_MSG(cond, msg) \
    if (!cond) { \
        gprintf("%s:", __FILE__); \
        gprintln(__LINE__, 10, 0); \
        gprintf(": %s", msg); \
        exit(-1); \
    }

#else  // ifdef DEBUG

#define NOT_REACHED
#define ASSERT(cond)
#define ASSERT_MSG(cond, msg)

#endif // ifdef DEBUG

#endif  // DEBUG_H_
