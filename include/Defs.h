//
// Copyright 2016 riteme
//

#ifndef RSRL_DEFS_H_
#define RSRL_DEFS_H_

#include <cstdio>
#include <cstdlib>

#ifndef NDEBUG

#define ASSERT(expr, message)          \
    if (!(expr)) {                     \
        fprintf(stderr, message "\n"); \
        abort();                       \
    }

#define ASSERTF(expr, message, ...)                 \
    if (!(expr)) {                                  \
        fprintf(stderr, message "\n", __VA_ARGS__); \
        abort();                                    \
    }

#else

#define ASSERT
#define ASSERTF

#endif  // IFNDEF NDEBUG

namespace rsr {

typedef unsigned char UByte;

}  // namespace rsr

#endif  // RSRL_DEFS_H_
