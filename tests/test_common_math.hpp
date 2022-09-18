/*
 * Unit tests for common math class
 * Using custom eztest framework, see eztest_macros.h for implementation detail
 */

TEST_START(test_sin)

    CHECK_EQ_EPS(sin(radians(30)),    0.5f,      "Quadrant 1 incorrect")
    CHECK_EQ_EPS(sin(radians(104)),   0.970295f, "Quadrant 2 incorrect")
    CHECK_EQ_EPS(sin(radians(255)),  -0.965925f, "Quadrant 3 incorrect")
    CHECK_EQ_EPS(sin(radians(300)),  -0.866025f, "Quadrant 4 incorrect")
    CHECK_EQ_EPS(sin(radians(390)),   0.5f,      "Quadrant 1 incorrect - above 360")
    CHECK_EQ_EPS(sin(radians(824)),   0.970295f, "Quadrant 2 incorrect - way above 360")
    CHECK_EQ_EPS(sin(radians(-825)), -0.965926f, "Quadrant 3 incorrect - way below 0")
    CHECK_EQ_EPS(sin(radians(-60)),  -0.866025f, "Quadrant 4 incorrect - below 0")

TEST_END(test_sin)

TEST_START(test_cos)

    CHECK_EQ_EPS(cos(radians(30)),    0.866025f, "Quadrant 1 incorrect")
    CHECK_EQ_EPS(cos(radians(104)),  -0.241922f, "Quadrant 2 incorrect")
    CHECK_EQ_EPS(cos(radians(255)),  -0.258819f, "Quadrant 3 incorrect")
    CHECK_EQ_EPS(cos(radians(300)),   0.5f,      "Quadrant 4 incorrect")
    CHECK_EQ_EPS(cos(radians(390)),   0.866025f, "Quadrant 1 incorrect - above 360")
    CHECK_EQ_EPS(cos(radians(824)),  -0.241922f, "Quadrant 2 incorrect - way above 360")
    CHECK_EQ_EPS(cos(radians(-825)), -0.258818f, "Quadrant 3 incorrect - way below 0")
    CHECK_EQ_EPS(cos(radians(-60)),   0.5f,      "Quadrant 4 incorrect - below 0")

TEST_END(test_cos)

TEST_START(test_sqrt)

    CHECK_EQ_EPS(sqrt(4.0f), 2.0f, "Square root incorrect (case: 4.0)")
    CHECK_EQ_EPS(sqrt(76851123.861123f), 8766.477277f, "Square root incorrect (case: 76851123.861123)")
    CHECK_EQ_EPS(sqrt(-1.0f), NaN, "Square root incorrect (case: -1.0)")

TEST_END(test_sqrt)