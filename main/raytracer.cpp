#include "raytracer.h"
#include "camera.h"
#include "scene.h"
#include "ray.h"
#include "intersection.h"
#include "sphere.h"

Raytracer::Raytracer(const Camera* camera, const Scene* scene) {
    this->_scene = scene;
    this->_camera = camera;
    this->_empty_color = vec3(220, 220, 220);
    this->_intersection_pool = new Intersection[MAX_OBJECTS]; // Will change
    this->_framebuffer = new unsigned char[_camera->get_pixel_count() * 3];
}

Raytracer::~Raytracer() {
    delete[] _intersection_pool;
    delete[] _framebuffer;
}

void Raytracer::set_scene(const Scene* scene) {
    this->_scene = scene;
}

void Raytracer::set_empty_color(const vec3& color) {
    this->_empty_color = color;
}

unsigned char* Raytracer::trace_scene() {
    int fb_index = 0;
    for (const vec3& pixel : _camera->image_surface()) {
        vec3 color = trace(_camera->get_pos(), pixel - _camera->get_pos());
        _framebuffer[fb_index++] = static_cast<unsigned char>(color.x);
        _framebuffer[fb_index++] = static_cast<unsigned char>(color.y);
        _framebuffer[fb_index++] = static_cast<unsigned char>(color.z);
    }
    return _framebuffer;
}

vec3 Raytracer::trace(const vec3& origin, const vec3& direction) {
    int list_tail = 0;
    Ray ray(origin, direction);
    for (const auto& shape : *_scene) {
        Intersection i = shape.check_intersection(ray);
        if (i.valid) _intersection_pool[list_tail++] = i;
    }
    if (list_tail == 0) return _empty_color;
    Intersection& closest_ixn = _intersection_pool[0];
    vec3 init_diff = closest_ixn.point - _camera->get_pos();
    float min_distance_sqr = init_diff.magnitude2();
    for (int i = 1; i < list_tail; i++) {
        Intersection& ixn = _intersection_pool[i];
        vec3 diff = ixn.point - _camera->get_pos();
        float distance_sqr = diff.magnitude2();
        if (distance_sqr < min_distance_sqr) {
            min_distance_sqr = distance_sqr;
            closest_ixn = ixn;
        }
    }
    return closest_ixn.color;
}
