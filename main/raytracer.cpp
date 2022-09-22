#include "raytracer.h"
#include "camera.h"
#include "scene.h"
#include "ray.h"
#include "intersection.h"
#include "sphere.h"

Raytracer::Raytracer(const Camera* camera, const Scene* scene) {
    this->_scene = scene;
    this->_camera = camera;
    this->_empty_color = vec3(22, 22, 22);
    this->_intersection_pool = new Intersection[MAX_OBJECTS]; // Will change
    this->_framebuffer = new unsigned char[_camera->pixel_count() * 3];
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
        // Get object surface color
        vec3 dir = pixel - _camera->pos();
        Intersection ixn = trace(_camera->pos(), dir);
        vec3 obj_color = ixn.color();

        // Get light amount
        vec3 reflect_dir = dir.reflect(ixn.normal()).normalize();
        Intersection reflect_ixn = trace(ixn.point(), reflect_dir);
        float brightness = reflect_dir.dot(-_scene->directional_light_dir());
        brightness = max(brightness, 0.1f);
        vec3 color = obj_color * (brightness);

        // Update pixel color value
        if (!ixn.valid) color = _empty_color;
        _framebuffer[fb_index++] = static_cast<unsigned char>(color.x);
        _framebuffer[fb_index++] = static_cast<unsigned char>(color.y);
        _framebuffer[fb_index++] = static_cast<unsigned char>(color.z);
    }
    return _framebuffer;
}

Intersection Raytracer::trace(const vec3& origin, const vec3& direction) {
    int list_tail = 0;
    Ray ray(origin, direction);
    for (const auto& shape : *_scene) {
        Intersection i = shape.check_intersection(ray);
        if (i.valid) _intersection_pool[list_tail++] = i;
    }
    if (list_tail == 0) return Intersection::none();
    Intersection& closest_ixn = _intersection_pool[0];
    vec3 init_diff = closest_ixn.point() - _camera->pos();
    float min_distance_sqr = init_diff.magnitude2();
    for (int i = 1; i < list_tail; i++) {
        Intersection& ixn = _intersection_pool[i];
        vec3 diff = ixn.point() - _camera->pos();
        float distance_sqr = diff.magnitude2();
        if (distance_sqr < min_distance_sqr) {
            min_distance_sqr = distance_sqr;
            closest_ixn = ixn;
        }
    }
    return closest_ixn;
}
