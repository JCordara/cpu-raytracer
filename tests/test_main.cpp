#include "eztest.hpp"
#include "eztest_macros.h"

#include "../lib/vex3d.h"
#include "../lib/vector.h"

void print_mat3(const mat3& m, bool newline = true) {
    std::cout << (newline ? "\n" : "");
    std::cout << "| " << m[0][0] << ", " << m[0][1] << ", " << m[0][2];
    std::cout << (newline ? " |\n" : ", ");
    std::cout << "| " << m[1][0] << ", " << m[1][1] << ", " << m[1][2];
    std::cout << (newline ? " |\n" : ", ");
    std::cout << "| " << m[2][0] << ", " << m[2][1] << ", " << m[2][2];
    std::cout << (newline ? " |\n" : " ");
}

void print_mat4(const mat4& m, bool newline = true) {
    std::cout << (newline ? "\n" : "");
    std::cout << "| " << m[0][0] << ", " << m[0][1] << ", " << m[0][2] << ", " << m[0][3];
    std::cout << (newline ? " |\n" : ", ");
    std::cout << "| " << m[1][0] << ", " << m[1][1] << ", " << m[1][2] << ", " << m[1][3];
    std::cout << (newline ? " |\n" : ", ");
    std::cout << "| " << m[2][0] << ", " << m[2][1] << ", " << m[2][2] << ", " << m[2][3];
    std::cout << (newline ? " |\n" : " ");
    std::cout << "| " << m[3][0] << ", " << m[3][1] << ", " << m[3][2] << ", " << m[3][3];
    std::cout << (newline ? " |\n" : " ");
}

void print_vec3(const vec3& v, bool newline = true) {
    std::cout << "(" << v.x << ", " << v.y << ", " << v.z << ") ";
    if (newline) {
        std::cout << "\n";
    }
}

void print_vec4(const vec4& v, bool newline = true) {
    std::cout << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ") ";
    if (newline) {
        std::cout << "\n";
    }
}

int main() {
    #include "test_common_math.hpp"
    #include "test_vec3f.hpp"
    #include "test_mat3.hpp"
    #include "test_vector.hpp"
    #include "test_vec4f.hpp"
    #include "test_mat4.hpp"
    return eztest::test_main();
}