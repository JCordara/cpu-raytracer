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
    _num_bounces(3),
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
    float blend = 0.15f;

    for (const vec3& virtual_pixel : _camera->image_surface()) {
        vec3 origin = _camera->pos();
        vec3 dir = /* to */ virtual_pixel - /* from */ origin;
        vec3 reflect_dir;

        // Initial cast
        opt<Intersection> ixn_opt = trace(origin, dir);

        // Move on to next pixel if no intersection found
        if (!ixn_opt) {
            _write_pixel(pixel_index++, _empty_color);
            continue;
        }

        Intersection ixn = ixn_opt.ref();
        vec3 pixel_color = ixn.color();
        float brightness = dir
            .reflect(ixn.normal())
            .normalize()
            .dot(-_scene->directional_light_dir());

        for (int i = 0; i < _num_bounces; i++) {
            reflect_dir = dir.reflect(ixn.normal()).normalize();
            float new_brightness = reflect_dir.dot(-_scene->directional_light_dir());
            new_brightness = max(new_brightness, 0.0f);
            brightness = lerp(brightness, new_brightness, blend);
            opt<Intersection> refl_ixn_opt = trace(ixn.point(), reflect_dir);
            if (refl_ixn_opt) {
                Intersection refl_ixn = refl_ixn_opt.ref();
                pixel_color = lerp(pixel_color, refl_ixn.color(), blend);
                ixn = refl_ixn;
            }
            else {
                pixel_color = lerp(pixel_color, _empty_color, blend);
                break;
            }
        }
        
        pixel_color = pixel_color * max(brightness, 0.1f);
        _write_pixel(pixel_index++, pixel_color);
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

void Raytracer::set_num_bounces(int n) {
    this->_num_bounces = n;
}

void Raytracer::_write_pixel(int pixel_index, const vec3& color) {
    int fb_index = pixel_index * 3;
    _framebuffer[fb_index + 0] = static_cast<unsigned char>(color.x);
    _framebuffer[fb_index + 1] = static_cast<unsigned char>(color.y);
    _framebuffer[fb_index + 2] = static_cast<unsigned char>(color.z);
}
