#ifndef _DEBUG_H
#define _DEBUG_H

#include "../lib/vex3d.h"

void print_vec3(const vec3& v, bool newline = true);
void print_mat3(const mat3& m, bool newline = true);

#ifdef _DEBUG
    #include <cstdio>
    #define print printf
#else
    #define print //

    namespace __gnu_cxx { // Non-overrided function bloats binary
        void __verbose_terminate_handler();
    }

#endif

#endif // _DEBUG_H
