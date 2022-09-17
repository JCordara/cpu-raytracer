/*
 * Unit tests for common math class
 * Using custom eztest framework, see eztest_macros.h for implementation detail
 */

TEST_START(test_sqrt)

    float result;

    result = sqrt(4.0f);
    CHECK_EQ(result, 2.0f, "Square root incorrect (case: 4.0)")

    result = sqrt(-1.0f);
    CHECK_EQ(result, NaN, "Square root incorrect (case: -1.0)")

TEST_END(test_sqrt)