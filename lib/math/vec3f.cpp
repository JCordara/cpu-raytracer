#include "vec3f.h"
#include "common.h"

// Binary operations between vectors

vec3f operator+(const vec3f& lhs, const vec3f& rhs) {
    return vec3f(
        lhs.x + rhs.x,
        lhs.y + rhs.y,
        lhs.z + rhs.z
    );
}

vec3f operator-(const vec3f& lhs, const vec3f& rhs) {
    return vec3f(
        lhs.x - rhs.x,
        lhs.y - rhs.y,
        lhs.z - rhs.z
    );
}

float vec3f::dot(const vec3f& rhs) const {
    return (this->x * rhs.x) + (this->y * rhs.y) + (this->z * rhs.z);
}

float vec3f::dot(const vec3f&& rhs) const {
    return (this->x * rhs.x) + (this->y * rhs.y) + (this->z * rhs.z);
}

vec3f vec3f::cross(const vec3f& rhs) const {
    return vec3f(
        (this->y * rhs.z) - (this->z * rhs.y),
        (this->z * rhs.x) - (this->x * rhs.z),
        (this->x * rhs.y) - (this->y * rhs.x)
    );
}

vec3f vec3f::cross(const vec3f&& rhs) const {
    return vec3f(
        (this->y * rhs.z) - (this->z * rhs.y),
        (this->z * rhs.x) - (this->x * rhs.z),
        (this->x * rhs.y) - (this->y * rhs.x)
    );
}

vec3f vec3f::reflect(const vec3f& normal) const {
    vec3f n = normal.normalize();
    float dp = this->dot(n);
    vec3f operand = 2 * dp * n;
    return *this - operand;
}

vec3f vec3f::reflect(const vec3f&& normal) const {
    vec3f n = normal.normalize();
    float dp = this->dot(n);
    vec3f operand = 2 * dp * n;
    return *this - operand;
}


// Binary operations with scalar types

// Addition
vec3f operator+(vec3f const& v, float scalar) {
    return vec3f(
        v.x + scalar,
        v.y + scalar,
        v.z + scalar
    );
}

vec3f operator+(float scalar, vec3f const& v) {
    return vec3f(
        scalar + v.x,
        scalar + v.y,
        scalar + v.z
    );
}

vec3f operator+(vec3f const& v, int scalar) {
    float f_scalar = static_cast<float>(scalar);
    return vec3f(
        v.x + f_scalar,
        v.y + f_scalar,
        v.z + f_scalar
    );
}

vec3f operator+(int scalar, vec3f const& v) {
    float f_scalar = static_cast<float>(scalar);
    return vec3f(
        f_scalar + v.x,
        f_scalar + v.y,
        f_scalar + v.z
    );
}

// Subtraction
vec3f operator-(vec3f const& v, float scalar) {
    return vec3f(
        v.x - scalar,
        v.y - scalar,
        v.z - scalar
    );
}

vec3f operator-(float scalar, vec3f const& v) {
    return vec3f(
        scalar - v.x,
        scalar - v.y,
        scalar - v.z
    );
}

vec3f operator-(vec3f const& v, int scalar) {
    float f_scalar = static_cast<float>(scalar);
    return vec3f(
        v.x - f_scalar,
        v.y - f_scalar,
        v.z - f_scalar
    );
}

vec3f operator-(int scalar, vec3f const& v) {
    float f_scalar = static_cast<float>(scalar);
    return vec3f(
        f_scalar - v.x,
        f_scalar - v.y,
        f_scalar - v.z
    );
}

// Multiplication
vec3f operator*(vec3f const& v, float scalar) {
    return vec3f(
        v.x * scalar,
        v.y * scalar,
        v.z * scalar
    );
}

vec3f operator*(float scalar, vec3f const& v) {
    return vec3f(
        scalar * v.x,
        scalar * v.y,
        scalar * v.z
    );
}

vec3f operator*(vec3f const& v, int scalar) {
    float f_scalar = static_cast<float>(scalar);
    return vec3f(
        v.x * f_scalar,
        v.y * f_scalar,
        v.z * f_scalar
    );
}

vec3f operator*(int scalar, vec3f const& v) {
    float f_scalar = static_cast<float>(scalar);
    return vec3f(
        f_scalar * v.x,
        f_scalar * v.y,
        f_scalar * v.z
    );
}

// Division
vec3f operator/(vec3f const& v, float scalar) {
    return vec3f(
        v.x / scalar,
        v.y / scalar,
        v.z / scalar
    );
}

vec3f operator/(float scalar, vec3f const& v) {
    return vec3f(
        scalar / v.x,
        scalar / v.y,
        scalar / v.z
    );
}

vec3f operator/(vec3f const& v, int scalar) {
    float f_scalar = static_cast<float>(scalar);
    return vec3f(
        v.x / f_scalar,
        v.y / f_scalar,
        v.z / f_scalar
    );
}

vec3f operator/(int scalar, vec3f const& v) {
    float f_scalar = static_cast<float>(scalar);
    return vec3f(
        f_scalar / v.x,
        f_scalar / v.y,
        f_scalar / v.z
    );
}


// Unary vector operations

float vec3f::magnitude() const {
    // Apparently this is the fasted sqrt algorithm out there
    return sqrt(
        (this->x * this->x) +
        (this->y * this->y) +
        (this->z * this->z)
    );
}

float vec3f::magnitude2() const {
    // Apparently this is the fasted sqrt algorithm out there
    return (
        (this->x * this->x) +
        (this->y * this->y) +
        (this->z * this->z)
    );
}

vec3f vec3f::normalize() const {
    if (this->x == 0 && this->y == 0 && this->z == 0) return vec3f();
    float magnitude = this->magnitude();
    return vec3f(
        this->x / magnitude, 
        this->y / magnitude, 
        this->z / magnitude
    );
}

vec3f vec3f::operator-() const {
    return vec3f(
        -this->x,
        -this->y,
        -this->z
    );
}


// Element access

float vec3f::operator[](int ix) {
    if (ix == 0) return x;
    if (ix == 1) return y;
    if (ix == 2) return z;
    else return NaN;
}



// Constructors

vec3f::vec3f() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

vec3f::vec3f(float init_value) {
    this->x = init_value;
    this->y = init_value;
    this->z = init_value;
}

vec3f::vec3f(int init_value) : vec3f(static_cast<float>(init_value)) {}

vec3f::vec3f(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

vec3f::vec3f(int x, int y, int z) : 
    vec3f(
        static_cast<float>(x),
        static_cast<float>(y),
        static_cast<float>(z)
    ) 
{}


vec3f::vec3f(float xyz[3]) {
    this->x = xyz[0];
    this->y = xyz[1];
    this->z = xyz[2];
}

vec3f::vec3f(int xyz[3]) : 
    vec3f(
        static_cast<float>(xyz[0]),
        static_cast<float>(xyz[1]),
        static_cast<float>(xyz[2])
    ) 
{}

vec3f::vec3f(const vec3f &other) {
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
}


vec3f& vec3f::operator=(const vec3f& rhs) {
    if (this != &rhs) {
        this->x = rhs.x;
        this->y = rhs.y;
        this->z = rhs.z;
    }
    return *this;
}

vec3f& vec3f::operator=(vec3f&& rhs) {
    if (this != &rhs) {
        this->x = rhs.x;
        this->y = rhs.y;
        this->z = rhs.z;
    }
    return *this;
}

// Equality operator

bool vec3f::operator==(const vec3f& rhs) {
    return (
        this->x == rhs.x &&
        this->y == rhs.y &&
        this->z == rhs.z
    );
}

bool vec3f::operator!=(const vec3f& rhs) {
    return (
        this->x != rhs.x ||
        this->y != rhs.y ||
        this->z != rhs.z
    );
}

