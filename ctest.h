/**
 *     .oooooo.       ooooooooooooo                        .
 *    d8P'  `Y8b      8'   888   `8                      .o8
 *   888                   888      .ooooo.    .oooo.o .o888oo
 *   888                   888     d88' `88b  d88(  "8   888
 *   888                   888     888ooo888  `"Y88b.    888
 *   `88b    ooo           888     888    .o  o.  )88b   888 .
 *    `Y8bood8P'          o888o    `Y8bod8P'  8""888P'   "888"
 *
 *
 *     C Test: A simple, macro-based testing framework for C
 *
 * Created by Nate Levin (@NateLevin1 on GitHub)
 * Last Updated: 2023-01-23
 *
 * Example Usage:
 * int main() {
 *     BEGIN_TESTING("filename.h");
 *
 *     TEST("describe what the test is testing") {
 *         RETURNS_INT(func, expected_return_int, (...arguments));
 *         RETURNS_STR(func, expected_return_str, (...arguments));
 *         ASSERT(boolean_expression);
 *         ASSERT_EQ(a, b);
 *         MODIFIES_STR_ARR(func, expected_str_arr, modified_str_arr, (...arguments));
 *     }
 *
 *     END_TESTING();
 * }
 *
 * NOTE: If your function modifies a string instead of returning a char*,
 *       use MODIFIES_STR instead of RETURNS_STR. For example:
 *       MODIFIES_STR(func, expected_str, modified_str, (...arguments)); // use when func modifies the string, instead of returning char*
 *
*/

#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

static int num_tests = 0;
static int passed = 0;
static int failed = 0;
static int start_time = 0;
static bool cur_test_failed = false;

#define __PASS(...) \
    printf("\033[32m✓\033[0m Passed: "); \
    printf(__VA_ARGS__); \
    printf("\n");

#define __FAIL(...) \
    printf("\033[31m✗ Failed:\033[0m "); \
    printf(__VA_ARGS__); \
    printf("\n"); \
    cur_test_failed = true;

#define BEGIN_TESTING(file) \
    printf("\n \033[36m---\033[0m %s \033[36m---\033[0m\n", file); \
    start_time = clock(); \

#define __HANDLE_TEST_FAILURES() \
    if(cur_test_failed) { \
        failed++; \
        cur_test_failed = false; \
    } else if(num_tests > 0) { \
        passed++; \
    };

#define TEST(description) \
    printf("\n\033[34m-\033[0m %s\n", description); \
    __HANDLE_TEST_FAILURES(); \
    num_tests++;

#define RETURNS_INT(func, expected, arguments) \
    { \
    int result = func arguments; \
    if(result == expected) {\
        __PASS("%s%s = %d", #func, #arguments, result); \
    } else { \
        __FAIL("%s%s should be \033[31m%d\033[0m, but got \033[31m%d\033[0m", #func, #arguments, expected, result); \
    }; \
    }

#define RETURNS_STR(func, expected, arguments) \
    { \
    char* result = func arguments; \
    if(strcmp(result, expected) == 0) {\
        __PASS("%s%s = \"%s\"", #func, #arguments, result); \
    } else { \
        __FAIL("%s%s should be \033[31m\"%s\"\033[0m, but got \033[31m\"%s\"\033[0m", #func, #arguments, expected, result); \
    }; \
    }

#define MODIFIES_STR_ARR(func, expected, modified, arguments) \
    { \
    func arguments; \
    int size = sizeof(modified) / sizeof(*modified); \
    for(int i = 0; i < size; i++) { \
        if(modified[i] == expected[i]) {\
            __PASS("%s%s[%d] = %s", #func, #arguments, i, modified[i]); \
        } else { \
            __FAIL("\033[0m%s%s[%d] should be %s, but got %s", #func, #arguments, i, expected[i], modified[i]); \
        }; \
    } \
    };

#define MODIFIES_STR(func, expected, modified, arguments) \
    { \
    func arguments; \
    if(strcmp(modified, expected) == 0) {\
        __PASS("%s%s = \"%s\"", #func, #arguments, modified); \
    } else { \
        __FAIL("%s%s should be \"%s\", but got \"%s\"\033[0m", #func, #arguments, expected, modified); \
    }; \
    }

#define ASSERT(boolean_expression) \
    { \
    if(boolean_expression) {\
        __PASS("%s", #boolean_expression); \
    } else { \
        __FAIL("%s\033[0m", #boolean_expression); \
    }; \
    }

#define ASSERT_EQ(a, b) \
    { \
    if(a == b) {\
        __PASS("%s == %s", #a, #b); \
    } else { \
        __FAIL("%s != %s\033[0m", #a, #b); \
    }; \
    }

#define ASSERT_STR_EQ(a, b) \
    { \
    if(strcmp(a, b) == 0) {\
        __PASS("%s == %s", #a, #b); \
    } else {\
        __FAIL("%s != %s (\"%s\" != \"%s\")\033[0m", #a, #b, a, b); \
    }; \
    }

#define END_TESTING() \
    __HANDLE_TEST_FAILURES(); \
    printf("\n-----------------------------\n"); \
    printf(" Ran \033[36m%d\033[0m tests (took %ldms)\n", num_tests, clock() - start_time); \
    if(failed > 0) { \
        printf(" \033[32m%d passed\033[0m, \033[31m%d failed\033[0m\n", passed, failed); \
    } else {\
        printf(" \033[32m%d passed\033[0m, %d failed\n", passed, failed); \
    } \
    printf("-----------------------------\n");
