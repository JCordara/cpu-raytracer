#ifndef MAT_4_H
#define MAT_4_H

class vec3f;
class vec4f;

class mat4 {
private:
    float _values[16];
public:
    
    mat4();
    mat4(const vec4f& v, bool col_major=false);
    mat4(const vec4f& v0, const vec4f& v1, const vec4f& v2, const vec4f& v3, bool col_major=false);
    mat4(
        float m00, float m01, float m02, float m03,
        float m10, float m11, float m12, float m13,
        float m20, float m21, float m22, float m23,
        float m30, float m31, float m32, float m33,
        bool col_major=false
    );
    mat4(float diagonal);

    // Math operations
    mat4  operator*(const mat4&  rhs) const;
    // Vector multiplication (only allow mat * vec, not vec * mat)
    vec4f operator*(const vec4f& rhs) const;
    vec3f operator*(const vec3f& rhs) const;
    
    // Generator functions
    static mat4 rot_x(float /* in radians */ angle, bool col_major=false);
    static mat4 rot_y(float /* in radians */ angle, bool col_major=false);
    static mat4 rot_z(float /* in radians */ angle, bool col_major=false);
    static mat4 scale(float factor);
    static mat4 scale(const vec3f& factors);
    static mat4 scale(float x, float y, float z);
    static mat4 scale_x(float factor);
    static mat4 scale_y(float factor);
    static mat4 scale_z(float factor);
    static mat4 translate(const vec3f& amounts);
    static mat4 translate(float x, float y, float z);
    static mat4 translate_x(float amount);
    static mat4 translate_y(float amount);
    static mat4 translate_z(float amount);

    // Element access
    vec4f operator[](int ix) const;

    bool operator==(const mat4& other);
    bool operator!=(const mat4& other);

    // Copy/move constructors
    mat4(const mat4& other);
    mat4(mat4&& other);

    // Copy/move assignments
    mat4& operator=(const mat4& rhs);
    mat4& operator=(mat4&& rhs);

    // Rule of 5
    ~mat4() = default;

};

#endif // MAT_4_H
