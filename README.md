# ctest

A single-header C testing framework.

## Usage

```c
int main() {
    BEGIN_TESTING("filename.h");

    TEST("describe what the test is testing") {
        RETURNS_INT(func, expected_return_int, (...arguments));
        RETURNS_STR(func, expected_return_str, (...arguments));
        ASSERT(boolean_expression);
        ASSERT_EQ(a, b);
        MODIFIES_STR_ARR(func, expected_str_arr, modified_str_arr, (...arguments));
    }

    END_TESTING();
}
```

## API

### `BEGIN_TESTING(filename)`

-   `filename`: The name of the file being tested.

Prints out a startup message. Must be called before any tests are run.

### `END_TESTING()`

Prints out a summary of the tests run.

### `TEST(description)`

-   `description`: A string describing the test.

Prints out a message indicating the test being run.

### `RETURNS_INT(func, expected_return_int, (...arguments))`

-   `func`: The function being tested. The literal name, not a string.
-   `expected_return_int`: The expected return value of `func`. Must be of type `int`.
-   `(...arguments)`: The arguments to pass to `func`. **Must be enclosed in parentheses**.

Checks that `func` returns `expected_return_int`.

Example:

```c
RETURNS_INT(add, 3, (1, 2));
```

### `RETURNS_STR(func, expected_return_str, (...arguments))`

-   `func`: The function being tested. The literal name, not a string.
-   `expected_return_str`: The expected return value of `func`. Must be a `char*`.
-   `(...arguments)`: The arguments to pass to `func`. **Must be enclosed in parentheses**.

Checks that `func` returns `expected_return_str`.

Example:

```c
RETURNS_STR(concat, "hello world", ("hello", " ", "world"));
```

### `MODIFIES_STR_ARR(func, expected_str_arr, modified_str_arr, (...arguments))`

-   `func`: The function being tested. The literal name, not a string.
-   `expected_str_arr`: The expected value of the `modified_str_arr` variable after `func` is called. Must be a `char**`/`char*[]`.
-   `modified_str_arr`: The variable that `func` modifies. Must be a `char**`.
-   `(...arguments)`: The arguments to pass to `func`. **Must be enclosed in parentheses**.

Checks that `func` modifies `modified_str_arr` to be `expected_str_arr`.

Example:

```c
char* arr[] = {"hello", "world"};
char* expected[] = {"world", "hello"};
MODIFIES_STR_ARR(reverse, expected, arr, (arr));
```

### `MODIFIES_STR(func, expected_str, modified_str, (...arguments))`

-   `func`: The function being tested. The literal name, not a string.
-   `expected_str`: The expected value of the `modified_str` variable after `func` is called. Must be a `char*`.
-   `modified_str`: The variable that `func` modifies. Must be a `char*`.
-   `(...arguments)`: The arguments to pass to `func`. **Must be enclosed in parentheses**.

Checks that `func` modifies `modified_str` to be `expected_str`.

Example:

```c
char* str = "hello";
char* expected = "olleh";
MODIFIES_STR(reverse, expected, str, (str));
```

### `ASSERT(boolean_expression)`

-   `boolean_expression`: A boolean expression.

Checks that `boolean_expression` is true.

Example:

```c
ASSERT(1 == 1);
```

### `ASSERT_EQ(a, b)`

-   `a`: A value.
-   `b`: A value.

Checks that `a` is equal to `b`, using the equality operator (`==`).

Example:

```c
ASSERT_EQ(1, 1);
```

### `ASSERT_STR_EQ(a, b)`

-   `a`: A `char*`.
-   `b`: A `char*`.

Checks that `a` is equal to `b`, using the `strcmp` function.

Example:

```c
ASSERT_STR_EQ("hello", "hello");
```
