# Current status
- Custom 3D vector math library
  - vec3f operations
  - mat3f operations
  - sin, cos, sqrt implementations
- Custom image output library
  - Generates 24bit color depth .bmp images
- Basic raytracing model implemented
  - Curved image plane (allows 360+ degrees field of view)
  - Ray-sphere collisions
  - No shading/lighting

# Goals
- Small binary size
  - No external libraries (STL, GLM, etc.)
- Fast
  - Multithreaded image generation
  - Optimized intersection algorithms
- Handle reflections and refractions

# Demo of current status
![demo_img](images/curved_image_plane.bmp)
