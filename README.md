# Current status
- Custom 3D vector math library
  - vec3f, vec4f operations
  - mat3, mat4 operations
  - sin, cos, sqrt implementations
- Basic raytracing model implemented
  - Curved image plane (allows 360+ degrees field of view)
  - Ray-sphere collisions
  - Basic reflections
  - Very basic lighting model
- Custom image output library
  - Generates 24bit color depth bitmap images

# End goals
- Small binary size
  - Only C library function calls
  - No external vector math libraries
- Fast
  - Multithreaded image generation
  - Optimized intersection algorithms
- Handle reflections and refractions

# Demo of current status
![demo_img](images/basic_reflections.bmp)
