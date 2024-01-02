#ifndef COMMON_MATH_H
#define COMMON_MATH_H

#define NaN           1.175494351e-38f
#define EPSILON       1.0000000000e-4f
#define QUARTER_PI    0.7853981633974f
#define HALF_PI       1.5707963267948f
#define PI            3.1415926535897f
#define THREE_HALF_PI 4.7123889803846f
#define TWO_PI        6.2831853071795f

#define FLOAT_MAX     3.4028234660e38f

constexpr double _rad_to_deg_ratio = 180.0f / PI;
constexpr double _deg_to_rad_ratio = PI / 180.0f;
constexpr double _2_fact_inv = 1.0f / (2.0f);
constexpr double _3_fact_inv = 1.0f / (3.0f * 2.0f);
constexpr double _4_fact_inv = 1.0f / (4.0f * 3.0f * 2.0f);
constexpr double _5_fact_inv = 1.0f / (5.0f * 4.0f * 3.0f * 2.0f);
constexpr double _6_fact_inv = 1.0f / (6.0f * 5.0f * 4.0f * 3.0f * 2.0f);
constexpr double _7_fact_inv = 1.0f / (7.0f * 6.0f * 5.0f * 4.0f * 3.0f * 2.0f);

constexpr double nan = NaN;

inline constexpr double lerp(double a, double b, double t) {
    return ((1.0f - t) * a) + (t * b);
}

inline constexpr double max(double a, double b) {
    return a > b ? a : b;
}

inline constexpr double min(double a, double b) {
    return a < b ? a : b;
}

inline constexpr double abs(double x) {
    return x >= 0 ? x : -x;
}

inline constexpr double radians(double degrees) {
    return _deg_to_rad_ratio * degrees;
}

inline constexpr double degrees(double radians) {
    return _rad_to_deg_ratio * radians;
}

inline bool float_eq(const double& x, const double& y) {
    return (x < (y + 0.0001f)) && (x > (y - 0.0001f));
}

inline constexpr double _sin_impl(double radians) {
    double pow3 = radians * radians * radians;
    double pow5 = pow3 * radians * radians;
    double pow7 = pow5 * radians * radians;
    return radians - (pow3 * _3_fact_inv) + (pow5 * _5_fact_inv) - (pow7 * _7_fact_inv);
}

inline constexpr double _cos_impl(double radians) {
    double pow2 = radians * radians;
    double pow4 = pow2 * radians * radians;
    double pow6 = pow4 * radians * radians;
    return 1 - (pow2 * _2_fact_inv) + (pow4 * _4_fact_inv) - (pow6 * _6_fact_inv);
}

inline double sin(double radians) {
    // Get into 0 - 360 degree range
    while (radians >= TWO_PI) radians -= TWO_PI;
    while (radians < 0) radians += TWO_PI;

    if      (abs(radians - 0.0f) < EPSILON)          return  0.0f;
    else if (abs(radians - HALF_PI) < EPSILON)       return  1.0f;
    else if (abs(radians - PI) < EPSILON)            return  0.0f;
    else if (abs(radians - THREE_HALF_PI) < EPSILON) return -1.0f;

    // Use vertical symmetry if in quadrants 3 or 4
    double multiplier = 1.0f;
    if (radians >= PI) {
        radians -= PI;
        multiplier = -1.0f;
    }

    if (radians >= HALF_PI) radians = PI - radians;
    if (radians < QUARTER_PI) return _sin_impl(radians) * multiplier;
    else return _cos_impl(HALF_PI - radians) * multiplier;
}

inline constexpr double cos(double radians) {
    // Get into 0 - 360 degree range
    while (radians >= TWO_PI) radians -= TWO_PI;
    while (radians < 0) radians += TWO_PI;

    if      (abs(radians - 0.0f) < EPSILON)           return  1.0f;
    else if (abs(radians - HALF_PI) < EPSILON)        return  0.0f;
    else if (abs(radians - PI) < EPSILON)             return -1.0f;
    else if (abs(radians - THREE_HALF_PI) < EPSILON)  return  0.0f;

    // Use vertical symmetry if in quadrants 3 or 4
    double multiplier = 1.0f;
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

inline constexpr double _sqrt_impl(double x, double s, double s2)
{
    return !(s < s2) ? s2 : _sqrt_impl(x, (x / s + s) / 2, s);
}

inline constexpr double sqrt(double x)
{
    if (x < 0) return NaN;
    double s = (x > 1) ? x : double(1);
    return _sqrt_impl(x, (x / s + s) / 2, s);
}

#endif // COMMON_MATH_H