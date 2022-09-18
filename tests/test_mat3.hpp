/*
 * Unit tests for mat3 class
 * Using custom eztest framework, see eztest_macros.h for implementation detail
 */

TEST_START(test_rotation)

    mat3 m = mat3::rot_y(radians(90));
    vec3 v = vec3(1.0f, 0.0f, 0.0f);
    vec3 result = m * v;
    print_vec3(result);
    CHECK_TRUE(result == vec3(0.0f, 0.0f, -1.0f), "90 degree rotation failed")

TEST_END(test_rotation)