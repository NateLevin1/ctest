#include "../ctest.h"

typedef struct {
    int x;
    int y;
} Point;

char charFunc() {
    return 'a';
}

int intFunc() {
    return 42;
}

long longFunc() {
    return 1234567890L;
}

int main() {
    BEGIN_TESTING("returns.c");

    TEST("Testing charFunc") {
        RETURNS(charFunc, (char)'a', ());
        RETURNS(charFunc, (char)'b', ());
    }

    TEST("Testing intFunc") {
        RETURNS(intFunc, 42, ());
        RETURNS(intFunc, 1, ());
    }

    TEST("Testing longFunc") {
        RETURNS(longFunc, 1234567890L, ());
        RETURNS(longFunc, 1L, ());
    }

    END_TESTING();
}