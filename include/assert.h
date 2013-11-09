#ifndef DEBUG_H_
#define DEBUG_H_

#ifdef DEBUG

#include <gb/drawing.h>
#include <stdlib.h>

#define NOT_REACHED ASSERT(FALSE)

#define ASSERT(cond) \
    if (!cond) { \
        gprintf("%s:%d: ERROR" , __FILE__, __LINE__); \
        exit(-1); \
    }

#define ASSERT_MSG(cond, msg) \
    if (!cond) { \
        gprintf("%s:%d: %s" , __FILE__, __LINE__, msg); \
        exit(-1); \
    }

#else  // ifdef DEBUG

#define NOT_REACHED
#define ASSERT(cond)
#define ASSERT_MSG(cond, msg)

#endif // ifdef DEBUG

#endif  // DEBUG_H_
