#ifndef COMMON_MATH_H
#define COMMON_MATH_H

#define NaN           1.175494351e-38f
#define QUARTER_PI    0.7853981633974f
#define HALF_PI       1.5707963267948f
#define PI            3.1415926535897f
#define THREE_HALF_PI 4.7123889803846f
#define TWO_PI        6.2831853071795f

constexpr float _rad_to_deg_ratio = 180.0f / PI;
constexpr float _deg_to_rad_ratio = PI / 180.0f;
constexpr float _2_fact_inv = 1.0f / (2.0f);
constexpr float _3_fact_inv = 1.0f / (3.0f * 2.0f);
constexpr float _4_fact_inv = 1.0f / (4.0f * 3.0f * 2.0f);
constexpr float _5_fact_inv = 1.0f / (5.0f * 4.0f * 3.0f * 2.0f);
constexpr float _6_fact_inv = 1.0f / (6.0f * 5.0f * 4.0f * 3.0f * 2.0f);
constexpr float _7_fact_inv = 1.0f / (7.0f * 6.0f * 5.0f * 4.0f * 3.0f * 2.0f);

inline constexpr float radians(float degrees) {
    return _deg_to_rad_ratio * degrees;
}

inline constexpr float degrees(float radians) {
    return _rad_to_deg_ratio * radians;
}

inline constexpr float _sin_impl(float radians) {
    float pow3 = radians * radians * radians;
    float pow5 = pow3 * radians * radians;
    float pow7 = pow5 * radians * radians;
    return radians - (pow3 * _3_fact_inv) + (pow5 * _5_fact_inv) - (pow7 * _7_fact_inv);
}

inline constexpr float _cos_impl(float radians) {
    float pow2 = radians * radians;
    float pow4 = pow2 * radians * radians;
    float pow6 = pow4 * radians * radians;
    return 1 - (pow2 * _2_fact_inv) + (pow4 * _4_fact_inv) - (pow6 * _6_fact_inv);
}

inline float sin(float radians) {
    // Get into 0 - 360 degree range
    while (radians >= TWO_PI) radians -= TWO_PI;
    while (radians < 0) radians += TWO_PI;

    // Use vertical symmetry if in quadrants 3 or 4
    float multiplier = 1.0f;
    if (radians >= PI) {
        radians -= PI;
        multiplier = -1.0f;
    }

    if (radians >= HALF_PI) radians = PI - radians;
    if (radians < QUARTER_PI) return _sin_impl(radians) * multiplier;
    else return _cos_impl(HALF_PI - radians) * multiplier;
}

inline constexpr float cos(float radians) {
    // Get into 0 - 360 degree range
    while (radians >= TWO_PI) radians -= TWO_PI;
    while (radians < 0) radians += TWO_PI;

    // Use vertical symmetry if in quadrants 3 or 4
    float multiplier = 1.0f;
    if (radians >= PI) {
        radians -= PI;
        multiplier = -1.0f;
    }

    if (radians >= HALF_PI) {
        radians = PI - radians;
        multiplier *= -1.0f;
    }
    if (radians < QUARTER_PI) return _cos_impl(radians) * multiplier;
    else return _sin_impl(HALF_PI - radians) * multiplier;
}

inline constexpr float _sqrt_impl(float x, float s, float s2)
{
    return !(s < s2) ? s2 : _sqrt_impl(x, (x / s + s) / 2, s);
}

inline constexpr float sqrt(float x)
{
    if (x < 0) return NaN;
    float s = (x > 1) ? x : float(1);
    return _sqrt_impl(x, (x / s + s) / 2, s);
}

#endif // COMMON_MATH_H