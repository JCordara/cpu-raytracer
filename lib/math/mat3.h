#ifndef MAT_3_H
#define MAT_3_H

#include "vec3f.h"
#include "common.h"

class mat3 {
private:
    vec3 _rows[3];
public:
    
    mat3();
    mat3(const vec3& v, bool col_major=false);
    mat3(const vec3& v0, const vec3& v1, const vec3& v2, bool col_major=false);

    mat3(
        float m00, float m01, float m02,
        float m10, float m11, float m12,
        float m20, float m21, float m22,
        bool col_major=false
    );
    mat3(float diagonal);

    // Math operations
    mat3 operator*(const mat3&  rhs);
    // Vector multiplication (only allow mat * vec, not vec * mat)
    vec3 operator*(const vec3& rhs);
    
    // Generator functions
    static mat3 rot_x(float /* in radians */ angle, bool col_major=false);
    static mat3 rot_y(float /* in radians */ angle, bool col_major=false);
    static mat3 rot_z(float /* in radians */ angle, bool col_major=false);
    static mat3 scale(float factor);
    static mat3 scale(const vec3& factors);
    static mat3 scale_x(float factor);
    static mat3 scale_y(float factor);
    static mat3 scale_z(float factor);

    // Element access
    vec3& operator[](int ix);
    const vec3& operator[](int ix) const;

    // Copy/move constructors
    mat3(const mat3& other);
    mat3(mat3&& other);

    // Copy/move assignments
    mat3& operator=(const mat3& rhs);
    mat3& operator=(mat3&& rhs);

    bool operator==(const mat3& other);
    bool operator!=(const mat3& other);

    // Rule of 5
    ~mat3() = default;

};

#endif // MAT_3_H
