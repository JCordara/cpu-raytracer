#ifndef COMMON_MATH_H
#define COMMON_MATH_H

#define NaN 1.175494351e-38f

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