#include "eztest.hpp"
#include "eztest_macros.h"

#include "../lib/vex3d.h"

int main() {
    #include "test_vec3f.hpp"
    #include "test_common_math.hpp"
    return eztest::test_main();
}