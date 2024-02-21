#include "../ctest.h"

typedef struct {
    int x;
    int y;
} Point;

int main() {
    BEGIN_TESTING("eq.c");

    TEST("1 is 1") {
        int a = 1;
        int b = 1;
        int c = 2;
        ASSERT_EQ(a, b);
        ASSERT_EQ(a, c);
    }

    TEST("Point equals point") {
        Point p1 = { 1, 2 };
        Point p2 = { 1, 3 };

        ASSERT_EQ(p1.x, p2.x);
        ASSERT_EQ(p1.y, p2.y);
        ASSERT_EQ(&p1, &p2);
    }

    END_TESTING();
}