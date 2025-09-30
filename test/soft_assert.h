#ifndef SOFT_ASSERT_H
#define SOFT_ASSERT_H

#include <stdio.h>

int soft_assert_failed = 0;

#define soft_assert(expr, fmt, ...) \
    do { \
        if (!(expr)) { \
            fprintf(stderr, \
                "Assertion failed: %s (File %s, line %d)\n" \
                "                " fmt "\n", \
                #expr, __FILE__, __LINE__, ##__VA_ARGS__); \
            soft_assert_failed = 1; \
        } \
    } while (0)

#define soft_assert_equal(a, b, fa, fb) soft_assert((a) == (b), fa  " == " fb, a, b)
#define soft_assert_equal_int(a, b) soft_assert_equal((a), (b), "%d", "%d")

#endif
