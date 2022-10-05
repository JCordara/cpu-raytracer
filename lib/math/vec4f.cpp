#include "vec4f.h"
#include "common.h"

// Binary operations between vectors

vec4f operator+(const vec4f& lhs, const vec4f& rhs) {
    return vec4f(
        lhs.x + rhs.x,
        lhs.y + rhs.y,
        lhs.z + rhs.z,
        lhs.w + rhs.w
    );
}

vec4f operator-(const vec4f& lhs, const vec4f& rhs) {
    return vec4f(
        lhs.x - rhs.x,
        lhs.y - rhs.y,
        lhs.z - rhs.z,
        lhs.w - rhs.w
    );
}

float vec4f::dot(const vec4f& rhs) const {
    return (
        (this->x * rhs.x) + 
        (this->y * rhs.y) + 
        (this->z * rhs.z) +
        (this->w * rhs.w)
    );
}

float vec4f::dot(const vec4f&& rhs) const {
    return (
        (this->x * rhs.x) + 
        (this->y * rhs.y) + 
        (this->z * rhs.z) +
        (this->w * rhs.w)
    );
}

vec4f vec4f::cross(const vec4f& rhs) const {
    return vec4f(
        (this->y * rhs.z) - (this->z * rhs.y),
        (this->z * rhs.x) - (this->x * rhs.z),
        (this->x * rhs.y) - (this->y * rhs.x),
        this->w
    );
}

vec4f vec4f::cross(const vec4f&& rhs) const {
    return vec4f(
        (this->y * rhs.z) - (this->z * rhs.y),
        (this->z * rhs.x) - (this->x * rhs.z),
        (this->x * rhs.y) - (this->y * rhs.x),
        this->w
    );
}

vec4f vec4f::reflect(const vec4f& normal) const {
    vec4f n = normal.normalize();
    float dp = this->dot(n);
    vec4f operand = 2 * dp * n;
    return *this - operand;
}

vec4f vec4f::reflect(const vec4f&& normal) const {
    vec4f n = normal.normalize();
    float dp = this->dot(n);
    vec4f operand = 2 * dp * n;
    return *this - operand;
}


// Binary operations with scalar types

// Addition
vec4f operator+(vec4f const& v, float scalar) {
    return vec4f(
        v.x + scalar,
        v.y + scalar,
        v.z + scalar,
        v.w + scalar
    );
}

vec4f operator+(float scalar, vec4f const& v) {
    return vec4f(
        v.x + scalar,
        v.y + scalar,
        v.z + scalar,
        v.w + scalar
    );
}

vec4f operator+(vec4f const& v, int scalar) {
    float f_scalar = static_cast<float>(scalar);
    return vec4f(
        v.x + scalar,
        v.y + scalar,
        v.z + scalar,
        v.w + scalar
    );
}

vec4f operator+(int scalar, vec4f const& v) {
    float f_scalar = static_cast<float>(scalar);
    return vec4f(
        f_scalar + v.x,
        f_scalar + v.y,
        f_scalar + v.z,
        f_scalar + v.w
    );
}

// Subtraction
vec4f operator-(vec4f const& v, float scalar) {
    return vec4f(
        v.x - scalar,
        v.y - scalar,
        v.z - scalar,
        v.w - scalar
    );
}

vec4f operator-(float scalar, vec4f const& v) {
    return vec4f(
        scalar - v.x,
        scalar - v.y,
        scalar - v.z,
        scalar - v.w
    );
}

vec4f operator-(vec4f const& v, int scalar) {
    float f_scalar = static_cast<float>(scalar);
    return vec4f(
        v.x - f_scalar,
        v.y - f_scalar,
        v.z - f_scalar,
        v.w - f_scalar
    );
}

vec4f operator-(int scalar, vec4f const& v) {
    float f_scalar = static_cast<float>(scalar);
    return vec4f(
        f_scalar - v.x,
        f_scalar - v.y,
        f_scalar - v.z,
        f_scalar - v.w
    );
}

// Multiplication
vec4f operator*(vec4f const& v, float scalar) {
    return vec4f(
        v.x * scalar,
        v.y * scalar,
        v.z * scalar,
        v.w * scalar
    );
}

vec4f operator*(float scalar, vec4f const& v) {
    return vec4f(
        scalar * v.x,
        scalar * v.y,
        scalar * v.z,
        scalar * v.w
    );
}

vec4f operator*(vec4f const& v, int scalar) {
    float f_scalar = static_cast<float>(scalar);
    return vec4f(
        v.x * f_scalar,
        v.y * f_scalar,
        v.z * f_scalar,
        v.w * f_scalar
    );
}

vec4f operator*(int scalar, vec4f const& v) {
    float f_scalar = static_cast<float>(scalar);
    return vec4f(
        f_scalar * v.x,
        f_scalar * v.y,
        f_scalar * v.z,
        f_scalar * v.w
    );
}

// Division
vec4f operator/(vec4f const& v, float scalar) {
    return vec4f(
        v.x / scalar,
        v.y / scalar,
        v.z / scalar,
        v.w / scalar
    );
}

vec4f operator/(float scalar, vec4f const& v) {
    return vec4f(
        scalar / v.x,
        scalar / v.y,
        scalar / v.z,
        scalar / v.w
    );
}

vec4f operator/(vec4f const& v, int scalar) {
    float f_scalar = static_cast<float>(scalar);
    return vec4f(
        v.x / f_scalar,
        v.y / f_scalar,
        v.z / f_scalar,
        v.w / f_scalar
    );
}

vec4f operator/(int scalar, vec4f const& v) {
    float f_scalar = static_cast<float>(scalar);
    return vec4f(
        f_scalar / v.x,
        f_scalar / v.y,
        f_scalar / v.z,
        f_scalar / v.w
    );
}


// Unary vector operations

float vec4f::magnitude() const {
    // Apparently this is the fasted sqrt algorithm out there
    return sqrt(
        (this->x * this->x) +
        (this->y * this->y) +
        (this->z * this->z) +
        (this->w * this->w)
    );
}

float vec4f::magnitude2() const {
    // Apparently this is the fasted sqrt algorithm out there
    return (
        (this->x * this->x) +
        (this->y * this->y) +
        (this->z * this->z) +
        (this->w * this->w)
    );
}

vec4f vec4f::normalize() const {
    if (this->x == 0 && this->y == 0 && this->z == 0) return vec4f();
    float magnitude = this->magnitude();
    return vec4f(
        this->x / magnitude, 
        this->y / magnitude, 
        this->z / magnitude,
        this->w / magnitude
    );
}

vec4f vec4f::operator-() const {
    return vec4f(
        -this->x,
        -this->y,
        -this->z,
        -this->w
    );
}


// Element access

float& vec4f::operator[](int ix) {
    static float nan = NaN;
    if (ix == 0) return x;
    if (ix == 1) return y;
    if (ix == 2) return z;
    if (ix == 3) return w;
    else return nan;
}

const float& vec4f::operator[](int ix) const {
    static float nan = NaN;
    if (ix == 0) return x;
    if (ix == 1) return y;
    if (ix == 2) return z;
    if (ix == 3) return w;
    else return nan;
}


// Constructors

vec4f::vec4f() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
    this->w = 0;
}

vec4f::vec4f(float init_value) {
    this->x = init_value;
    this->y = init_value;
    this->z = init_value;
    this->w = init_value;
}

vec4f::vec4f(int init_value) : vec4f(static_cast<float>(init_value)) {}

vec4f::vec4f(float x, float y, float z, float w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

vec4f::vec4f(int x, int y, int z, int w) : 
    vec4f(
        static_cast<float>(x),
        static_cast<float>(y),
        static_cast<float>(z),
        static_cast<float>(w)
    ) 
{}


vec4f::vec4f(float xyzw[4]) {
    this->x = xyzw[0];
    this->y = xyzw[1];
    this->z = xyzw[2];
    this->z = xyzw[3];
}

vec4f::vec4f(int xyzw[4]) : 
    vec4f(
        static_cast<float>(xyzw[0]),
        static_cast<float>(xyzw[1]),
        static_cast<float>(xyzw[2]),
        static_cast<float>(xyzw[3])
    ) 
{}

vec4f::vec4f(const vec4f &other) {
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
    this->w = other.w;
}


vec4f& vec4f::operator=(const vec4f& rhs) {
    if (this != &rhs) {
        this->x = rhs.x;
        this->y = rhs.y;
        this->z = rhs.z;
        this->w = rhs.w;
    }
    return *this;
}

vec4f& vec4f::operator=(vec4f&& rhs) {
    if (this != &rhs) {
        this->x = rhs.x;
        this->y = rhs.y;
        this->z = rhs.z;
        this->w = rhs.w;
    }
    return *this;
}

// Equality operator

bool vec4f::operator==(const vec4f& rhs) {
    return (
        float_eq(this->x, rhs.x) &&
        float_eq(this->y, rhs.y) &&
        float_eq(this->z, rhs.z) &&
        float_eq(this->w, rhs.w)
    );
}

bool vec4f::operator!=(const vec4f& rhs) {
    return !(
        float_eq(this->x, rhs.x) &&
        float_eq(this->y, rhs.y) &&
        float_eq(this->z, rhs.z) &&
        float_eq(this->w, rhs.w)
    );
}

