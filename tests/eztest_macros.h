#ifndef EZTEST_MACROS_H
#define EZTEST_MACROS_H

#define TEST_START(name) auto name = []() { \
    bool _eztest_passed = true;             \
    float _eztest_diff = 0;                 \
    float _eztest_eps = 0.0000001;

#define TEST_END(name)          \
    return _eztest_passed;      \
};                              \
eztest::add_test(name, #name);

#define CHECK_EQ(actual, expected, msg)                 \
if ((actual) != (expected)) {                           \
    std::cout << "\n-- " << msg;                        \
    std::cout << " - Actual [" << (actual);             \
    std::cout << "], Expected [" << (expected) << "]";  \
    _eztest_passed = false;                             \
}

#define CHECK_EQ_EPS(actual, expected, msg)                         \
_eztest_diff = (actual) - (expected);                               \
if (_eztest_diff < -_eztest_eps || _eztest_diff > _eztest_eps) {    \
    std::cout << "\n-- " << msg;                                    \
    std::cout << " - Actual [" << (actual);                         \
    std::cout << "], Expected [" << (expected) << "]";              \
    _eztest_passed = false;                                         \
}

#define CHECK_TRUE(expression, msg)                     \
if (!(expression)) {                                      \
    std::cout << "\n-- " << msg;                        \
    std::cout << " - Actual [False], Expected [True]";  \
    _eztest_passed = false;                             \
}

#define CHECK_FALSE(expression, msg)                    \
if (expression) {                                       \
    std::cout << "\n-- " << msg;                        \
    std::cout << " - Actual [True], Expected [False]";  \
    _eztest_passed = false;                             \
}

#endif // EZTEST_MACROS_H
