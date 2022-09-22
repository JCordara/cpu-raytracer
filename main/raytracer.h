#ifndef RAY_TRACER_H
#define RAY_TRACER_H

#include "../lib/vex3d.h"

class Camera;
class Scene;
class Ray;
class Intersection;

/**
 * Raytracer objects contain the necessary information to create a raytraced
 * image from a given scene and camera specification. 
 */
class Raytracer {
private:

    const Scene* _scene;
    const Camera* _camera;

    vec3 _empty_color;

    unsigned char* _framebuffer;
    Intersection* _intersection_pool;
    const int MAX_OBJECTS = 1000;

public:

    Raytracer(const Camera* camera, const Scene* scene);
    ~Raytracer();

    void set_scene(const Scene* scene);
    void set_empty_color(const vec3& color);

    unsigned char* trace_scene();
    Intersection trace(const vec3& origin, const vec3& direction);

    // TODO: reflections and stuff
    void set_num_bounces(int n);
};

#endif // RAY_TRACER_H
