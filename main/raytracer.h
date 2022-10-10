#ifndef RAY_TRACER_H
#define RAY_TRACER_H

#include "../lib/vex3d.h"
#include "../lib/optional.h"
#include "../lib/vector.h"

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
    unsigned int _num_bounces;

    unsigned char* _framebuffer;
    vector<Intersection> _intersection_pool;

public:

    Raytracer(const Camera* camera, const Scene* scene);
    ~Raytracer();

    void set_scene(const Scene* scene);
    void set_empty_color(const vec3& color);

    unsigned char* trace_scene();
    vec3 path_trace(const Ray& ray, unsigned int iteration = 0);
    opt<Intersection> trace(const vec3& origin, const vec3& direction);

    float cast_light_ray(const Intersection& ixn);

    void set_num_bounces(int n);

private:

    void _write_pixel(int pixel_index, const vec3& color);

};

#endif // RAY_TRACER_H
