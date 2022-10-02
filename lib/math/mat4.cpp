#include "mat4.h"
#include "vec4f.h"
#include "vec3f.h"
#include "common.h"


mat4::mat4() {
    this->_values[0]  = 0.0f;
    this->_values[1]  = 0.0f;
    this->_values[2]  = 0.0f;
    this->_values[3]  = 0.0f;
    this->_values[4]  = 0.0f;
    this->_values[5]  = 0.0f;
    this->_values[6]  = 0.0f;
    this->_values[7]  = 0.0f;
    this->_values[8]  = 0.0f;
    this->_values[9]  = 0.0f;
    this->_values[10] = 0.0f;
    this->_values[11] = 0.0f;
    this->_values[12] = 0.0f;
    this->_values[13] = 0.0f;
    this->_values[14] = 0.0f;
    this->_values[15] = 0.0f;
}

mat4::mat4(const vec4f& v, bool col_major) {
    if (!col_major) {
        vec4f* row_ptr = nullptr;
        row_ptr = reinterpret_cast<vec4f*>(&_values[0]);
        *row_ptr = v;
        row_ptr = reinterpret_cast<vec4f*>(&_values[4]);
        *row_ptr = v;
        row_ptr = reinterpret_cast<vec4f*>(&_values[8]);
        *row_ptr = v;
        row_ptr = reinterpret_cast<vec4f*>(&_values[12]);
        *row_ptr = v;
    } else {
        this->_values[0]  = v.x;
        this->_values[4]  = v.y;
        this->_values[8]  = v.z;
        this->_values[12] = v.w;
        this->_values[1]  = v.x;
        this->_values[5]  = v.y;
        this->_values[9]  = v.z;
        this->_values[13] = v.w;
        this->_values[2]  = v.x;
        this->_values[6]  = v.y;
        this->_values[10] = v.z;
        this->_values[14] = v.w;
        this->_values[3]  = v.x;
        this->_values[7]  = v.y;
        this->_values[11] = v.z;
        this->_values[15] = v.w;
    }
}

mat4::mat4(
    const vec4f& v0, 
    const vec4f& v1, 
    const vec4f& v2, 
    const vec4f& v3, 
    bool col_major
) {
    if (!col_major) {
        vec4f* row_ptr = nullptr;
        row_ptr = reinterpret_cast<vec4f*>(&_values[0]);
        *row_ptr = v0;
        row_ptr = reinterpret_cast<vec4f*>(&_values[4]);
        *row_ptr = v1;
        row_ptr = reinterpret_cast<vec4f*>(&_values[8]);
        *row_ptr = v2;
        row_ptr = reinterpret_cast<vec4f*>(&_values[12]);
        *row_ptr = v3;
    } else {
        this->_values[0]  = v0.x;
        this->_values[4]  = v0.y;
        this->_values[8]  = v0.z;
        this->_values[12] = v0.w;
        this->_values[1]  = v1.x;
        this->_values[5]  = v1.y;
        this->_values[9]  = v1.z;
        this->_values[13] = v1.w;
        this->_values[2]  = v2.x;
        this->_values[6]  = v2.y;
        this->_values[10] = v2.z;
        this->_values[14] = v2.w;
        this->_values[3]  = v3.x;
        this->_values[7]  = v3.y;
        this->_values[11] = v3.z;
        this->_values[15] = v3.w;
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
        this->_values[0]  = m00;
        this->_values[1]  = m01;
        this->_values[2]  = m02;
        this->_values[3]  = m03;
        this->_values[4]  = m10;
        this->_values[5]  = m11;
        this->_values[6]  = m12;
        this->_values[7]  = m13;
        this->_values[8]  = m20;
        this->_values[9]  = m21;
        this->_values[10] = m22;
        this->_values[11] = m23;
        this->_values[12] = m30;
        this->_values[13] = m31;
        this->_values[14] = m32;
        this->_values[15] = m33;
    } else {
        this->_values[0]  = m00;
        this->_values[4]  = m01;
        this->_values[8]  = m02;
        this->_values[12] = m03;
        this->_values[1]  = m10;
        this->_values[5]  = m11;
        this->_values[9]  = m12;
        this->_values[13] = m13;
        this->_values[2]  = m20;
        this->_values[6]  = m21;
        this->_values[10] = m22;
        this->_values[14] = m23;
        this->_values[3]  = m30;
        this->_values[7]  = m31;
        this->_values[11] = m32;
        this->_values[15] = m33;
    }
}

mat4::mat4(float diagonal) {
    this->_values[0]  = diagonal;
    this->_values[1]  = 0.0f;
    this->_values[2]  = 0.0f;
    this->_values[3]  = 0.0f;
    this->_values[4]  = 0.0f;
    this->_values[5]  = diagonal;
    this->_values[6]  = 0.0f;
    this->_values[7]  = 0.0f;
    this->_values[8]  = 0.0f;
    this->_values[9]  = 0.0f;
    this->_values[10] = diagonal;
    this->_values[11] = 0.0f;
    this->_values[12] = 0.0f;
    this->_values[13] = 0.0f;
    this->_values[14] = 0.0f;
    this->_values[15] = diagonal;
}

// Math operations
mat4 mat4::operator*(const mat4& rhs) {
    return mat4(
        (_values[0] * rhs._values[0])  + (_values[1] * rhs._values[4]) + 
        (_values[2] * rhs._values[8])  + (_values[3] * rhs._values[12]),
        (_values[0] * rhs._values[1])  + (_values[1] * rhs._values[5]) + 
        (_values[2] * rhs._values[9])  + (_values[3] * rhs._values[13]),
        (_values[0] * rhs._values[2])  + (_values[1] * rhs._values[6]) + 
        (_values[2] * rhs._values[10]) + (_values[3] * rhs._values[14]),
        (_values[0] * rhs._values[3])  + (_values[1] * rhs._values[7]) + 
        (_values[2] * rhs._values[11]) + (_values[3] * rhs._values[15]),

        (_values[4] * rhs._values[0])  + (_values[5] * rhs._values[4]) + 
        (_values[6] * rhs._values[8])  + (_values[7] * rhs._values[12]),
        (_values[4] * rhs._values[1])  + (_values[5] * rhs._values[5]) + 
        (_values[6] * rhs._values[9])  + (_values[7] * rhs._values[13]),
        (_values[4] * rhs._values[2])  + (_values[5] * rhs._values[6]) + 
        (_values[6] * rhs._values[10]) + (_values[7] * rhs._values[14]),
        (_values[4] * rhs._values[3])  + (_values[5] * rhs._values[7]) + 
        (_values[6] * rhs._values[11]) + (_values[7] * rhs._values[15]),

        (_values[8]  * rhs._values[0])  + (_values[9]  * rhs._values[4]) + 
        (_values[10]  * rhs._values[8]) + (_values[11] * rhs._values[12]),
        (_values[8]  * rhs._values[1])  + (_values[9]  * rhs._values[5]) + 
        (_values[10] * rhs._values[9])  + (_values[11] * rhs._values[13]),
        (_values[8]  * rhs._values[2])  + (_values[9]  * rhs._values[6]) + 
        (_values[10] * rhs._values[10]) + (_values[11] * rhs._values[14]),
        (_values[8]  * rhs._values[3])  + (_values[9]  * rhs._values[7]) + 
        (_values[10] * rhs._values[11]) + (_values[11] * rhs._values[15]),

        (_values[12] * rhs._values[0])  + (_values[13] * rhs._values[4]) + 
        (_values[14] * rhs._values[8])  + (_values[15] * rhs._values[12]),
        (_values[12] * rhs._values[1])  + (_values[13] * rhs._values[5]) + 
        (_values[14] * rhs._values[9])  + (_values[15] * rhs._values[13]),
        (_values[12] * rhs._values[2])  + (_values[13] * rhs._values[6]) + 
        (_values[14] * rhs._values[10]) + (_values[15] * rhs._values[14]),
        (_values[12] * rhs._values[3])  + (_values[13] * rhs._values[7]) + 
        (_values[14] * rhs._values[11]) + (_values[15] * rhs._values[15])
    );
}

vec4f mat4::operator*(const vec4f& rhs) {
    return vec4f(
        (_values[0]  * rhs.x) + (_values[1]  * rhs.y) + 
        (_values[2]  * rhs.z) + (_values[3]  * rhs.w),
        
        (_values[4]  * rhs.x) + (_values[5]  * rhs.y) + 
        (_values[6]  * rhs.z) + (_values[7]  * rhs.w),
        
        (_values[8]  * rhs.x) + (_values[9]  * rhs.y) + 
        (_values[10] * rhs.z) + (_values[11] * rhs.w),
        
        (_values[12] * rhs.x) + (_values[13] * rhs.y) + 
        (_values[14] * rhs.z) + (_values[15] * rhs.w)
    );
}

vec3f mat4::operator*(const vec3f& rhs) {
    return vec3f(
        (_values[0]  * rhs.x) + (_values[1]  * rhs.y) + 
        (_values[2]  * rhs.z) + (_values[3]  * 1.0f),
        
        (_values[4]  * rhs.x) + (_values[5]  * rhs.y) + 
        (_values[6]  * rhs.z) + (_values[7]  * 1.0f),
        
        (_values[8]  * rhs.x) + (_values[9]  * rhs.y) + 
        (_values[10] * rhs.z) + (_values[11] * 1.0f)
    );
}

// Generator functions
mat4 mat4::rot_x(float /* in radians */ angle, bool col_major) {
    float cos_angle = cos(angle);
    float sin_angle = sin(angle);
    mat4 rotation_matrix;
    if (!col_major) {
        rotation_matrix._values[0]  = 1.0f; // xx
        rotation_matrix._values[1]  = 0.0f; // xy
        rotation_matrix._values[2]  = 0.0f; // xz
        rotation_matrix._values[3]  = 0.0f; // xw

        rotation_matrix._values[4]  = 0.0f; // yx
        rotation_matrix._values[5]  = cos_angle; // yy
        rotation_matrix._values[6]  = sin_angle; // yz
        rotation_matrix._values[7]  = 0.0f; // yw

        rotation_matrix._values[8]  = 0.0f; // zx
        rotation_matrix._values[9]  = -sin_angle; // zy
        rotation_matrix._values[10] = cos_angle; // zz
        rotation_matrix._values[11] = 0.0f; // zw

        rotation_matrix._values[12] = 0.0f; // wx
        rotation_matrix._values[13] = 0.0f; // wy
        rotation_matrix._values[14] = 0.0f; // wz
        rotation_matrix._values[15] = 1.0f; // ww
    } else {
        rotation_matrix._values[0]  = 1.0f; // xx
        rotation_matrix._values[1]  = 0.0f; // yx
        rotation_matrix._values[2]  = 0.0f; // zx
        rotation_matrix._values[3]  = 0.0f; // wx

        rotation_matrix._values[4]  = 0.0f; // xy
        rotation_matrix._values[5]  = cos_angle; // yy
        rotation_matrix._values[6]  = -sin_angle; // zy
        rotation_matrix._values[7]  = 0.0f; // wy

        rotation_matrix._values[8]  = 0.0f; // xz
        rotation_matrix._values[9]  = sin_angle; // yz
        rotation_matrix._values[10] = cos_angle; // zz
        rotation_matrix._values[11] = 0.0f; // wz

        rotation_matrix._values[12] = 0.0f; // xw
        rotation_matrix._values[13] = 0.0f; // yw
        rotation_matrix._values[14] = 0.0f; // zw
        rotation_matrix._values[15] = 1.0f; // ww
    }
    return rotation_matrix;
}

mat4 mat4::rot_y(float /* in radians */ angle, bool col_major) {
    float cos_angle = cos(angle);
    float sin_angle = sin(angle);
    mat4 rotation_matrix;
    if (!col_major) {
        rotation_matrix._values[0]  = cos_angle; // xx
        rotation_matrix._values[1]  = 0.0f; // xy
        rotation_matrix._values[2]  = sin_angle; // xz
        rotation_matrix._values[3]  = 0.0f; // xw

        rotation_matrix._values[4]  = 0.0f; // yx
        rotation_matrix._values[5]  = 1.0f; // yy
        rotation_matrix._values[6]  = 0.0f; // yz
        rotation_matrix._values[7]  = 0.0f; // yw

        rotation_matrix._values[8]  = -sin_angle; // zx
        rotation_matrix._values[9]  = 0.0f; // zy
        rotation_matrix._values[10] = cos_angle; // zz
        rotation_matrix._values[11] = 0.0f; // zw

        rotation_matrix._values[12] = 0.0f; // wx
        rotation_matrix._values[13] = 0.0f; // wy
        rotation_matrix._values[14] = 0.0f; // wz
        rotation_matrix._values[15] = 1.0f; // ww
    } else {
        rotation_matrix._values[0]  = cos_angle; // xx
        rotation_matrix._values[1]  = 0.0f; // yx
        rotation_matrix._values[2]  = -sin_angle; // zx
        rotation_matrix._values[3]  = 0.0f; // wx

        rotation_matrix._values[4]  = 0.0f; // xy
        rotation_matrix._values[5]  = 1.0f; // yy
        rotation_matrix._values[6]  = 0.0f; // zy
        rotation_matrix._values[7]  = 0.0f; // wy

        rotation_matrix._values[8]  = sin_angle; // xz
        rotation_matrix._values[9]  = 0.0f; // yz
        rotation_matrix._values[10] = cos_angle; // zz
        rotation_matrix._values[11] = 0.0f; // wz

        rotation_matrix._values[12] = 0.0f; // xw
        rotation_matrix._values[13] = 0.0f; // yw
        rotation_matrix._values[14] = 0.0f; // zw
        rotation_matrix._values[15] = 1.0f; // ww
    }
    return rotation_matrix;
}

mat4 mat4::rot_z(float /* in radians */ angle, bool col_major) {
    float cos_angle = cos(angle);
    float sin_angle = sin(angle);
    mat4 rotation_matrix;
    if (!col_major) {
        rotation_matrix._values[0]  = cos_angle; // xx
        rotation_matrix._values[1]  = sin_angle; // xy
        rotation_matrix._values[2]  = 0.0f; // xz
        rotation_matrix._values[3]  = 0.0f; // xw

        rotation_matrix._values[4]  = -sin_angle; // yx
        rotation_matrix._values[5]  = cos_angle; // yy
        rotation_matrix._values[6]  = 0.0f; // yz
        rotation_matrix._values[7]  = 0.0f; // yw

        rotation_matrix._values[8]  = 0.0f; // zx
        rotation_matrix._values[9]  = 0.0f; // zy
        rotation_matrix._values[10] = 1.0f; // zz
        rotation_matrix._values[11] = 0.0f; // zw

        rotation_matrix._values[12] = 0.0f; // wx
        rotation_matrix._values[13] = 0.0f; // wy
        rotation_matrix._values[14] = 0.0f; // wz
        rotation_matrix._values[15] = 1.0f; // ww
    } else {
        rotation_matrix._values[0]  = cos_angle; // xx
        rotation_matrix._values[1]  = -sin_angle; // yx
        rotation_matrix._values[2]  = 0.0f; // zx
        rotation_matrix._values[3]  = 0.0f; // wx

        rotation_matrix._values[4]  = sin_angle; // xy
        rotation_matrix._values[5]  = cos_angle; // yy
        rotation_matrix._values[6]  = 0.0f; // zy
        rotation_matrix._values[7]  = 0.0f; // wy

        rotation_matrix._values[8]  = 0.0f; // xz
        rotation_matrix._values[9]  = 0.0f; // yz
        rotation_matrix._values[10] = 1.0f; // zz
        rotation_matrix._values[11] = 0.0f; // wz

        rotation_matrix._values[12] = 0.0f; // xw
        rotation_matrix._values[13] = 0.0f; // yw
        rotation_matrix._values[14] = 0.0f; // zw
        rotation_matrix._values[15] = 1.0f; // ww
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

mat4 mat4::scale(const vec3f& factors) {
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

mat4 mat4::translate(const vec3f& amounts) {
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
vec4f mat4::operator[](int ix) const {
    if (ix == 1) return vec4(_values[4],  _values[5],  _values[6],  _values[7] );
    if (ix == 0) return vec4(_values[0],  _values[1],  _values[2],  _values[3] );
    if (ix == 2) return vec4(_values[8],  _values[9],  _values[10], _values[11]);
    if (ix == 3) return vec4(_values[12], _values[13], _values[14], _values[15]);
    else return vec4f(NaN, NaN, NaN, NaN);
}


// Copy/move constructors
mat4::mat4(const mat4& other) {
    this->_values[0]  = other._values[0];
    this->_values[1]  = other._values[1];
    this->_values[2]  = other._values[2];
    this->_values[3]  = other._values[3];
    this->_values[4]  = other._values[4];
    this->_values[5]  = other._values[5];
    this->_values[6]  = other._values[6];
    this->_values[7]  = other._values[7];
    this->_values[8]  = other._values[8];
    this->_values[9]  = other._values[9];
    this->_values[10] = other._values[10];
    this->_values[11] = other._values[11];
    this->_values[12] = other._values[12];
    this->_values[13] = other._values[13];
    this->_values[14] = other._values[14];
    this->_values[15] = other._values[15];
}

mat4::mat4(mat4&& other) {
    this->_values[0]  = other._values[0];
    this->_values[1]  = other._values[1];
    this->_values[2]  = other._values[2];
    this->_values[3]  = other._values[3];
    this->_values[4]  = other._values[4];
    this->_values[5]  = other._values[5];
    this->_values[6]  = other._values[6];
    this->_values[7]  = other._values[7];
    this->_values[8]  = other._values[8];
    this->_values[9]  = other._values[9];
    this->_values[10] = other._values[10];
    this->_values[11] = other._values[11];
    this->_values[12] = other._values[12];
    this->_values[13] = other._values[13];
    this->_values[14] = other._values[14];
    this->_values[15] = other._values[15];

    other._values[0]  = 0.0f;
    other._values[1]  = 0.0f;
    other._values[2]  = 0.0f;
    other._values[3]  = 0.0f;
    other._values[4]  = 0.0f;
    other._values[5]  = 0.0f;
    other._values[6]  = 0.0f;
    other._values[7]  = 0.0f;
    other._values[8]  = 0.0f;
    other._values[9]  = 0.0f;
    other._values[10] = 0.0f;
    other._values[11] = 0.0f;
    other._values[12] = 0.0f;
    other._values[13] = 0.0f;
    other._values[14] = 0.0f;
    other._values[15] = 0.0f;
}

// Copy/move assignments
mat4& mat4::operator=(const mat4& rhs) {
    if (this != &rhs) {
        this->_values[0]  = rhs._values[0];
        this->_values[1]  = rhs._values[1];
        this->_values[2]  = rhs._values[2];
        this->_values[3]  = rhs._values[3];
        this->_values[4]  = rhs._values[4];
        this->_values[5]  = rhs._values[5];
        this->_values[6]  = rhs._values[6];
        this->_values[7]  = rhs._values[7];
        this->_values[8]  = rhs._values[8];
        this->_values[9]  = rhs._values[9];
        this->_values[10] = rhs._values[10];
        this->_values[11] = rhs._values[11];
        this->_values[12] = rhs._values[12];
        this->_values[13] = rhs._values[13];
        this->_values[14] = rhs._values[14];
        this->_values[15] = rhs._values[15];
    }
    return *this;
}

mat4& mat4::operator=(mat4&& rhs) {
    if (this != &rhs) {
        this->_values[0]  = rhs._values[0];
        this->_values[1]  = rhs._values[1];
        this->_values[2]  = rhs._values[2];
        this->_values[3]  = rhs._values[3];
        this->_values[4]  = rhs._values[4];
        this->_values[5]  = rhs._values[5];
        this->_values[6]  = rhs._values[6];
        this->_values[7]  = rhs._values[7];
        this->_values[8]  = rhs._values[8];
        this->_values[9]  = rhs._values[9];
        this->_values[10] = rhs._values[10];
        this->_values[11] = rhs._values[11];
        this->_values[12] = rhs._values[12];
        this->_values[13] = rhs._values[13];
        this->_values[14] = rhs._values[14];
        this->_values[15] = rhs._values[15];
        
        rhs._values[0]  = 0.0f;
        rhs._values[1]  = 0.0f;
        rhs._values[2]  = 0.0f;
        rhs._values[3]  = 0.0f;
        rhs._values[4]  = 0.0f;
        rhs._values[5]  = 0.0f;
        rhs._values[6]  = 0.0f;
        rhs._values[7]  = 0.0f;
        rhs._values[8]  = 0.0f;
        rhs._values[9]  = 0.0f;
        rhs._values[10] = 0.0f;
        rhs._values[11] = 0.0f;
        rhs._values[12] = 0.0f;
        rhs._values[13] = 0.0f;
        rhs._values[14] = 0.0f;
        rhs._values[15] = 0.0f;
    }
    return *this;
}

bool mat4::operator==(const mat4& other) {
    return (
        float_eq(_values[0],  other._values[0])   &&
        float_eq(_values[1],  other._values[1])   &&
        float_eq(_values[2],  other._values[2])   &&
        float_eq(_values[3],  other._values[3])   &&
        float_eq(_values[4],  other._values[4])   &&
        float_eq(_values[5],  other._values[5])   &&
        float_eq(_values[6],  other._values[6])   &&
        float_eq(_values[7],  other._values[7])   &&
        float_eq(_values[8],  other._values[8])   &&
        float_eq(_values[9],  other._values[9])   &&
        float_eq(_values[10], other._values[10])  &&
        float_eq(_values[11], other._values[11])  &&
        float_eq(_values[12], other._values[12])  &&
        float_eq(_values[13], other._values[13])  &&
        float_eq(_values[14], other._values[14])  &&
        float_eq(_values[15], other._values[15])
    );
}

bool mat4::operator!=(const mat4& other) {
    return !(
        float_eq(_values[0],  other._values[0])   &&
        float_eq(_values[1],  other._values[1])   &&
        float_eq(_values[2],  other._values[2])   &&
        float_eq(_values[3],  other._values[3])   &&
        float_eq(_values[4],  other._values[4])   &&
        float_eq(_values[5],  other._values[5])   &&
        float_eq(_values[6],  other._values[6])   &&
        float_eq(_values[7],  other._values[7])   &&
        float_eq(_values[8],  other._values[8])   &&
        float_eq(_values[9],  other._values[9])   &&
        float_eq(_values[10], other._values[10])  &&
        float_eq(_values[11], other._values[11])  &&
        float_eq(_values[12], other._values[12])  &&
        float_eq(_values[13], other._values[13])  &&
        float_eq(_values[14], other._values[14])  &&
        float_eq(_values[15], other._values[15])
    );
}
