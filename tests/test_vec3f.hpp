/*
 * Unit tests for vec3f class
 * Using custom eztest framework, see eztest_macros.h for implementation detail
 */

TEST_START(test_vec3f_addition)

    vec3f u(1.0f, 2.0f, 3.0f);
    vec3f v(1.0f, -5.0f, 15.0f);
    vec3f result;

    result = u + v;
    CHECK_EQ(result.x,  2.0f, "vec3f + vec3f addition incorrect in x component")
    CHECK_EQ(result.y, -3.0f, "vec3f + vec3f addition incorrect in y component")
    CHECK_EQ(result.z, 18.0f, "vec3f + vec3f addition incorrect in z component")

TEST_END(test_vec3f_addition)


TEST_START(test_vec3f_subtraction)

    vec3f u(1.0f, 2.0f, 3.0f);
    vec3f v(1.0f, -5.0f, 15.0f);
    vec3f result;

    result = u - v;
    CHECK_EQ(result.x,   0.0f, "vec3f - vec3f subtraction incorrect in x component")
    CHECK_EQ(result.y,   7.0f, "vec3f - vec3f subtraction incorrect in y component")
    CHECK_EQ(result.z, -12.0f, "vec3f - vec3f subtraction incorrect in z component")

TEST_END(test_vec3f_subtraction)


TEST_START(test_vec3f_dot_product)

    vec3f u(1.0f, 2.0f, 3.0f);
    vec3f v(1.0f, -5.0f, 15.0f);
    float result;

    result = u.dot(v);
    CHECK_EQ(result, 36.0f, "vec3f . vec3f dot product incorrect")
    
    result = v.dot(u);
    CHECK_EQ(result, 36.0f, "vec3f . vec3f dot product incorrect - non-commutative")

TEST_END(test_vec3f_dot_product)


TEST_START(test_vec3f_cross_product)

    vec3f u(2.0f, 3.0f, 4.0f);
    vec3f v(5.0f, 6.0f, 7.0f);
    vec3f result;

    result = u.cross(v);
    CHECK_EQ(result.x, -3.0f, "vec3f x vec3f cross product incorrect in x component")
    CHECK_EQ(result.y,  6.0f, "vec3f y vec3f cross product incorrect in y component")
    CHECK_EQ(result.z, -3.0f, "vec3f z vec3f cross product incorrect in z component")
    
    result = v.cross(u);
    CHECK_EQ(result.x,  3.0f, "vec3f x vec3f cross product incorrect - commutativity issue")
    CHECK_EQ(result.y, -6.0f, "vec3f y vec3f cross product incorrect - commutativity issue")
    CHECK_EQ(result.z,  3.0f, "vec3f z vec3f cross product incorrect - commutativity issue")

TEST_END(test_vec3f_cross_product)


TEST_START(test_vec3f_reflect)

    vec3f n0(0.0f, 1.0f, 0.0f);
    vec3f v0(1.0f, -1.0f, 0.0f);
    vec3f n1(2.7f, -1.2f, 5.3f);
    vec3f v1(0.25f, 5.2f, -8.8f);
    vec3f result;

    result = v0.reflect(n0);
    CHECK_EQ(result.x, 1.0f, "vec3f reflection incorrect in x component - 2D test")
    CHECK_EQ(result.y, 1.0f, "vec3f reflection incorrect in y component - 2D test")
    CHECK_EQ(result.z, 0.0f, "vec3f reflection incorrect in z component - 2D test")

    result = v1.reflect(n1);
    CHECK_EQ_EPS(result.magnitude(), v1.magnitude(), "vec3f magnitude changed after reflection")

TEST_END(test_vec3f_reflect)


TEST_START(test_vec3f_refract)

    float n1 = 1.0f;
    float n2 = 1.5f;

    vec3 incident0(0.70710678f, 0.0f, 0.70710678f);
    vec3 normal0(0.0f, 0.0f, -1.0f);
    vec3 result0 = incident0.refract(normal0, n1, n2).normalize();
    vec3 expected0(0.47140452f, 0.0f, 0.88191712f);

    vec3 incident1(4.0f, 1.0f, 1.0f);
    vec3 normal1(0.0f, -2.0f, -1.0f);
    vec3 result1 = incident1.refract(normal1, n1, n2).normalize();
    vec3 expected1(0.62853944f, 0.66139334f, 0.40926408f);

    vec3 incident2(0.1f, 0.0f, 1.0f);
    vec3 normal2(0.0f, 0.0f, -1.0f);
    vec3 result2 = incident2.refract(normal2, n2, n1).normalize();
    vec3 expected2(0.149256f, 0.0f, 0.988799f);

    vec3 incident3(0.5f, -0.5f, 0.5f);
    vec3 normal3 = vec3(0.0f, 1.0f, 0.0f).normalize();
    vec3 result3 = incident3.refract(normal3, n1, n1);
    vec3 expected3 = incident3.normalize();

    CHECK_EQ_EPS(result0.x, expected0.x, "vec3f refraction incorrect in x component - 2D test")
    CHECK_EQ_EPS(result0.y, expected0.y, "vec3f refraction incorrect in y component - 2D test")
    CHECK_EQ_EPS(result0.z, expected0.z, "vec3f refraction incorrect in z component - 2D test")

    CHECK_EQ_EPS(result1.x, expected1.x, "vec3f refraction incorrect in x component - 3D test")
    CHECK_EQ_EPS(result1.y, expected1.y, "vec3f refraction incorrect in y component - 3D test")
    CHECK_EQ_EPS(result1.z, expected1.z, "vec3f refraction incorrect in z component - 3D test")

    CHECK_EQ_EPS(result2.x, expected2.x, "vec3f refraction incorrect in x component - high index to low test")
    CHECK_EQ_EPS(result2.y, expected2.y, "vec3f refraction incorrect in y component - high index to low test")
    CHECK_EQ_EPS(result2.z, expected2.z, "vec3f refraction incorrect in z component - high index to low test")

    CHECK_EQ_EPS(result3.x, expected3.x, "vec3f refraction incorrect in x component - no change in refractive index")
    CHECK_EQ_EPS(result3.y, expected3.y, "vec3f refraction incorrect in y component - no change in refractive index")
    CHECK_EQ_EPS(result3.z, expected3.z, "vec3f refraction incorrect in z component - no change in refractive index")

TEST_END(test_vec3f_refract)


TEST_START(test_scalar_addition)

    vec3f v(0.0f, 5.0f, 10.0f);
    vec3f result;

    result = v + 2.0f;
    CHECK_EQ(result.x, 2.0f,  "vec3f.x + float scalar addition failed")
    CHECK_EQ(result.y, 7.0f,  "vec3f.y + float scalar addition failed")
    CHECK_EQ(result.z, 12.0f, "vec3f.z + float scalar addition failed")

    result = 2.0f + v;
    CHECK_EQ(result.x, 2.0f,  "float scalar + vec3f.x addition failed")
    CHECK_EQ(result.y, 7.0f,  "float scalar + vec3f.y addition failed")
    CHECK_EQ(result.z, 12.0f, "float scalar + vec3f.z addition failed")

    result = v + 2;
    CHECK_EQ(result.x, 2.0f,  "vec3f.x + int scalar addition failed")
    CHECK_EQ(result.y, 7.0f,  "vec3f.y + int scalar addition failed")
    CHECK_EQ(result.z, 12.0f, "vec3f.z + int scalar addition failed")

    result = 2 + v;
    CHECK_EQ(result.x, 2.0f,  "int scalar + vec3f.x addition failed")
    CHECK_EQ(result.y, 7.0f,  "int scalar + vec3f.y addition failed")
    CHECK_EQ(result.z, 12.0f, "int scalar + vec3f.z addition failed")

TEST_END(test_scalar_addition)


TEST_START(test_scalar_subtraction)

    vec3f v(0.0f, 5.0f, 10.0f);
    vec3f result;

    result = v - 2.0f;
    CHECK_EQ(result.x, -2.0f,  "vec3f.x - float scalar subtraction failed")
    CHECK_EQ(result.y,  3.0f,  "vec3f.y - float scalar subtraction failed")
    CHECK_EQ(result.z,  8.0f,  "vec3f.z - float scalar subtraction failed")

    result = 2.0f - v;
    CHECK_EQ(result.x,  2.0f,  "float scalar - vec3f.x subtraction failed")
    CHECK_EQ(result.y, -3.0f,  "float scalar - vec3f.y subtraction failed")
    CHECK_EQ(result.z, -8.0f,  "float scalar - vec3f.z subtraction failed")

    result = v - 2;
    CHECK_EQ(result.x, -2.0f,  "vec3f.x - int scalar subtraction failed")
    CHECK_EQ(result.y,  3.0f,  "vec3f.y - int scalar subtraction failed")
    CHECK_EQ(result.z,  8.0f,  "vec3f.z - int scalar subtraction failed")

    result = 2 - v;
    CHECK_EQ(result.x,  2.0f,  "int scalar - vec3f.x subtraction failed")
    CHECK_EQ(result.y, -3.0f,  "int scalar - vec3f.y subtraction failed")
    CHECK_EQ(result.z, -8.0f,  "int scalar - vec3f.z subtraction failed")

TEST_END(test_scalar_subtraction)


TEST_START(test_scalar_multiplication)

    vec3f v(0.0f, 5.0f, 10.0f);
    vec3f result;

    result = v * 2.0f;
    CHECK_EQ(result.x,  0.0f,  "vec3f.x * float scalar multiplication failed")
    CHECK_EQ(result.y, 10.0f,  "vec3f.y * float scalar multiplication failed")
    CHECK_EQ(result.z, 20.0f,  "vec3f.z * float scalar multiplication failed")

    result = 2.0f * v;
    CHECK_EQ(result.x,  0.0f,  "float scalar * vec3f.x multiplication failed")
    CHECK_EQ(result.y, 10.0f,  "float scalar * vec3f.y multiplication failed")
    CHECK_EQ(result.z, 20.0f,  "float scalar * vec3f.z multiplication failed")

    result = v * 2;
    CHECK_EQ(result.x,  0.0f,  "vec3f.x * int scalar multiplication failed")
    CHECK_EQ(result.y, 10.0f,  "vec3f.y * int scalar multiplication failed")
    CHECK_EQ(result.z, 20.0f,  "vec3f.z * int scalar multiplication failed")

    result = 2 * v;
    CHECK_EQ(result.x,  0.0f,  "int scalar * vec3f.x multiplication failed")
    CHECK_EQ(result.y, 10.0f,  "int scalar * vec3f.y multiplication failed")
    CHECK_EQ(result.z, 20.0f,  "int scalar * vec3f.z multiplication failed")

TEST_END(test_scalar_multiplication)


TEST_START(test_scalar_division)

    vec3f v(1.0f, 5.0f, 10.0f);
    vec3f result;

    result = v / 2.0f;
    CHECK_EQ(result.x, 0.5f,  "vec3f.x / float scalar division failed")
    CHECK_EQ(result.y, 2.5f,  "vec3f.y / float scalar division failed")
    CHECK_EQ(result.z, 5.0f,  "vec3f.z / float scalar division failed")

    result = 2.0f / v;
    CHECK_EQ(result.x, 2.0f,  "float scalar / vec3f.x division failed")
    CHECK_EQ(result.y, 0.4f,  "float scalar / vec3f.y division failed")
    CHECK_EQ(result.z, 0.2f,  "float scalar / vec3f.z division failed")

    result = v / 2;
    CHECK_EQ(result.x, 0.5f,  "vec3f.x / int scalar division failed")
    CHECK_EQ(result.y, 2.5f,  "vec3f.y / int scalar division failed")
    CHECK_EQ(result.z, 5.0f,  "vec3f.z / int scalar division failed")

    result = 2 / v;
    CHECK_EQ(result.x, 2.0f,  "int scalar / vec3f.x division failed")
    CHECK_EQ(result.y, 0.4f,  "int scalar / vec3f.y division failed")
    CHECK_EQ(result.z, 0.2f,  "int scalar / vec3f.z division failed")

TEST_END(test_scalar_division)


TEST_START(test_scalar_negation)

    vec3f v(0.0f, 5.0f, -10.0f);
    vec3f result;

    result = -v;
    CHECK_EQ(result.x,  0.0f,  "vec3f negation incorrect in x component")
    CHECK_EQ(result.y, -5.0f,  "vec3f negation incorrect in y component")
    CHECK_EQ(result.z, 10.0f,  "vec3f negation incorrect in z component")

TEST_END(test_scalar_negation)


TEST_START(test_vec3f_magnitude)

    vec3f v(2.0f, 4.0f, 15.0f);
    vec3f zero;
    float result;

    result = v.magnitude();
    CHECK_EQ_EPS(result, 15.65247584249853f, "vec3f magnitude incorrect")

    result = zero.magnitude();
    CHECK_EQ(result, 0.0f, "vec3f magnitude incorrect (0 case)")

TEST_END(test_vec3f_magnitude)


TEST_START(test_vec3f_normalize)

    vec3f v(2.0f, 4.0f, 15.0f);
    vec3f zero;
    vec3f result;

    result = v.normalize();
    CHECK_EQ_EPS(result.x, 0.1277753129999880f, "vec3f normalization incorrect in x component")
    CHECK_EQ_EPS(result.y, 0.2555506259999759f, "vec3f normalization incorrect in y component")
    CHECK_EQ_EPS(result.z, 0.9583148474999097f, "vec3f normalization incorrect in z component")

    result = zero.normalize();
    CHECK_EQ(result.x, 0.0f, "vec3f normalization incorrect in x component (0 case)")
    CHECK_EQ(result.y, 0.0f, "vec3f normalization incorrect in y component (0 case)")
    CHECK_EQ(result.z, 0.0f, "vec3f normalization incorrect in z component (0 case)")

TEST_END(test_vec3f_normalize)


TEST_START(test_vec3f_constructors)

    vec3f v0;
    CHECK_EQ(v0.x, 0.0f, "vec3f default constructor does not initialize x component to 0");
    CHECK_EQ(v0.y, 0.0f, "vec3f default constructor does not initialize y component to 0");
    CHECK_EQ(v0.z, 0.0f, "vec3f default constructor does not initialize z component to 0");

    vec3f v1(42.0f);
    CHECK_EQ(v1.x, 42.0f, "vec3f single paramater constructor does not initialize x component correctly");
    CHECK_EQ(v1.y, 42.0f, "vec3f single paramater constructor does not initialize y component correctly");
    CHECK_EQ(v1.z, 42.0f, "vec3f single paramater constructor does not initialize z component correctly");

    vec3f v2(42);
    CHECK_EQ(v2.x, 42.0f, "vec3f single paramater integer constructor does not initialize x component correctly");
    CHECK_EQ(v2.y, 42.0f, "vec3f single paramater integer constructor does not initialize y component correctly");
    CHECK_EQ(v2.z, 42.0f, "vec3f single paramater integer constructor does not initialize z component correctly");

    vec3f v3(1.0f, 2.0f, 3.0f);
    CHECK_EQ(v3.x, 1.0f, "vec3f multiparamater constructor does not initialize x component correctly");
    CHECK_EQ(v3.y, 2.0f, "vec3f multiparamater constructor does not initialize y component correctly");
    CHECK_EQ(v3.z, 3.0f, "vec3f multiparamater constructor does not initialize z component correctly");

    vec3f v4(1, 2, 3);
    CHECK_EQ(v4.x, 1.0f, "vec3f multiparamater integer constructor does not initialize x component correctly");
    CHECK_EQ(v4.y, 2.0f, "vec3f multiparamater integer constructor does not initialize y component correctly");
    CHECK_EQ(v4.z, 3.0f, "vec3f multiparamater integer constructor does not initialize z component correctly");

    float fcomponents[3] = {1.0f, 2.0f, 3.0f};
    vec3f v5(fcomponents);
    CHECK_EQ(v5.x, 1.0f, "vec3f array constructor does not initialize x component correctly");
    CHECK_EQ(v5.y, 2.0f, "vec3f array constructor does not initialize y component correctly");
    CHECK_EQ(v5.z, 3.0f, "vec3f array constructor does not initialize z component correctly");

    int icomponents[3] = {1, 2, 3};
    vec3f v6(icomponents);
    CHECK_EQ(v6.x, 1.0f, "vec3f array integer constructor does not initialize x component correctly");
    CHECK_EQ(v6.y, 2.0f, "vec3f array integer constructor does not initialize y component correctly");
    CHECK_EQ(v6.z, 3.0f, "vec3f array integer constructor does not initialize z component correctly");

TEST_END(test_vec3f_constructors)


TEST_START(test_vec3f_copy_move)

    vec3f u0(2.0f, 4.0f, 8.0f);
    vec3f v0(u0);
    CHECK_EQ(v0.x, 2.0f, "vec3f copy constructor does not copy x component correctly");
    CHECK_EQ(v0.y, 4.0f, "vec3f copy constructor does not copy y component correctly");
    CHECK_EQ(v0.z, 8.0f, "vec3f copy constructor does not copy z component correctly");

    vec3f v1(vec3f(2.0f, 4.0f, 8.0f));
    CHECK_EQ(v1.x, 2.0f, "vec3f move constructor does not move x component correctly");
    CHECK_EQ(v1.y, 4.0f, "vec3f move constructor does not move y component correctly");
    CHECK_EQ(v1.z, 8.0f, "vec3f move constructor does not move z component correctly");

    vec3f u2(2.0f, 4.0f, 8.0f);
    vec3f v2;
    v2 = u2;
    CHECK_EQ(v2.x, 2.0f, "vec3f copy assignment does not copy x component correctly");
    CHECK_EQ(v2.y, 4.0f, "vec3f copy assignment does not copy y component correctly");
    CHECK_EQ(v2.z, 8.0f, "vec3f copy assignment does not copy z component correctly");

    vec3f v3;
    v3 = vec3f(2.0f, 4.0f, 8.0f);
    CHECK_EQ(v3.x, 2.0f, "vec3f move assignment does not move x component correctly");
    CHECK_EQ(v3.y, 4.0f, "vec3f move assignment does not move y component correctly");
    CHECK_EQ(v3.z, 8.0f, "vec3f move assignment does not move z component correctly");

TEST_END(test_vec3f_copy_move)


TEST_START(test_vec3f_equality)

    vec3f u(1.0f, 2.0f, 3.0f);
    vec3f v(1.0f, 2.0f, 3.0f);
    vec3f d(-1.0f, -2.0f, -3.0f);

    CHECK_TRUE( u == v, "vec3f == vec3f equality operator returns false on equivalent vectors")
    CHECK_FALSE(u == d, "vec3f == vec3f equality operator returns true on non-equivalent vectors")
    CHECK_FALSE(u != v, "vec3f != vec3f equality operator returns true on equivalent vectors")
    CHECK_TRUE( u != d, "vec3f != vec3f equality operator returns false on non-equivalent vectors")

TEST_END(test_vec3f_equality)

