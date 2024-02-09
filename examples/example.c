#include "../ctest.h"

int sum(int a, int b);

char* reverse(char* str, char* dest);

int main() {
    BEGIN_TESTING("example.c");

    TEST("sum adds two numbers") {
        RETURNS_INT(sum, 1, (1, 0));
        RETURNS_INT(sum, 5, (2, 3));
        RETURNS_INT(sum, -2, (-6, 4));
    }

    TEST("reverse reverses a string") {
        char dest[6];
        RETURNS_STR(reverse, "olleh", ("hello", dest));
        RETURNS_STR(reverse, "dlrow", ("world", dest));
    }

    TEST("reverse reverses a string (modifier form)") {
        char dest[6];
        MODIFIES_STR(reverse, "olleh", dest, ("hello", dest));
        MODIFIES_STR(reverse, "dlrow", dest, ("world", dest));
    }

    TEST("reverse reverses a string (str_eq form)") {
        char dest[6];
        ASSERT_STR_EQ(reverse("hello", dest), "olleh");
        ASSERT_STR_EQ(reverse("world", dest), "dlrow");
    }

    TEST("1 is 1") {
        ASSERT_EQ(1, 1);
    }

    TEST("false is true") {
        ASSERT_EQ(false, true);
        ASSERT(false);
    }

    END_TESTING();
}

int sum(int a, int b) {
    return a + b;
}

char* reverse(char* str, char* dest) {
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        dest[i] = str[len - i - 1];
    }
    dest[len] = '\0';
    return dest;
}