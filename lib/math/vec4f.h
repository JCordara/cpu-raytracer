#ifndef VEC_4_F_H
#define VEC_4_F_H

// vec4 as convenience alias
class vec4f;
typedef vec4f vec4;

class vec4f {
public:

    float x;
    float y;
    float z;
    float w;
        
    float dot(const vec4f& rhs) const;
    float dot(const vec4f&& rhs) const;
    vec4f cross(const vec4f& rhs) const;
    vec4f cross(const vec4f&& rhs) const;
    vec4f reflect(const vec4f& normal) const;
    vec4f reflect(const vec4f&& normal) const;

    float magnitude() const;
    float magnitude2() const;
    vec4f normalize() const;
    vec4f operator-() const;

    vec4f();
    vec4f(float init_value);
    vec4f(int   init_value);
    vec4f(float x, float y, float z, float w);
    vec4f(int   x, int   y, int   z, int   w);
    vec4f(float xyzw[4]);
    vec4f(int   xyzw[4]);

    // Element access
    float& operator[](int ix);
    const float& operator[](int ix) const;

    // Copy/move constructors
    vec4f(const vec4f &other);
    vec4f(vec4f&& other) = default;

    // Copy/move assignment operators
    vec4f& operator=(const vec4f& rhs);
    vec4f& operator=(vec4f&& rhs);

    bool operator==(const vec4f& rhs);
    bool operator!=(const vec4f& rhs);
};

vec4f operator+(vec4f const& v, float scalar);
vec4f operator+(vec4f const& v, int   scalar);
vec4f operator+(float scalar,   vec4f const& v);
vec4f operator+(int   scalar,   vec4f const& v);

vec4f operator-(vec4f const& v, float scalar);
vec4f operator-(vec4f const& v, int   scalar);
vec4f operator-(float scalar,   vec4f const& v);
vec4f operator-(int   scalar,   vec4f const& v);

vec4f operator*(vec4f const& v, float scalar);
vec4f operator*(vec4f const& v, int   scalar);
vec4f operator*(float scalar,   vec4f const& v);
vec4f operator*(int   scalar,   vec4f const& v);

vec4f operator/(vec4f const& v, float scalar);
vec4f operator/(vec4f const& v, int   scalar);
vec4f operator/(float scalar,   vec4f const& v);
vec4f operator/(int   scalar,   vec4f const& v);

vec4f operator+(const vec4f& lhs, const vec4f& rhs);
vec4f operator-(const vec4f& lhs, const vec4f& rhs);

#endif // VEC_4_F_H
