#include "mat4.h"


mat4::mat4() {
    // Default vec4f constructor initializes all values to 0
}

mat4::mat4(const vec4& v, bool col_major) {
    if (!col_major) {
        this->_rows[0] = v;
        this->_rows[1] = v;
        this->_rows[2] = v;
        this->_rows[3] = v;
    } else {
        this->_rows[0] = vec4(v.x);
        this->_rows[1] = vec4(v.y);
        this->_rows[2] = vec4(v.z);
        this->_rows[3] = vec4(v.w);
    }
}

mat4::mat4(
    const vec4& v0, 
    const vec4& v1, 
    const vec4& v2, 
    const vec4& v3, 
    bool col_major
) {
    if (!col_major) {
        this->_rows[0] = v0;
        this->_rows[1] = v1;
        this->_rows[2] = v2;
        this->_rows[3] = v3;
    } else {
        this->_rows[0] = vec4(v0.x, v1.x, v2.x, v3.x);
        this->_rows[1] = vec4(v0.y, v1.y, v2.y, v3.y);
        this->_rows[2] = vec4(v0.z, v1.z, v2.z, v3.z);
        this->_rows[3] = vec4(v0.w, v1.w, v2.w, v3.w);
    }
}

mat4::mat4(
    float m00, float m01, float m02, float m03,
    float m10, float m11, float m12, float m13,
    float m20, float m21, float m22, float m23,
    float m30, float m31, float m32, float m33,
    bool col_major)
{
    if (!col_major) {
        this->_rows[0] = vec4(m00, m01, m02, m03);
        this->_rows[1] = vec4(m10, m11, m12, m13);
        this->_rows[2] = vec4(m20, m21, m22, m23);
        this->_rows[3] = vec4(m30, m31, m32, m33);
    } else {
        this->_rows[0] = vec4(m00, m10, m20, m30);
        this->_rows[1] = vec4(m01, m11, m21, m31);
        this->_rows[2] = vec4(m02, m12, m22, m32);
        this->_rows[3] = vec4(m03, m13, m23, m33);
    }
}

mat4::mat4(float diagonal) {
    this->_rows[0].x = diagonal;
    this->_rows[1].y = diagonal;
    this->_rows[2].z = diagonal;
    this->_rows[3].w = diagonal;
}

// Math operations
mat4 mat4::operator*(const mat4& rhs) const {
    return mat4(
        (_rows[0].x * rhs._rows[0].x) + (_rows[0].y * rhs._rows[1].x) + 
        (_rows[0].z * rhs._rows[2].x) + (_rows[0].w * rhs._rows[3].x),
        (_rows[0].x * rhs._rows[0].y) + (_rows[0].y * rhs._rows[1].y) + 
        (_rows[0].z * rhs._rows[2].y) + (_rows[0].w * rhs._rows[3].y),
        (_rows[0].x * rhs._rows[0].z) + (_rows[0].y * rhs._rows[1].z) + 
        (_rows[0].z * rhs._rows[2].z) + (_rows[0].w * rhs._rows[3].z),
        (_rows[0].x * rhs._rows[0].w) + (_rows[0].y * rhs._rows[1].w) + 
        (_rows[0].z * rhs._rows[2].w) + (_rows[0].w * rhs._rows[3].w),

        (_rows[1].x * rhs._rows[0].x) + (_rows[1].y * rhs._rows[1].x) + 
        (_rows[1].z * rhs._rows[2].x) + (_rows[1].w * rhs._rows[3].x),
        (_rows[1].x * rhs._rows[0].y) + (_rows[1].y * rhs._rows[1].y) + 
        (_rows[1].z * rhs._rows[2].y) + (_rows[1].w * rhs._rows[3].y),
        (_rows[1].x * rhs._rows[0].z) + (_rows[1].y * rhs._rows[1].z) + 
        (_rows[1].z * rhs._rows[2].z) + (_rows[1].w * rhs._rows[3].z),
        (_rows[1].x * rhs._rows[0].w) + (_rows[1].y * rhs._rows[1].w) + 
        (_rows[1].z * rhs._rows[2].w) + (_rows[1].w * rhs._rows[3].w),

        (_rows[2].x * rhs._rows[0].x) + (_rows[2].y * rhs._rows[1].x) + 
        (_rows[2].z * rhs._rows[2].x) + (_rows[2].w * rhs._rows[3].x),
        (_rows[2].x * rhs._rows[0].y) + (_rows[2].y * rhs._rows[1].y) + 
        (_rows[2].z * rhs._rows[2].y) + (_rows[2].w * rhs._rows[3].y),
        (_rows[2].x * rhs._rows[0].z) + (_rows[2].y * rhs._rows[1].z) + 
        (_rows[2].z * rhs._rows[2].z) + (_rows[2].w * rhs._rows[3].z),
        (_rows[2].x * rhs._rows[0].w) + (_rows[2].y * rhs._rows[1].w) + 
        (_rows[2].z * rhs._rows[2].w) + (_rows[2].w * rhs._rows[3].w),

        (_rows[3].x * rhs._rows[0].x) + (_rows[3].y * rhs._rows[1].x) + 
        (_rows[3].z * rhs._rows[2].x) + (_rows[3].w * rhs._rows[3].x),
        (_rows[3].x * rhs._rows[0].y) + (_rows[3].y * rhs._rows[1].y) + 
        (_rows[3].z * rhs._rows[2].y) + (_rows[3].w * rhs._rows[3].y),
        (_rows[3].x * rhs._rows[0].z) + (_rows[3].y * rhs._rows[1].z) + 
        (_rows[3].z * rhs._rows[2].z) + (_rows[3].w * rhs._rows[3].z),
        (_rows[3].x * rhs._rows[0].w) + (_rows[3].y * rhs._rows[1].w) + 
        (_rows[3].z * rhs._rows[2].w) + (_rows[3].w * rhs._rows[3].w)
    );
}

vec4 mat4::operator*(const vec4& rhs) const {
    return vec4(
        (_rows[0].x * rhs.x) + (_rows[0].y * rhs.y) + 
        (_rows[0].z * rhs.z) + (_rows[0].w * rhs.w),
        
        (_rows[1].x * rhs.x) + (_rows[1].y * rhs.y) + 
        (_rows[1].z * rhs.z) + (_rows[1].w * rhs.w),
        
        (_rows[2].x * rhs.x) + (_rows[2].y * rhs.y) + 
        (_rows[2].z * rhs.z) + (_rows[2].w * rhs.w),
        
        (_rows[3].x * rhs.x) + (_rows[3].y * rhs.y) + 
        (_rows[3].z * rhs.z) + (_rows[3].w * rhs.w)
    );
}

vec3 mat4::operator*(const vec3& rhs) const {
    return vec3(
        (_rows[0].x * rhs.x) + (_rows[0].y * rhs.y) + 
        (_rows[0].z * rhs.z) + (_rows[0].w * 1.0f),
        
        (_rows[1].x * rhs.x) + (_rows[1].y * rhs.y) + 
        (_rows[1].z * rhs.z) + (_rows[1].w * 1.0f),
        
        (_rows[2].x * rhs.x) + (_rows[2].y * rhs.y) + 
        (_rows[2].z * rhs.z) + (_rows[2].w * 1.0f)
    );
}

// Generator functions
mat4 mat4::rot_x(float /* in radians */ angle, bool col_major) {
    float cos_angle = cos(angle);
    float sin_angle = sin(angle);
    mat4 rotation_matrix;
    if (!col_major) {
        rotation_matrix._rows[0].x = 1.0f;
        rotation_matrix._rows[1].y = cos_angle;
        rotation_matrix._rows[1].z = sin_angle;
        rotation_matrix._rows[2].y = -sin_angle;
        rotation_matrix._rows[2].z = cos_angle;
        rotation_matrix._rows[3].w = 1.0f;
    } else {
        rotation_matrix._rows[0].x = 1.0f;
        rotation_matrix._rows[1].y = cos_angle;
        rotation_matrix._rows[1].z = -sin_angle;
        rotation_matrix._rows[2].y = sin_angle;
        rotation_matrix._rows[2].z = cos_angle;
        rotation_matrix._rows[3].w = 1.0f;
    }
    return rotation_matrix;
}

mat4 mat4::rot_y(float /* in radians */ angle, bool col_major) {
    float cos_angle = cos(angle);
    float sin_angle = sin(angle);
    mat4 rotation_matrix;
    if (!col_major) {
        rotation_matrix._rows[0].x = cos_angle;
        rotation_matrix._rows[0].z = sin_angle;
        rotation_matrix._rows[1].y = 1.0f;
        rotation_matrix._rows[2].x = -sin_angle;
        rotation_matrix._rows[2].z = cos_angle;
        rotation_matrix._rows[3].w = 1.0f;
    } else {
        rotation_matrix._rows[0].x = cos_angle;
        rotation_matrix._rows[0].z = -sin_angle;
        rotation_matrix._rows[1].y = 1.0f;
        rotation_matrix._rows[2].x = sin_angle;
        rotation_matrix._rows[2].z = cos_angle;
        rotation_matrix._rows[3].w = 1.0f;
    }
    return rotation_matrix;
}

mat4 mat4::rot_z(float /* in radians */ angle, bool col_major) {
    float cos_angle = cos(angle);
    float sin_angle = sin(angle);
    mat4 rotation_matrix;
    if (!col_major) {
        rotation_matrix._rows[0].x = cos_angle;
        rotation_matrix._rows[0].y = sin_angle;
        rotation_matrix._rows[1].x = -sin_angle;
        rotation_matrix._rows[1].y = cos_angle;
        rotation_matrix._rows[2].z = 1.0f;
        rotation_matrix._rows[3].w = 1.0f;
    } else {
        rotation_matrix._rows[0].x = cos_angle;
        rotation_matrix._rows[0].y = -sin_angle;
        rotation_matrix._rows[1].x = sin_angle;
        rotation_matrix._rows[1].y = cos_angle;
        rotation_matrix._rows[2].z = 1.0f;
        rotation_matrix._rows[3].w = 1.0f;
    }
    return rotation_matrix;
}

mat4 mat4::scale(float factor) {
    return mat4(
        factor, 0.0f,  0.0f,  0.0f,
         0.0f, factor, 0.0f,  0.0f,
         0.0f,  0.0f, factor, 0.0f,
         0.0f,  0.0f,  0.0f,  1.0f
    );
}

mat4 mat4::scale(const vec3& factors) {
    return mat4(
        factors.x,  0.0f,      0.0f,     0.0f,
          0.0f,    factors.y,  0.0f,     0.0f,
          0.0f,      0.0f,    factors.z, 0.0f,
          0.0f,      0.0f,     0.0f,     1.0f
    );
}

mat4 mat4::scale(float x, float y, float z) {
    return mat4(
         x,   0.0f, 0.0f, 0.0f,
        0.0f,  y,   0.0f, 0.0f,
        0.0f, 0.0f,  z,   0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}

mat4 mat4::scale_x(float factor) {
    return mat4(
        factor, 0.0f, 0.0f, 0.0f,
         0.0f,  1.0f, 0.0f, 0.0f,
         0.0f,  0.0f, 1.0f, 0.0f,
         0.0f,  0.0f, 0.0f, 1.0f
    );
}

mat4 mat4::scale_y(float factor) {
    return mat4(
        1.0f,  0.0f,  0.0f, 0.0f,
        0.0f, factor, 0.0f, 0.0f,
        0.0f,  0.0f,  1.0f, 0.0f,
        0.0f,  0.0f,  0.0f, 1.0f
    );
}

mat4 mat4::scale_z(float factor) {
    return mat4(
        1.0f, 0.0f,  0.0f,  0.0f,
        0.0f, 1.0f,  0.0f,  0.0f,
        0.0f, 0.0f, factor, 0.0f,
        0.0f, 0.0f,  0.0f,  1.0f
    );
}

mat4 mat4::translate(const vec3& amounts) {
    return mat4(
        1.0f, 0.0f, 0.0f, amounts.x,
        0.0f, 1.0f, 0.0f, amounts.y,
        0.0f, 0.0f, 1.0f, amounts.z,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}

mat4 mat4::translate(float x, float y, float z) {
    return mat4(
        1.0f, 0.0f, 0.0f, x,
        0.0f, 1.0f, 0.0f, y,
        0.0f, 0.0f, 1.0f, z,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}

mat4 mat4::translate_x(float amount) {
    return mat4(
        1.0f, 0.0f, 0.0f, amount,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}

mat4 mat4::translate_y(float amount) {
    return mat4(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, amount,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}

mat4 mat4::translate_z(float amount) {
    return mat4(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, amount,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}


// Element access
vec4& mat4::operator[](int ix) {
    return this->_rows[ix]; // Will segfault if access out of bounds
}

const vec4& mat4::operator[](int ix) const {
    return this->_rows[ix]; // Will segfault if access out of bounds
}


// Copy/move constructors
mat4::mat4(const mat4& other) {
    this->_rows[0] = other._rows[0];
    this->_rows[1] = other._rows[1];
    this->_rows[2] = other._rows[2];
    this->_rows[3] = other._rows[3];
}

mat4::mat4(mat4&& other) {
    this->_rows[0] = other._rows[0];
    this->_rows[1] = other._rows[1];
    this->_rows[2] = other._rows[2];
    this->_rows[3] = other._rows[3];
    other._rows[0] = vec4(0.0f);
    other._rows[1] = vec4(0.0f);
    other._rows[2] = vec4(0.0f);
    other._rows[3] = vec4(0.0f);
}

// Copy/move assignments
mat4& mat4::operator=(const mat4& rhs) {
    if (this != &rhs) {
        this->_rows[0] = rhs._rows[0];
        this->_rows[1] = rhs._rows[1];
        this->_rows[2] = rhs._rows[2];
        this->_rows[3] = rhs._rows[3];
    }
    return *this;
}

mat4& mat4::operator=(mat4&& rhs) {
    if (this != &rhs) {
        this->_rows[0] = rhs._rows[0];
        this->_rows[1] = rhs._rows[1];
        this->_rows[2] = rhs._rows[2];
        this->_rows[3] = rhs._rows[3];
        rhs._rows[0] = vec4(0.0f);
        rhs._rows[1] = vec4(0.0f);
        rhs._rows[2] = vec4(0.0f);
        rhs._rows[3] = vec4(0.0f);
    }
    return *this;
}

bool mat4::operator==(const mat4& other) {
    return (
        (_rows[0] == other._rows[0]) &&
        (_rows[1] == other._rows[1]) &&
        (_rows[2] == other._rows[2]) &&
        (_rows[3] == other._rows[3])
    );
}

bool mat4::operator!=(const mat4& other) {
    return !(
        (_rows[0] == other._rows[0]) &&
        (_rows[1] == other._rows[1]) &&
        (_rows[2] == other._rows[2]) &&
        (_rows[3] == other._rows[3])
    );
}
