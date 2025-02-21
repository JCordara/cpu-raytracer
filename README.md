# CPU Raytracing Engine

A simple raytracing engine built with no external dependencies.

## Building

### CMake
```bash
mkdir build && cd build
cmake ..
cmake --build .
Debug/cpu-raytracer.exe
```
This will generate a file called "output.bmp" in the build/ directory.

### GCC
I made a little script called `run.sh` that simply calls gcc and outputs the binary to the `bin/` directory. There's also a `build-release.sh` script that passes a couple of extra compiler arguments.

## Testing
To keep up this repo's tradition of not using any external code, a custom-built test framework called "eztest" was built that provides assert macros and a test runner. The runner actually works by `#include`ing test source files into the main function body and calling `eztest:test_main()`. A little unconventional, but it works!

Run the script `run_tests.sh` to execute the test cases. Test coverage is just the math and container libraries.

## Current status
- Basic raytracing model implemented
  - Ray-sphere & ray-plane collisions
  - Reflection
  - Refraction
  - Shadows
  - Curved image plane (allows 360+ degrees field of view)
  - Basic lighting model
- Custom 3D vector math library
  - vec3f, vec4f operations
  - mat3, mat4 operations
  - sin, cos, sqrt implementations
- Custom image output library
  - Generates 24bit color depth bitmap images (.bmp)

### Demo
![demo_img](images/08_shadows.bmp)
