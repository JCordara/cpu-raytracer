#include "mat3.h"


mat3::mat3() {
    // Default vec3f constructor initializes all values to 0
}

mat3::mat3(const vec3& v, bool col_major) {
    if (!col_major) {
        this->_rows[0] = v;
        this->_rows[1] = v;
        this->_rows[2] = v;
    } else {
        this->_rows[0] = vec3(v.x);
        this->_rows[1] = vec3(v.y);
        this->_rows[2] = vec3(v.z);
    }
}

mat3::mat3(const vec3& v0, const vec3& v1, const vec3& v2, bool col_major) {
    if (!col_major) {
        this->_rows[0] = v0;
        this->_rows[1] = v1;
        this->_rows[2] = v2;
    } else {
        this->_rows[0] = vec3(v0.x, v1.x, v2.x);
        this->_rows[1] = vec3(v0.y, v1.y, v2.y);
        this->_rows[2] = vec3(v0.z, v1.z, v2.z);
    }
}

mat3::mat3(
    float m00, float m01, float m02,
    float m10, float m11, float m12,
    float m20, float m21, float m22,
    bool col_major)
{
    if (!col_major) {
        this->_rows[0] = vec3(m00, m01, m02);
        this->_rows[1] = vec3(m10, m11, m12);
        this->_rows[2] = vec3(m20, m21, m22);
    } else {
        this->_rows[0] = vec3(m00, m10, m20);
        this->_rows[1] = vec3(m01, m11, m21);
        this->_rows[2] = vec3(m02, m12, m22);
    }
}

mat3::mat3(float diagonal) {
    this->_rows[0].x = diagonal;
    this->_rows[1].y = diagonal;
    this->_rows[2].z = diagonal;
}

// Math operations
mat3 mat3::operator*(const mat3& rhs) {
    return mat3(
        (_rows[0].x * rhs._rows[0].x) + 
        (_rows[0].y * rhs._rows[1].x) + 
        (_rows[0].z * rhs._rows[2].x),
        (_rows[0].x * rhs._rows[0].y) + 
        (_rows[0].y * rhs._rows[1].y) + 
        (_rows[0].z * rhs._rows[2].y),
        (_rows[0].x * rhs._rows[0].z) + 
        (_rows[0].y * rhs._rows[1].z) + 
        (_rows[0].z * rhs._rows[2].z),

        (_rows[1].x * rhs._rows[0].x) + 
        (_rows[1].y * rhs._rows[1].x) + 
        (_rows[1].z * rhs._rows[2].x),
        (_rows[1].x * rhs._rows[0].y) + 
        (_rows[1].y * rhs._rows[1].y) + 
        (_rows[1].z * rhs._rows[2].y),
        (_rows[1].x * rhs._rows[0].z) + 
        (_rows[1].y * rhs._rows[1].z) + 
        (_rows[1].z * rhs._rows[2].z),

        (_rows[2].x * rhs._rows[0].x) + 
        (_rows[2].y * rhs._rows[1].x) + 
        (_rows[2].z * rhs._rows[2].x),
        (_rows[2].x * rhs._rows[0].y) + 
        (_rows[2].y * rhs._rows[1].y) + 
        (_rows[2].z * rhs._rows[2].y),
        (_rows[2].x * rhs._rows[0].z) + 
        (_rows[2].y * rhs._rows[1].z) + 
        (_rows[2].z * rhs._rows[2].z)
    );
}

vec3 mat3::operator*(const vec3& rhs) {
    return vec3(
        (_rows[0].x * rhs.x) + (_rows[0].y * rhs.y) + (_rows[0].z * rhs.z),
        (_rows[1].x * rhs.x) + (_rows[1].y * rhs.y) + (_rows[1].z * rhs.z),
        (_rows[2].x * rhs.x) + (_rows[2].y * rhs.y) + (_rows[2].z * rhs.z)
    );
}

// Generator functions
mat3 mat3::rot_x(float /* in radians */ angle, bool col_major) {
    float cos_angle = cos(angle);
    float sin_angle = sin(angle);
    mat3 rotation_matrix;
    if (!col_major) {
        rotation_matrix._rows[0].x = 1.0f;
        rotation_matrix._rows[1].y = cos_angle;
        rotation_matrix._rows[1].z = sin_angle;
        rotation_matrix._rows[2].y = -sin_angle;
        rotation_matrix._rows[2].z = cos_angle;
    } else {
        rotation_matrix._rows[0].x = 1.0f;
        rotation_matrix._rows[1].y = cos_angle;
        rotation_matrix._rows[1].z = -sin_angle;
        rotation_matrix._rows[2].y = sin_angle;
        rotation_matrix._rows[2].z = cos_angle;
    }
    return rotation_matrix;
}

mat3 mat3::rot_y(float /* in radians */ angle, bool col_major) {
    float cos_angle = cos(angle);
    float sin_angle = sin(angle);
    mat3 rotation_matrix;
    if (!col_major) {
        rotation_matrix._rows[0].x = cos_angle;
        rotation_matrix._rows[0].z = sin_angle;
        rotation_matrix._rows[1].y = 1.0f;
        rotation_matrix._rows[2].x = -sin_angle;
        rotation_matrix._rows[2].z = cos_angle;
    } else {
        rotation_matrix._rows[0].x = cos_angle;
        rotation_matrix._rows[0].z = -sin_angle;
        rotation_matrix._rows[1].y = 1.0f;
        rotation_matrix._rows[2].x = sin_angle;
        rotation_matrix._rows[2].z = cos_angle;
    }
    return rotation_matrix;
}

mat3 mat3::rot_z(float /* in radians */ angle, bool col_major) {
    float cos_angle = cos(angle);
    float sin_angle = sin(angle);
    mat3 rotation_matrix;
    if (!col_major) {
        rotation_matrix._rows[0].x = cos_angle;
        rotation_matrix._rows[0].y = sin_angle;
        rotation_matrix._rows[1].x = -sin_angle;
        rotation_matrix._rows[1].y = cos_angle;
        rotation_matrix._rows[2].z = 1.0f;
    } else {
        rotation_matrix._rows[0].x = cos_angle;
        rotation_matrix._rows[0].y = -sin_angle;
        rotation_matrix._rows[1].x = sin_angle;
        rotation_matrix._rows[1].y = cos_angle;
        rotation_matrix._rows[2].z = 1.0f;
    }
    return rotation_matrix;
}

mat3 mat3::scale(float factor) {
    return mat3(factor);
}

mat3 mat3::scale(float x, float y, float z) {
    return mat3(
         x,   0.0f, 0.0f,
        0.0f,  y,   0.0f,
        0.0f, 0.0f,  z
    );
}

mat3 mat3::scale(const vec3& factors) {
    return mat3(
        factors.x,  0.0f,      0.0f,
          0.0f,    factors.y,  0.0f,
          0.0f,      0.0f,    factors.z
    );
}

mat3 mat3::scale_x(float factor) {
    return mat3(
        factor, 0.0f, 0.0f,
         0.0f,  1.0f, 0.0f,
         0.0f,  0.0f, 1.0f
    );
}

mat3 mat3::scale_y(float factor) {
    return mat3(
        1.0f,  0.0f,  0.0f,
        0.0f, factor, 0.0f,
        0.0f,  0.0f,  1.0f
    );
}

mat3 mat3::scale_z(float factor) {
    return mat3(
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, factor
    );
}

// Element access
vec3& mat3::operator[](int ix) {
    return this->_rows[ix]; // Will segfault if access out of bounds
}

const vec3& mat3::operator[](int ix) const {
    return this->_rows[ix]; // Will segfault if access out of bounds
}


// Copy/move constructors
mat3::mat3(const mat3& other) {
    this->_rows[0] = other._rows[0];
    this->_rows[1] = other._rows[1];
    this->_rows[2] = other._rows[2];
}

mat3::mat3(mat3&& other) {
    this->_rows[0] = other._rows[0];
    this->_rows[1] = other._rows[1];
    this->_rows[2] = other._rows[2];
    other._rows[0] = vec3(0.0f);
    other._rows[1] = vec3(0.0f);
    other._rows[2] = vec3(0.0f);
}

// Copy/move assignments
mat3& mat3::operator=(const mat3& rhs) {
    if (this != &rhs) {
        this->_rows[0] = rhs._rows[0];
        this->_rows[1] = rhs._rows[1];
        this->_rows[2] = rhs._rows[2];
    }
    return *this;
}

mat3& mat3::operator=(mat3&& rhs) {
    if (this != &rhs) {
        this->_rows[0] = rhs._rows[0];
        this->_rows[1] = rhs._rows[1];
        this->_rows[2] = rhs._rows[2];
        rhs._rows[0] = vec3(0.0f);
        rhs._rows[1] = vec3(0.0f);
        rhs._rows[2] = vec3(0.0f);
    }
    return *this;
}


bool mat3::operator==(const mat3& other) {
    return (
        (_rows[0] == other._rows[0]) &&
        (_rows[1] == other._rows[1]) &&
        (_rows[2] == other._rows[2])
    );
}

bool mat3::operator!=(const mat3& other) {
    return !(
        (_rows[0] == other._rows[0]) &&
        (_rows[1] == other._rows[1]) &&
        (_rows[2] == other._rows[2])
    );
}
