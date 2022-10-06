#include "raytracer.h"
#include "camera.h"
#include "scene.h"
#include "ray.h"
#include "intersection.h"
#include "sphere.h"

Raytracer::Raytracer(const Camera* camera, const Scene* scene) :
    _scene(scene),
    _camera(camera),
    _empty_color(75, 110, 170),
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
    int pixel_index = 0;
    for (const vec3& virtual_pixel : _camera->image_surface()) {
        // Get intersection
        vec3 dir = /* to */ virtual_pixel - /* from */ _camera->pos();
        opt<Intersection> ixn_opt = trace(_camera->pos(), dir);
        Intersection* ixn = ixn_opt.ptr();

        // If no intersection found
        if (!ixn) {
            _write_pixel(pixel_index++, _empty_color);
            continue;
        }

        // Get light amount
        vec3 reflect_dir = dir.reflect(ixn->normal()).normalize();
        float brightness = reflect_dir.dot(-_scene->directional_light_dir());
        brightness = max(brightness, 0.1f);

        vec3 color = ixn->color() * (brightness);

        float blend = 0.15f;
        opt<Intersection> reflect_ixn_opt = trace(ixn->point(), reflect_dir);
        if (Intersection* reflect_ixn = reflect_ixn_opt.ptr()) {
            vec3 reflect_dir2 = reflect_dir.reflect(reflect_ixn->normal()).normalize();
            float brightness = reflect_dir2.dot(-_scene->directional_light_dir());
            brightness = max(brightness, 0.1f);
            vec3 reflect_color = reflect_ixn->color() * brightness;
            color = ((1.0f - blend) * color) + ((blend) * reflect_color);
        } else {
            color = ((1.0f - blend) * color) + ((blend) * _empty_color);
        }
        
        // Update pixel color value
        _write_pixel(pixel_index++, color);
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

void Raytracer::_write_pixel(int pixel_index, const vec3& color) {
    int fb_index = pixel_index * 3;
    _framebuffer[fb_index + 0] = static_cast<unsigned char>(color.x);
    _framebuffer[fb_index + 1] = static_cast<unsigned char>(color.y);
    _framebuffer[fb_index + 2] = static_cast<unsigned char>(color.z);
}
