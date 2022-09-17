#ifndef MAT_3_H
#define MAT_3_H

class vec3f;

class mat3 {
private:
    float _values[9];
public:
    
    mat3();
    mat3(const vec3f& v, bool col_major=false);
    mat3(const vec3f& v0, const vec3f& v1, const vec3f& v2, bool col_major=false);

    mat3(
        float m00, float m01, float m02,
        float m10, float m11, float m12,
        float m20, float m21, float m22
    );
    mat3(float diagonal);

    // Math operations
    mat3  operator*(const mat3&  rhs);
    // Vector multiplication (only allow mat * vec, not vec * mat)
    vec3f operator*(const vec3f& rhs);
    
    // Copy/move constructors
    mat3(const mat3& other);
    mat3(mat3&& other);

    // Copy/move assignments
    mat3& operator=(const mat3& rhs);
    mat3& operator=(mat3&& rhs);

    // Rule of 5
    ~mat3() = default;

};

#endif // MAT_3_H
