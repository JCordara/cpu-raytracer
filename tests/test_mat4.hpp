/*
 * Unit tests for mat4 class
 * Using custom eztest framework, see eztest_macros.h for implementation detail
 */

TEST_START(test_mat4_equality)

    mat4 m0(
        0.0f,  1.0f,  2.0f,  3.0f,
        4.0f,  5.0f,  6.0f,  7.0f,
        8.0f,  9.0f,  10.0f, 11.0f,
        12.0f, 13.0f, 14.0f, 15.0f
    );
    mat4 m1(
        0.0f,  1.0f,  2.0f,  3.0f,
        4.0f,  5.0f,  6.0f,  7.0f,
        8.0f,  9.0f,  10.0f, 11.0f,
        12.0f, 13.0f, 14.0f, 15.0f
    );
    mat4 m2(
        1.0f,  1.0f,  2.0f,  3.0f,
        3.0f,  5.0f,  5.0f,  7.0f,
        8.0f,  9.5f,  10.0f, 11.0f,
        12.0f, 13.0f, 14.0f, 15.0f
    );

    CHECK_TRUE(m0 == m1, "Equality operator returns false on equivalent matrices")
    CHECK_FALSE(m0 == m2, "Equality operator returns true on non-equivalent matrices")
    CHECK_FALSE(m0 != m1, "Inequality operator returns true on equivalent matrices")
    CHECK_TRUE(m0 != m2, "Inequality operator returns false on non-equivalent matrices")

TEST_END(test_mat4_equality)


TEST_START(test_mat4_elementwise_constructor)

    mat4 m(
        0.0f,  1.0f,  2.0f,  3.0f,
        4.0f,  5.0f,  6.0f,  7.0f,
        8.0f,  9.0f,  10.0f, 11.0f,
        12.0f, 13.0f, 14.0f, 15.0f
    );

    CHECK_EQ_EPS(m[0][0], 0.0f,  "First element incorrect"      )
    CHECK_EQ_EPS(m[0][1], 1.0f,  "Second element incorrect"     )
    CHECK_EQ_EPS(m[0][2], 2.0f,  "Third element incorrect"      )
    CHECK_EQ_EPS(m[0][3], 3.0f,  "Fourth element incorrect"     )
    CHECK_EQ_EPS(m[1][0], 4.0f,  "Fifth element incorrect"      )
    CHECK_EQ_EPS(m[1][1], 5.0f,  "Sixth element incorrect"      )
    CHECK_EQ_EPS(m[1][2], 6.0f,  "Seventh element incorrect"    )
    CHECK_EQ_EPS(m[1][3], 7.0f,  "Eighth element incorrect"     )
    CHECK_EQ_EPS(m[2][0], 8.0f,  "Nineth element incorrect"     )
    CHECK_EQ_EPS(m[2][1], 9.0f,  "Tenth element incorrect"      )
    CHECK_EQ_EPS(m[2][2], 10.0f, "Eleventh element incorrect"   )
    CHECK_EQ_EPS(m[2][3], 11.0f, "Twelvth element incorrect"    )
    CHECK_EQ_EPS(m[3][0], 12.0f, "Thirteenth element incorrect" )
    CHECK_EQ_EPS(m[3][1], 13.0f, "Fourteenth element incorrect" )
    CHECK_EQ_EPS(m[3][2], 14.0f, "Fifteenth element incorrect"  )
    CHECK_EQ_EPS(m[3][3], 15.0f, "Sixteenth element incorrect"  )

TEST_END(test_mat4_elementwise_constructor)


TEST_START(test_mat4_construction)

    // Used for construction
    vec4 v0 = vec4(0.0f,  1.0f,  2.0f,  3.0f);
    vec4 v1 = vec4(4.0f,  5.0f,  6.0f,  7.0f);
    vec4 v2 = vec4(8.0f,  9.0f,  10.0f, 11.0f);
    vec4 v3 = vec4(12.0f, 13.0f, 14.0f, 15.0f);

    mat4 m0;
    mat4 m1(v0);
    mat4 m2(v0, true);
    mat4 m3(vec4(0.0f, 1.0f, 2.0f, 3.0f));
    mat4 m4(vec4(0.0f, 1.0f, 2.0f, 3.0f), true);
    mat4 m5(v0, v1, v2, v3);
    mat4 m6(v0, v1, v2, v3, true);
    mat4 m7(
        0.0f,  1.0f,  2.0f,  3.0f,
        4.0f,  5.0f,  6.0f,  7.0f,
        8.0f,  9.0f,  10.0f, 11.0f,
        12.0f, 13.0f, 14.0f, 15.0f
    );
    mat4 m8(
        0.0f,  1.0f,  2.0f,  3.0f,
        4.0f,  5.0f,  6.0f,  7.0f,
        8.0f,  9.0f,  10.0f, 11.0f,
        12.0f, 13.0f, 14.0f, 15.0f,
        true
    );
    mat4 m9(1.0f);

    mat4 default_expected(
        0.0f, 0.0f, 0.0f, 0.0f, 
        0.0f, 0.0f, 0.0f, 0.0f, 
        0.0f, 0.0f, 0.0f, 0.0f, 
        0.0f, 0.0f, 0.0f, 0.0f
    );
    mat4 single_vec_init_expected(
        0.0f, 1.0f, 2.0f, 3.0f, 
        0.0f, 1.0f, 2.0f, 3.0f, 
        0.0f, 1.0f, 2.0f, 3.0f, 
        0.0f, 1.0f, 2.0f, 3.0f
    );
    mat4 single_vec_init_colmajor_expected(
        0.0f, 0.0f, 0.0f, 0.0f, 
        1.0f, 1.0f, 1.0f, 1.0f, 
        2.0f, 2.0f, 2.0f, 2.0f, 
        3.0f, 3.0f, 3.0f, 3.0f
    );
    mat4 element_specific_expected(
        0.0f,  1.0f,  2.0f,  3.0f,
        4.0f,  5.0f,  6.0f,  7.0f,
        8.0f,  9.0f,  10.0f, 11.0f,
        12.0f, 13.0f, 14.0f, 15.0f
    );
    mat4 element_specific_colmajor_expected(
        0.0f, 4.0f, 8.0f,  12.0f,
        1.0f, 5.0f, 9.0f,  13.0f,
        2.0f, 6.0f, 10.0f, 14.0f,
        3.0f, 7.0f, 11.0f, 15.0f
    );
    mat4 diagonal_expected(
        1.0f, 0.0f, 0.0f, 0.0f, 
        0.0f, 1.0f, 0.0f, 0.0f, 
        0.0f, 0.0f, 1.0f, 0.0f, 
        0.0f, 0.0f, 0.0f, 1.0f
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

TEST_END(test_mat4_construction)


TEST_START(test_mat4_copy_move)

    mat4 expected(
        0.0f,  1.0f,  2.0f,  3.0f,
        4.0f,  5.0f,  6.0f,  7.0f,
        8.0f,  9.0f,  10.0f, 11.0f,
        12.0f, 13.0f, 14.0f, 15.0f
    );
    mat4 m_cp_assignment = expected;
    mat4 m_mv_assignment = mat4(
        0.0f,  1.0f,  2.0f,  3.0f,
        4.0f,  5.0f,  6.0f,  7.0f,
        8.0f,  9.0f,  10.0f, 11.0f,
        12.0f, 13.0f, 14.0f, 15.0f
    );
    mat4 m_cp_constructor(expected);
    mat4 m_mv_constructor(mat4(
        0.0f,  1.0f,  2.0f,  3.0f,
        4.0f,  5.0f,  6.0f,  7.0f,
        8.0f,  9.0f,  10.0f, 11.0f,
        12.0f, 13.0f, 14.0f, 15.0f
    ));

    CHECK_TRUE(m_cp_assignment  == expected, "Matrix copy assignment failed")
    CHECK_TRUE(m_mv_assignment  == expected, "Matrix move assignment failed")
    CHECK_TRUE(m_cp_constructor == expected, "Matrix copy constructor failed")
    CHECK_TRUE(m_mv_constructor == expected, "Matrix move constructor failed")

TEST_END(test_mat4_copy_move)


TEST_START(test_mat4_mat4_multiplication)

    mat4 m0;
    mat4 m_identity(1.0f);
    mat4 m_random1(
        0.4f, 9.2f, 2.9f, 1.1f,
        8.6f, 4.5f, 2.7f, 7.2f,
        4.1f, 2.3f, 7.7f, 1.1f,
        7.8f, 4.3f, 7.4f, 1.0f
    );
    mat4 m_random2(
        3.4f, 4.8f, 4.2f, 6.3f, 
        6.4f, 8.3f, 5.4f, 6.7f, 
        4.2f, 6.6f, 1.4f, 3.6f, 
        2.8f, 4.5f, 9.0f, 7.6f
    );

    mat4 result_zero = m0 * m_random1;
    mat4 result_identity = m_identity * m_random1;
    mat4 result_random = m_random1 * m_random2;

    mat4 expected_zero;
    mat4 expected_identity = m_random1;
    mat4 expected_random(
        75.5f,  102.37f, 65.32f, 82.96f, 
        89.54f, 128.85f, 129.0f, 148.77f, 
        64.08f, 94.54f,  50.32f, 77.32f, 
        87.92f, 126.47f, 75.34f, 112.19f
    );

    CHECK_TRUE(result_zero == expected_zero, "Zero matrix times any matrix does not produce zero matrix")
    CHECK_TRUE(result_identity == expected_identity, "Identity matrix times any matrix does not produce original matrix")
    CHECK_TRUE(result_random == expected_random, "Matrix multiplication incorrect")

TEST_END(test_mat4_mat4_multiplication)


TEST_START(test_mat4_rotation_matrix)

    float sin_60 = 0.866025403784f;
    float cos_60 = 0.500000000000f;

    mat4 rotx = mat4::rot_x(radians(60.0f));
    mat4 roty = mat4::rot_y(radians(60.0f));
    mat4 rotz = mat4::rot_z(radians(60.0f));

    mat4 expected_rotx = mat4(
        1.0f,   0.0f,   0.0f,  0.0f,
        0.0f,  cos_60, sin_60, 0.0f,
        0.0f, -sin_60, cos_60, 0.0f,
        0.0f,   0.0f,   0.0f,  1.0f
    );
    mat4 expected_roty = mat4(
        cos_60, 0.0f, sin_60, 0.0f,
         0.0f,  1.0f,  0.0f,  0.0f,
       -sin_60, 0.0f, cos_60, 0.0f,
         0.0f,  0.0f,  0.0f,  1.0f
    );
    mat4 expected_rotz = mat4(
        cos_60, sin_60, 0.0f, 0.0f,
       -sin_60, cos_60, 0.0f, 0.0f,
         0.0f,   0.0f,  1.0f, 0.0f,
         0.0f,   0.0f,  0.0f, 1.0f
    );

    CHECK_TRUE(rotx == expected_rotx, "X rotation matrix incorrect")
    CHECK_TRUE(roty == expected_roty, "Y rotation matrix incorrect")
    CHECK_TRUE(rotz == expected_rotz, "Z rotation matrix incorrect")

TEST_END(test_mat4_rotation_matrix)


TEST_START(test_mat4_scale_matrix)

    mat4 scale_uniform = mat4::scale(3.0f);
    mat4 scale  = mat4::scale(vec3f(2.0f, 0.0f, -1.5f));
    mat4 scalex = mat4::scale_x(2.0f);
    mat4 scaley = mat4::scale_y(2.0f);
    mat4 scalez = mat4::scale_z(2.0f);

    mat4 expected_scale_uniform = mat4(
        3.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 3.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 3.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
    mat4 expected_scale = mat4(
        2.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f,-1.5f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
    mat4 expected_scalex = mat4(
        2.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
    mat4 expected_scaley = mat4(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 2.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
    mat4 expected_scalez = mat4(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 2.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );

    CHECK_TRUE(scale_uniform == expected_scale_uniform, "Uniform scale matrix incorrect")
    CHECK_TRUE(scale  == expected_scale,  "Multi vaule scale matrix incorrect")
    CHECK_TRUE(scalex == expected_scalex, "X scale matrix incorrect")
    CHECK_TRUE(scaley == expected_scaley, "Y scale matrix incorrect")
    CHECK_TRUE(scalez == expected_scalez, "Z scale matrix incorrect")

TEST_END(test_mat4_scale_matrix)


TEST_START(test_mat4_translation_matrix)

    mat4 translate  = mat4::translate(vec3f(2.0f, 0.0f, -1.5f));
    mat4 translatex = mat4::translate_x(2.0f);
    mat4 translatey = mat4::translate_y(2.0f);
    mat4 translatez = mat4::translate_z(2.0f);

    mat4 expected_translate = mat4(
        1.0f, 0.0f, 0.0f, 2.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f,-1.5f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
    mat4 expected_translatex = mat4(
        1.0f, 0.0f, 0.0f, 2.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
    mat4 expected_translatey = mat4(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 2.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
    mat4 expected_translatez = mat4(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 2.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );

    CHECK_TRUE(translate  == expected_translate,  "Multi value translate matrix incorrect")
    CHECK_TRUE(translatex == expected_translatex, "X translate matrix incorrect")
    CHECK_TRUE(translatey == expected_translatey, "Y translate matrix incorrect")
    CHECK_TRUE(translatez == expected_translatez, "Z translate matrix incorrect")

TEST_END(test_mat4_translation_matrix)


TEST_START(test_mat4_vec4_multiplication)

    vec4f v(2.5f, 0.0f, -2.5f, 99.9f);
    mat4 m(
        3.4f, 4.8f, 4.2f, 6.3f, 
        6.4f, 8.3f, 5.4f, 6.7f, 
        4.2f, 6.6f, 1.4f, 3.6f, 
        2.8f, 4.5f, 9.0f, 7.6f
    );
    vec4f result = m * v;
    vec4f expected(627.37f, 671.83f, 366.64f, 743.74f);

    CHECK_TRUE(result == expected, "4x4 Matrix * 4D Vector multiplication result incorrect (random values)")

TEST_END(test_mat4_vec4_multiplication)


TEST_START(test_mat4_vec3_multiplication)

    vec3f v0(2.5f, 0.0f, -2.5f);
    mat4 m0(
        3.0f, 0.0f, 0.0f, 0.0f, 
        0.0f, 3.0f, 0.0f, 0.0f, 
        0.0f, 0.0f, 3.0f, 0.0f, 
        0.0f, 0.0f, 0.0f, 1.0f
    );
    vec3f result0 = m0 * v0;
    vec3f expected0(7.5f, 0.0f, -7.5f);

    vec3f v1(2.0f, 0.0f, 10.0f);
    mat4 m1(
        0.0f, 1.0f, 0.0f, 0.0f, 
       -1.0f, 0.0f, 0.0f, 0.0f, 
        0.0f, 0.0f, 1.0f, 0.0f, 
        0.0f, 0.0f, 0.0f, 1.0f
    );
    vec3f result1 = m1 * v1;
    vec3f expected1(0.0f, -2.0f, 10.0f);

    vec3f v2(2.0f, 3.0f, 4.0f);
    mat4 m2(
        1.0f, 0.0f, 0.0f,  1.0f, 
        0.0f, 1.0f, 0.0f,  2.0f, 
        0.0f, 0.0f, 1.0f, -3.0f, 
        0.0f, 0.0f, 0.0f,  1.0f
    );
    vec3f result2 = m2 * v2;
    vec3f expected2(3.0f, 5.0f, 1.0f);

    CHECK_TRUE(result0 == expected0, "4x4 Matrix * 3D Vector multiplication result incorrect (scale)")
    CHECK_TRUE(result1 == expected1, "4x4 Matrix * 3D Vector multiplication result incorrect (rotation)")
    CHECK_TRUE(result2 == expected2, "4x4 Matrix * 3D Vector multiplication result incorrect (translation)")

TEST_END(test_mat4_vec3_multiplication)


TEST_START(test_mat4_vec3_translations)

    vec3f v0 = vec3(1.0f, 1.0f, 1.0f);
    vec3f v0_result = mat4::translate(vec3(2.0f, -1.5f, 0.0f)) * v0;

    vec3f v1 = vec3(1.0f, 1.0f, 1.0f);
    vec3f v1_result = mat4::translate_x(10.0f) * v1;

    vec3f v2 = vec3(1.0f, 1.0f, 1.0f);
    vec3f v2_result = mat4::translate_y(10.0f) * v2;

    vec3f v3 = vec3(1.0f, 1.0f, 1.0f);
    vec3f v3_result = mat4::translate_z(10.0f) * v3;

    vec3f v0_expected = vec3f(3.0f, -0.5f, 1.0f);
    vec3f v1_expected = vec3f(11.0f, 1.0f, 1.0f);
    vec3f v2_expected = vec3f(1.0f, 11.0f, 1.0f);
    vec3f v3_expected = vec3f(1.0f, 1.0f, 11.0f);

    CHECK_TRUE(v0_result == v0_expected, "Multi value translation failed")
    CHECK_TRUE(v1_result == v1_expected, "X translation failed")
    CHECK_TRUE(v2_result == v2_expected, "Y translation failed")
    CHECK_TRUE(v3_result == v3_expected, "Z translation failed")

TEST_END(test_mat4_vec3_translations)


TEST_START(test_mat4_vec3_rotations)

    vec3f v0 = vec3(1.0f, 1.0f, 1.0f);
    vec3f v0_result = mat4::rot_x(radians(90)) * v0;

    vec3f v1 = vec3(1.0f, 1.0f, 1.0f);
    vec3f v1_result = mat4::rot_y(radians(90)) * v1;

    vec3f v2 = vec3(1.0f, 1.0f, 1.0f);
    vec3f v2_result = mat4::rot_z(radians(90)) * v2;

    vec3f v0_expected = vec3f(1.0f, 1.0f, -1.0f);
    vec3f v1_expected = vec3f(1.0f, 1.0f, -1.0f);
    vec3f v2_expected = vec3f(1.0f, -1.0f, 1.0f);

    CHECK_TRUE(v0_result == v0_expected, "X rotation failed")
    CHECK_TRUE(v1_result == v1_expected, "Y rotation failed")
    CHECK_TRUE(v2_result == v2_expected, "Z rotation failed")

TEST_END(test_mat4_vec3_rotations)


TEST_START(test_mat4_vec3_scale)

    vec3f v0 = vec3(1.0f, 1.0f, 1.0f);
    vec3f v0_result = mat4::scale(2.0f, -1.5f, 0.0f) * v0;

    vec3f v1 = vec3(1.0f, 1.0f, 1.0f);
    vec3f v1_result = mat4::scale_x(10.0f) * v1;

    vec3f v2 = vec3(1.0f, 1.0f, 1.0f);
    vec3f v2_result = mat4::scale_y(10.0f) * v2;

    vec3f v3 = vec3(1.0f, 1.0f, 1.0f);
    vec3f v3_result = mat4::scale_z(10.0f) * v3;

    vec3f v0_expected = vec3f(2.0f, -1.5f, 0.0f);
    vec3f v1_expected = vec3f(10.0f, 1.0f, 1.0f);
    vec3f v2_expected = vec3f(1.0f, 10.0f, 1.0f);
    vec3f v3_expected = vec3f(1.0f, 1.0f, 10.0f);

    CHECK_TRUE(v0_result == v0_expected, "Multi value scale failed")
    CHECK_TRUE(v1_result == v1_expected, "X scale failed")
    CHECK_TRUE(v2_result == v2_expected, "Y scale failed")
    CHECK_TRUE(v3_result == v3_expected, "Z scale failed")

TEST_END(test_mat4_vec3_scale)

