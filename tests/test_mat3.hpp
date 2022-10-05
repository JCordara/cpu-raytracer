/*
 * Unit tests for mat3 class
 * Using custom eztest framework, see eztest_macros.h for implementation detail
 */


TEST_START(test_mat3_elementwise_constructor)

    mat3 m(
        0.0f,  1.0f,  2.0f, 
        4.0f,  5.0f,  6.0f, 
        8.0f,  9.0f,  10.0f
    );

    CHECK_EQ_EPS(m[0][0], 0.0f,  "First element incorrect"  )
    CHECK_EQ_EPS(m[0][1], 1.0f,  "Second element incorrect" )
    CHECK_EQ_EPS(m[0][2], 2.0f,  "Third element incorrect"  )
    CHECK_EQ_EPS(m[1][0], 4.0f,  "Fourth element incorrect" )
    CHECK_EQ_EPS(m[1][1], 5.0f,  "Fifth element incorrect"  )
    CHECK_EQ_EPS(m[1][2], 6.0f,  "Sixth element incorrect"  )
    CHECK_EQ_EPS(m[2][0], 8.0f,  "Seventh element incorrect")
    CHECK_EQ_EPS(m[2][1], 9.0f,  "Eighth element incorrect" )
    CHECK_EQ_EPS(m[2][2], 10.0f, "Nineth element incorrect" )

TEST_END(test_mat3_elementwise_constructor)


TEST_START(test_mat3_equality)

    mat3 m0(
        0.0f,  1.0f,  2.0f,
        4.0f,  5.0f,  6.0f,
        8.0f,  9.0f,  10.0f
    );
    mat3 m1(
        0.0f,  1.0f,  2.0f, 
        4.0f,  5.0f,  6.0f, 
        8.0f,  9.0f,  10.0f
    );
    mat3 m2(
        1.0f,  1.0f,  2.0f,
        3.0f,  5.0f,  5.0f,
        8.0f,  9.5f,  10.0f
    );

    CHECK_TRUE(m0 == m1, "Equality operator returns false on equivalent matrices")
    CHECK_FALSE(m0 == m2, "Equality operator returns true on non-equivalent matrices")
    CHECK_FALSE(m0 != m1, "Inequality operator returns true on equivalent matrices")
    CHECK_TRUE(m0 != m2, "Inequality operator returns false on non-equivalent matrices")

TEST_END(test_mat3_equality)


TEST_START(test_mat3_construction)

    // Used for construction
    vec3 v0 = vec3(0.0f,  1.0f,  2.0f);
    vec3 v1 = vec3(4.0f,  5.0f,  6.0f);
    vec3 v2 = vec3(8.0f,  9.0f,  10.0f);

    mat3 m0;
    mat3 m1(v0);
    mat3 m2(v0, true);
    mat3 m3(vec3(0.0f, 1.0f, 2.0f));
    mat3 m4(vec3(0.0f, 1.0f, 2.0f), true);
    mat3 m5(v0, v1, v2);
    mat3 m6(v0, v1, v2, true);
    mat3 m7(
        0.0f,  1.0f,  2.0f, 
        4.0f,  5.0f,  6.0f, 
        8.0f,  9.0f,  10.0f
    );
    mat3 m8(
        0.0f,  1.0f,  2.0f,
        4.0f,  5.0f,  6.0f,
        8.0f,  9.0f,  10.0f,
        true
    );
    mat3 m9(1.0f);

    mat3 default_expected(
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f
    );
    mat3 single_vec_init_expected(
        0.0f, 1.0f, 2.0f,
        0.0f, 1.0f, 2.0f,
        0.0f, 1.0f, 2.0f
    );
    mat3 single_vec_init_colmajor_expected(
        0.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f,
        2.0f, 2.0f, 2.0f
    );
    mat3 element_specific_expected(
        0.0f,  1.0f,  2.0f,
        4.0f,  5.0f,  6.0f,
        8.0f,  9.0f,  10.0f
    );
    mat3 element_specific_colmajor_expected(
        0.0f, 4.0f, 8.0f,
        1.0f, 5.0f, 9.0f,
        2.0f, 6.0f, 10.0f
    );
    mat3 diagonal_expected(
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    );

    CHECK_TRUE(m0 == default_expected, "Default construction produces incorrect matrix")
    CHECK_TRUE(m1 == single_vec_init_expected, "Single vector construction produces incorrect matrix")
    CHECK_TRUE(m2 == single_vec_init_colmajor_expected, "Single vector column-major construction produces incorrect matrix")
    CHECK_TRUE(m3 == single_vec_init_expected, "Single rvalue vector construction produces incorrect matrix")
    CHECK_TRUE(m4 == single_vec_init_colmajor_expected, "Single rvalue vector column-major construction produces incorrect matrix")
    CHECK_TRUE(m5 == element_specific_expected, "Multiple vector construction produces incorrect matrix")
    CHECK_TRUE(m6 == element_specific_colmajor_expected, "Multiple vector column-major construction produces incorrect matrix")
    CHECK_TRUE(m7 == element_specific_expected, "Element specific construction produces incorrect matrix")
    CHECK_TRUE(m8 == element_specific_colmajor_expected, "Element specific column-major construction produces incorrect matrix")
    CHECK_TRUE(m9 == diagonal_expected, "Diagonal construction produces incorrect matrix")

TEST_END(test_mat3_construction)


TEST_START(test_mat3_copy_move)

    mat3 expected(
        0.0f,  1.0f,  2.0f,
        4.0f,  5.0f,  6.0f,
        8.0f,  9.0f,  10.0f
    );
    mat3 m_cp_assignment = expected;
    mat3 m_mv_assignment = mat3(
        0.0f,  1.0f,  2.0f, 
        4.0f,  5.0f,  6.0f, 
        8.0f,  9.0f,  10.0f
    );
    mat3 m_cp_constructor(expected);
    mat3 m_mv_constructor(mat3(
        0.0f,  1.0f,  2.0f,
        4.0f,  5.0f,  6.0f,
        8.0f,  9.0f,  10.0f
    ));

    CHECK_TRUE(m_cp_assignment  == expected, "Matrix copy assignment failed")
    CHECK_TRUE(m_mv_assignment  == expected, "Matrix move assignment failed")
    CHECK_TRUE(m_cp_constructor == expected, "Matrix copy constructor failed")
    CHECK_TRUE(m_mv_constructor == expected, "Matrix move constructor failed")

TEST_END(test_mat3_copy_move)


TEST_START(test_mat3_mat3_multiplication)

    mat3 m0;
    mat3 m_identity(1.0f);
    mat3 m_random1(
        0.4f, 9.2f, 2.9f,
        8.6f, 4.5f, 2.7f,
        4.1f, 2.3f, 7.7f
    );
    mat3 m_random2(
        3.4f, 4.8f, 4.2f,
        6.4f, 8.3f, 5.4f,
        4.2f, 6.6f, 1.4f
    );

    mat3 result_zero = m0 * m_random1;
    mat3 result_identity = m_identity * m_random1;
    mat3 result_random = m_random1 * m_random2;

    mat3 expected_zero;
    mat3 expected_identity = m_random1;
    mat3 expected_random(
        72.42f, 97.42f, 55.42f,
        69.38f, 96.45f, 64.20f,
        61.00f, 89.59f, 40.42f
    );

    CHECK_TRUE(result_zero == expected_zero, "Zero matrix times any matrix does not produce zero matrix")
    CHECK_TRUE(result_identity == expected_identity, "Identity matrix times any matrix does not produce original matrix")
    CHECK_TRUE(result_random == expected_random, "Matrix multiplication incorrect")

TEST_END(test_mat3_mat3_multiplication)


TEST_START(test_mat3_rotation_matrix)

    float sin_60 = 0.866025403784f;
    float cos_60 = 0.500000000000f;

    mat3 rotx = mat3::rot_x(radians(60.0f));
    mat3 roty = mat3::rot_y(radians(60.0f));
    mat3 rotz = mat3::rot_z(radians(60.0f));

    mat3 expected_rotx = mat3(
        1.0f,   0.0f,   0.0f,
        0.0f,  cos_60, sin_60,
        0.0f, -sin_60, cos_60
    );
    mat3 expected_roty = mat3(
        cos_60, 0.0f, sin_60,
         0.0f,  1.0f,  0.0f, 
       -sin_60, 0.0f, cos_60
    );
    mat3 expected_rotz = mat3(
        cos_60, sin_60, 0.0f,
       -sin_60, cos_60, 0.0f,
         0.0f,   0.0f,  1.0f
    );

    CHECK_TRUE(rotx == expected_rotx, "X rotation matrix incorrect")
    CHECK_TRUE(roty == expected_roty, "Y rotation matrix incorrect")
    CHECK_TRUE(rotz == expected_rotz, "Z rotation matrix incorrect")

TEST_END(test_mat3_rotation_matrix)


TEST_START(test_mat3_scale_matrix)

    mat3 scale_uniform = mat3::scale(3.0f);
    mat3 scale  = mat3::scale(vec3(2.0f, 0.0f, -1.5f));
    mat3 scalex = mat3::scale_x(2.0f);
    mat3 scaley = mat3::scale_y(2.0f);
    mat3 scalez = mat3::scale_z(2.0f);

    mat3 expected_scale_uniform = mat3(
        3.0f, 0.0f, 0.0f,
        0.0f, 3.0f, 0.0f,
        0.0f, 0.0f, 3.0f
    );
    mat3 expected_scale = mat3(
        2.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f,-1.5f
    );
    mat3 expected_scalex = mat3(
        2.0f, 0.0f, 0.0f, 
        0.0f, 1.0f, 0.0f, 
        0.0f, 0.0f, 1.0f
    );
    mat3 expected_scaley = mat3(
        1.0f, 0.0f, 0.0f,
        0.0f, 2.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    );
    mat3 expected_scalez = mat3(
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 2.0f
    );

    CHECK_TRUE(scale_uniform == expected_scale_uniform, "Uniform scale matrix incorrect")
    CHECK_TRUE(scale  == expected_scale,  "Multi vaule scale matrix incorrect")
    CHECK_TRUE(scalex == expected_scalex, "X scale matrix incorrect")
    CHECK_TRUE(scaley == expected_scaley, "Y scale matrix incorrect")
    CHECK_TRUE(scalez == expected_scalez, "Z scale matrix incorrect")

TEST_END(test_mat3_scale_matrix)


TEST_START(test_mat3_vec3_multiplication)

    vec3 v(2.5f, 0.0f, -2.5f);
    mat3 m(
        3.4f, 4.8f, 4.2f,
        6.4f, 8.3f, 5.4f,
        4.2f, 6.6f, 1.4f
    );
    vec3 result = m * v;
    vec3 expected(-2.0f, 2.5f, 7.0f);

    CHECK_TRUE(result == expected, "3x3 Matrix * 3D Vector multiplication result incorrect (random values)")

TEST_END(test_mat3_vec3_multiplication)


TEST_START(test_mat3_vec3_rotations)

    vec3f v0 = vec3(1.0f, 1.0f, 1.0f);
    vec3f v0_result = mat3::rot_x(radians(90)) * v0;

    vec3f v1 = vec3(1.0f, 1.0f, 1.0f);
    vec3f v1_result = mat3::rot_y(radians(90)) * v1;

    vec3f v2 = vec3(1.0f, 1.0f, 1.0f);
    vec3f v2_result = mat3::rot_z(radians(90)) * v2;

    vec3f v0_expected = vec3f(1.0f, 1.0f, -1.0f);
    vec3f v1_expected = vec3f(1.0f, 1.0f, -1.0f);
    vec3f v2_expected = vec3f(1.0f, -1.0f, 1.0f);

    CHECK_TRUE(v0_result == v0_expected, "X rotation failed")
    CHECK_TRUE(v1_result == v1_expected, "Y rotation failed")
    CHECK_TRUE(v2_result == v2_expected, "Z rotation failed")

TEST_END(test_mat3_vec3_rotations)


TEST_START(test_mat3_vec3_scale)

    vec3f v0 = vec3(1.0f, 1.0f, 1.0f);
    vec3f v0_result = mat3::scale(2.0f, -1.5f, 0.0f) * v0;

    vec3f v1 = vec3(1.0f, 1.0f, 1.0f);
    vec3f v1_result = mat3::scale_x(10.0f) * v1;

    vec3f v2 = vec3(1.0f, 1.0f, 1.0f);
    vec3f v2_result = mat3::scale_y(10.0f) * v2;

    vec3f v3 = vec3(1.0f, 1.0f, 1.0f);
    vec3f v3_result = mat3::scale_z(10.0f) * v3;

    vec3f v0_expected = vec3f(2.0f, -1.5f, 0.0f);
    vec3f v1_expected = vec3f(10.0f, 1.0f, 1.0f);
    vec3f v2_expected = vec3f(1.0f, 10.0f, 1.0f);
    vec3f v3_expected = vec3f(1.0f, 1.0f, 10.0f);

    CHECK_TRUE(v0_result == v0_expected, "Multi value scale failed")
    CHECK_TRUE(v1_result == v1_expected, "X scale failed")
    CHECK_TRUE(v2_result == v2_expected, "Y scale failed")
    CHECK_TRUE(v3_result == v3_expected, "Z scale failed")

TEST_END(test_mat3_vec3_scale)

