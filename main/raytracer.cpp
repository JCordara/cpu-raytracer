#include "raytracer.h"
#include "camera.h"
#include "scene.h"
#include "ray.h"
#include "intersection.h"
#include "sphere.h"

Raytracer::Raytracer(const Camera* camera, const Scene* scene) :
    _scene(scene),
    _camera(camera),
    _empty_color(22, 22, 22),
    _intersection_pool(1000)
{
    this->_framebuffer = new unsigned char[_camera->pixel_count() * 3];
}

Raytracer::~Raytracer() {
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
        opt<Intersection> ixn = trace(_camera->pos(), dir);
        if (!ixn) {
            _framebuffer[fb_index++] = static_cast<unsigned char>(_empty_color.x);
            _framebuffer[fb_index++] = static_cast<unsigned char>(_empty_color.y);
            _framebuffer[fb_index++] = static_cast<unsigned char>(_empty_color.z);
            continue;
        }
        Intersection& obj_ixn = ixn.unwrap();
        vec3 obj_color = obj_ixn.color();

        // Get light amount
        vec3 reflect_dir = dir.reflect(obj_ixn.normal()).normalize();
        // opt<Intersection> reflect_ixn = trace(obj_ixn.point(), reflect_dir);
        float brightness = reflect_dir.dot(-_scene->directional_light_dir());
        brightness = max(brightness, 0.1f);
        vec3 color = obj_color * (brightness);

        // Update pixel color value
        _framebuffer[fb_index++] = static_cast<unsigned char>(color.x);
        _framebuffer[fb_index++] = static_cast<unsigned char>(color.y);
        _framebuffer[fb_index++] = static_cast<unsigned char>(color.z);
    }
    return _framebuffer;
}

opt<Intersection> Raytracer::trace(const vec3& origin, const vec3& direction) {
    _intersection_pool.clear();
    Ray ray(origin, direction);
    for (const auto& shape : *_scene) {
        opt<Intersection> ixn_opt = shape->check_intersection(ray);

        // If ray intersects, insert in order of closest
        if (Intersection* ixn = ixn_opt.ptr()) {
            unsigned int index = 0;
            while (index < _intersection_pool.size()) {
                if (ixn->dist_sqr() < _intersection_pool[index].dist_sqr())
                    break;
                index++;
            }
            _intersection_pool.insert(index, *ixn);
        }
    }

    // If no intersections were added, return no intersection
    if (_intersection_pool.size() == 0) return opt<Intersection>::none();
    
    // Return closest intersection for now
    return opt<Intersection>(_intersection_pool[0]);
}
