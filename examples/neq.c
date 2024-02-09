#include "../ctest.h"

int main() {
    BEGIN_TESTING("neq.c");

    TEST("Not equal macros work") {
        ASSERT_NOT_EQ(1, 2);
        ASSERT_STR_NOT_EQ("a", "b");
    }

    TEST("Not equal macros fail when given equal (expect failure)") {
        ASSERT_NOT_EQ(1, 1);
        ASSERT_STR_NOT_EQ("a", "a");
    }

    END_TESTING();
}