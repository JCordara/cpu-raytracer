#ifndef VEC_3_F_H
#define VEC_3_F_H

// vec3 as convenience alias
class vec3f;
typedef vec3f vec3;

class vec3f {
public:

    float x;
    float y;
    float z;
        
    float dot(const vec3f& rhs) const;
    float dot(const vec3f&& rhs) const;
    vec3f cross(const vec3f& rhs) const;
    vec3f cross(const vec3f&& rhs) const;
    vec3f reflect(const vec3f& normal) const;
    vec3f reflect(const vec3f&& normal) const;

    float magnitude() const;
    float magnitude2() const;
    vec3f normalize() const;
    vec3f operator-() const;

    vec3f();
    vec3f(float init_value);
    vec3f(int   init_value);
    vec3f(float x, float y, float z);
    vec3f(int   x, int   y, int   z);
    vec3f(float xyz[3]);
    vec3f(int   xyz[3]);

    // Element access
    float operator[](int ix);

    // Copy/move constructors
    vec3f(const vec3f &other);
    vec3f(vec3f&& other) = default;

    // Copy/move assignment operators
    vec3f& operator=(const vec3f& rhs);
    vec3f& operator=(vec3f&& rhs);

    bool operator==(const vec3f& rhs);
    bool operator!=(const vec3f& rhs);
};

vec3f operator+(vec3f const& v, float scalar);
vec3f operator+(vec3f const& v, int   scalar);
vec3f operator+(float scalar,   vec3f const& v);
vec3f operator+(int   scalar,   vec3f const& v);

vec3f operator-(vec3f const& v, float scalar);
vec3f operator-(vec3f const& v, int   scalar);
vec3f operator-(float scalar,   vec3f const& v);
vec3f operator-(int   scalar,   vec3f const& v);

vec3f operator*(vec3f const& v, float scalar);
vec3f operator*(vec3f const& v, int   scalar);
vec3f operator*(float scalar,   vec3f const& v);
vec3f operator*(int   scalar,   vec3f const& v);

vec3f operator/(vec3f const& v, float scalar);
vec3f operator/(vec3f const& v, int   scalar);
vec3f operator/(float scalar,   vec3f const& v);
vec3f operator/(int   scalar,   vec3f const& v);

vec3f operator+(const vec3f& lhs, const vec3f& rhs);
vec3f operator-(const vec3f& lhs, const vec3f& rhs);

#endif // VEC_3_F_H
