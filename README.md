# Current status
- Custom 3D vector math library
  - vec3f, vec4f operations
  - mat3, mat4 operations
  - sin, cos, sqrt implementations
- Basic raytracing model implemented
  - Ray-sphere collisions
  - Basic reflections
  - Curved image plane (allows 360+ degrees field of view)
  - Very basic lighting model (no shadows yet)
- Custom image output library
  - Generates 24bit color depth bitmap images (.bmp)

# End goals
- Functionality
  - Reflection
  - Refraction
  - Shadows
  - BRDF materials
  - Multiple basic shapes (Sphere, ellipse, rectangular prisms, pyramids, etc.)
  - Space partitioning
- Small binary size
  - Only C library function calls
  - No external vector math libraries
- Fast
  - Multithreaded image generation
  - Optimized intersection algorithms

# Demo of current status
![demo_img](images/04_variable_reflectivity.bmp)
