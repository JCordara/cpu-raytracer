#include "mat3.h"
#include "vec3f.h"
#include "common.h"


mat3::mat3() {
    this->_values[0] = 0.0f;
    this->_values[1] = 0.0f;
    this->_values[2] = 0.0f;
    this->_values[3] = 0.0f;
    this->_values[4] = 0.0f;
    this->_values[5] = 0.0f;
    this->_values[6] = 0.0f;
    this->_values[7] = 0.0f;
    this->_values[8] = 0.0f;
}

mat3::mat3(const vec3f& v, bool col_major) {
    if (!col_major) {
        vec3f* row_ptr = nullptr;
        row_ptr = reinterpret_cast<vec3f*>(&_values[0]);
        *row_ptr = v;
        row_ptr = reinterpret_cast<vec3f*>(&_values[3]);
        *row_ptr = v;
        row_ptr = reinterpret_cast<vec3f*>(&_values[6]);
        *row_ptr = v;
    } else {
        this->_values[0] = v.x;
        this->_values[3] = v.y;
        this->_values[6] = v.z;
        this->_values[1] = v.x;
        this->_values[4] = v.y;
        this->_values[7] = v.z;
        this->_values[2] = v.x;
        this->_values[5] = v.y;
        this->_values[8] = v.z;
    }
}

mat3::mat3(const vec3f& v0, const vec3f& v1, const vec3f& v2, bool col_major) {
    if (!col_major) {
        vec3f* row_ptr = nullptr;
        row_ptr = reinterpret_cast<vec3f*>(&_values[0]);
        *row_ptr = v0;
        row_ptr = reinterpret_cast<vec3f*>(&_values[3]);
        *row_ptr = v1;
        row_ptr = reinterpret_cast<vec3f*>(&_values[6]);
        *row_ptr = v2;
    } else {
        this->_values[0] = v0.x;
        this->_values[3] = v0.y;
        this->_values[6] = v0.z;
        this->_values[1] = v1.x;
        this->_values[4] = v1.y;
        this->_values[7] = v1.z;
        this->_values[2] = v2.x;
        this->_values[5] = v2.y;
        this->_values[8] = v2.z;
    }
}

mat3::mat3(
    float m00, float m01, float m02,
    float m10, float m11, float m12,
    float m20, float m21, float m22,
    bool col_major)
{
    if (!col_major) {
        this->_values[0] = m00;
        this->_values[1] = m01;
        this->_values[2] = m02;
        this->_values[3] = m10;
        this->_values[4] = m11;
        this->_values[5] = m12;
        this->_values[6] = m20;
        this->_values[7] = m21;
        this->_values[8] = m22;
    } else {
        this->_values[0] = m00;
        this->_values[3] = m01;
        this->_values[6] = m02;
        this->_values[1] = m10;
        this->_values[4] = m11;
        this->_values[7] = m12;
        this->_values[2] = m20;
        this->_values[5] = m21;
        this->_values[8] = m22;
    }
}

mat3::mat3(float diagonal) {
    this->_values[0] = diagonal;
    this->_values[1] = 0.0f;
    this->_values[2] = 0.0f;
    this->_values[3] = 0.0f;
    this->_values[4] = diagonal;
    this->_values[5] = 0.0f;
    this->_values[6] = 0.0f;
    this->_values[7] = 0.0f;
    this->_values[8] = diagonal;
}

// Math operations
mat3 mat3::operator*(const mat3& rhs) {
    return mat3(
        (_values[0] * rhs._values[0]) + (_values[1] * rhs._values[3]) + (_values[2] * rhs._values[6]),
        (_values[0] * rhs._values[1]) + (_values[1] * rhs._values[4]) + (_values[2] * rhs._values[7]),
        (_values[0] * rhs._values[2]) + (_values[1] * rhs._values[5]) + (_values[2] * rhs._values[8]),
        (_values[3] * rhs._values[0]) + (_values[4] * rhs._values[3]) + (_values[5] * rhs._values[6]),
        (_values[3] * rhs._values[1]) + (_values[4] * rhs._values[4]) + (_values[5] * rhs._values[7]),
        (_values[3] * rhs._values[2]) + (_values[4] * rhs._values[5]) + (_values[5] * rhs._values[8]),
        (_values[6] * rhs._values[0]) + (_values[7] * rhs._values[3]) + (_values[8] * rhs._values[6]),
        (_values[6] * rhs._values[1]) + (_values[7] * rhs._values[4]) + (_values[8] * rhs._values[7]),
        (_values[6] * rhs._values[2]) + (_values[7] * rhs._values[5]) + (_values[8] * rhs._values[8])
    );
}

vec3f mat3::operator*(const vec3f& rhs) {
    return vec3f(
        (_values[0] * rhs.x) + (_values[1] * rhs.y) + (_values[2] * rhs.z),
        (_values[3] * rhs.x) + (_values[4] * rhs.y) + (_values[5] * rhs.z),
        (_values[6] * rhs.x) + (_values[7] * rhs.y) + (_values[8] * rhs.z)
    );
}

// Generator functions
mat3 mat3::rot_x(float /* in radians */ angle, bool col_major) {
    float cos_angle = cos(angle);
    float sin_angle = sin(angle);
    mat3 rotation_matrix;
    if (!col_major) {
        rotation_matrix._values[0] = 1.0f;
        rotation_matrix._values[1] = 0.0f;
        rotation_matrix._values[2] = 0.0f;
        rotation_matrix._values[3] = 0.0f;
        rotation_matrix._values[4] = cos_angle;
        rotation_matrix._values[5] = -sin_angle;
        rotation_matrix._values[6] = 0.0f;
        rotation_matrix._values[7] = sin_angle;
        rotation_matrix._values[8] = cos_angle;
    } else {
        rotation_matrix._values[0] = 1.0f;
        rotation_matrix._values[1] = 0.0f;
        rotation_matrix._values[2] = 0.0f;
        rotation_matrix._values[3] = 0.0f;
        rotation_matrix._values[4] = cos_angle;
        rotation_matrix._values[5] = sin_angle;
        rotation_matrix._values[6] = 0.0f;
        rotation_matrix._values[7] = -sin_angle;
        rotation_matrix._values[8] = cos_angle;
    }
    return rotation_matrix;
}

mat3 mat3::rot_y(float /* in radians */ angle, bool col_major) {
    float cos_angle = cos(-angle);
    float sin_angle = sin(-angle);
    mat3 rotation_matrix;
    if (!col_major) {
        rotation_matrix._values[0] = cos_angle;
        rotation_matrix._values[1] = 0.0f;
        rotation_matrix._values[2] = -sin_angle;
        rotation_matrix._values[3] = 0.0f;
        rotation_matrix._values[4] = 1.0f;
        rotation_matrix._values[5] = 0.0f;
        rotation_matrix._values[6] = sin_angle;
        rotation_matrix._values[7] = 0.0f;
        rotation_matrix._values[8] = cos_angle;
    } else {
        rotation_matrix._values[0] = cos_angle;
        rotation_matrix._values[1] = 0.0f;
        rotation_matrix._values[2] = sin_angle;
        rotation_matrix._values[3] = 0.0f;
        rotation_matrix._values[4] = 1.0f;
        rotation_matrix._values[5] = 0.0f;
        rotation_matrix._values[6] = -sin_angle;
        rotation_matrix._values[7] = 0.0f;
        rotation_matrix._values[8] = cos_angle;
    }
    return rotation_matrix;
}

mat3 mat3::rot_z(float /* in radians */ angle, bool col_major) {
    float cos_angle = cos(angle);
    float sin_angle = sin(angle);
    mat3 rotation_matrix;
    if (!col_major) {
        rotation_matrix._values[0] = cos_angle;
        rotation_matrix._values[1] = -sin_angle;
        rotation_matrix._values[2] = 0.0f;
        rotation_matrix._values[3] = cos_angle;
        rotation_matrix._values[4] = sin_angle;
        rotation_matrix._values[5] = 0.0f;
        rotation_matrix._values[6] = 0.0f;
        rotation_matrix._values[7] = 0.0f;
        rotation_matrix._values[8] = 1.0f;
    } else {
        rotation_matrix._values[0] = cos_angle;
        rotation_matrix._values[1] = sin_angle;
        rotation_matrix._values[2] = 0.0f;
        rotation_matrix._values[3] = cos_angle;
        rotation_matrix._values[4] = -sin_angle;
        rotation_matrix._values[5] = 0.0f;
        rotation_matrix._values[6] = 0.0f;
        rotation_matrix._values[7] = 0.0f;
        rotation_matrix._values[8] = 1.0f;
    }
    return rotation_matrix;
}

mat3 mat3::scale(float factor) {
    return mat3(factor);
}

mat3 mat3::scale(const vec3f& factors) {
    return mat3(
        factors.x,  0.0f,      0.0f,
          0.0f,    factors.y,  0.0f,
          0.0f,      0.0f,    factors.z
    );
}

mat3 mat3::scale_x(float factor) {
    return mat3(
        factor, 0.0f, 0.0f,
         0.0f,  0.0f, 0.0f,
         0.0f,  0.0f, 0.0f
    );
}

mat3 mat3::scale_y(float factor) {
    return mat3(
        0.0f,  0.0f,  0.0f,
        0.0f, factor, 0.0f,
        0.0f,  0.0f,  0.0f
    );
}

mat3 mat3::scale_z(float factor) {
    return mat3(
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, factor
    );
}

// Element access
vec3f mat3::operator[](int ix) const {
    if (ix == 0) return vec3(_values[0], _values[1], _values[2]);
    if (ix == 1) return vec3(_values[3], _values[4], _values[5]);
    if (ix == 2) return vec3(_values[6], _values[7], _values[8]);
    else return vec3f(NaN, NaN, NaN);
}


// Copy/move constructors
mat3::mat3(const mat3& other) {
    this->_values[0] = other._values[0];
    this->_values[1] = other._values[1];
    this->_values[2] = other._values[2];
    this->_values[3] = other._values[3];
    this->_values[4] = other._values[4];
    this->_values[5] = other._values[5];
    this->_values[6] = other._values[6];
    this->_values[7] = other._values[7];
    this->_values[8] = other._values[8];
}

mat3::mat3(mat3&& other) {
    this->_values[0] = other._values[0];
    this->_values[1] = other._values[1];
    this->_values[2] = other._values[2];
    this->_values[3] = other._values[3];
    this->_values[4] = other._values[4];
    this->_values[5] = other._values[5];
    this->_values[6] = other._values[6];
    this->_values[7] = other._values[7];
    this->_values[8] = other._values[8];

    other._values[0] = 0.0f;
    other._values[1] = 0.0f;
    other._values[2] = 0.0f;
    other._values[3] = 0.0f;
    other._values[4] = 0.0f;
    other._values[5] = 0.0f;
    other._values[6] = 0.0f;
    other._values[7] = 0.0f;
    other._values[8] = 0.0f;
}

// Copy/move assignments
mat3& mat3::operator=(const mat3& rhs) {
    if (this != &rhs) {
        this->_values[0] = rhs._values[0];
        this->_values[1] = rhs._values[1];
        this->_values[2] = rhs._values[2];
        this->_values[3] = rhs._values[3];
        this->_values[4] = rhs._values[4];
        this->_values[5] = rhs._values[5];
        this->_values[6] = rhs._values[6];
        this->_values[7] = rhs._values[7];
        this->_values[8] = rhs._values[8];
    }
    return *this;
}

mat3& mat3::operator=(mat3&& rhs) {
    if (this != &rhs) {
        this->_values[0] = rhs._values[0];
        this->_values[1] = rhs._values[1];
        this->_values[2] = rhs._values[2];
        this->_values[3] = rhs._values[3];
        this->_values[4] = rhs._values[4];
        this->_values[5] = rhs._values[5];
        this->_values[6] = rhs._values[6];
        this->_values[7] = rhs._values[7];
        this->_values[8] = rhs._values[8];
        rhs._values[0] = 0.0f;
        rhs._values[1] = 0.0f;
        rhs._values[2] = 0.0f;
        rhs._values[3] = 0.0f;
        rhs._values[4] = 0.0f;
        rhs._values[5] = 0.0f;
        rhs._values[6] = 0.0f;
        rhs._values[7] = 0.0f;
        rhs._values[8] = 0.0f;
    }
    return *this;
}


bool mat3::operator==(const mat3& other) {
    return (
        float_eq(_values[0], other._values[0])  &&
        float_eq(_values[1], other._values[1])  &&
        float_eq(_values[2], other._values[2])  &&
        float_eq(_values[3], other._values[3])  &&
        float_eq(_values[4], other._values[4])  &&
        float_eq(_values[5], other._values[5])  &&
        float_eq(_values[6], other._values[6])  &&
        float_eq(_values[7], other._values[7])  &&
        float_eq(_values[8], other._values[8])
    );
}

bool mat3::operator!=(const mat3& other) {
    return !(
        float_eq(_values[0], other._values[0])  &&
        float_eq(_values[1], other._values[1])  &&
        float_eq(_values[2], other._values[2])  &&
        float_eq(_values[3], other._values[3])  &&
        float_eq(_values[4], other._values[4])  &&
        float_eq(_values[5], other._values[5])  &&
        float_eq(_values[6], other._values[6])  &&
        float_eq(_values[7], other._values[7])  &&
        float_eq(_values[8], other._values[8])
    );
}
