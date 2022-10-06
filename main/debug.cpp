#include "debug.h"

#ifdef _DEBUG
    void print_vec3(const vec3& v, bool newline) {
        printf("(%.2f, %.2f, %.2f)%s", v.x, v.y, v.z, newline ? "\n" : "");
    }

    void print_mat3(const mat3& m, bool newline) {
        printf("| %.2f, %.2f, %.2f %s", m[0][0], m[0][1], m[0][2], newline ? "|\n" : ", ");
        printf("| %.2f, %.2f, %.2f %s", m[1][0], m[1][1], m[1][2], newline ? "|\n" : ", ");
        printf("| %.2f, %.2f, %.2f %s", m[2][0], m[2][1], m[2][2], newline ? "|\n" : ", ");
    }
#else // Don't include cstdio, saves about 1KB
    void print_vec3(const vec3& v, bool newline) {}
    void print_mat3(const mat3& m, bool newline) {}
    namespace __gnu_cxx { // Non-overrided function bloats binary
        void __verbose_terminate_handler() {for (;;);}
    }
#endif
