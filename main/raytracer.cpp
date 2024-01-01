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

    for (const vec3& virtual_pixel : _camera->image_surface()) {
        Ray initial_ray = Ray(_camera->pos(), virtual_pixel - _camera->pos());
        vec3 color_sample = path_trace(initial_ray);

        _write_pixel(pixel_index++, color_sample);
    }

    return _framebuffer;
}

vec3 Raytracer::path_trace(const Ray& ray, unsigned int iteration) {
    // Base case raycast
    if (iteration >= _num_bounces) {
        opt<Intersection> ixn_opt = trace(ray.origin(), ray.direction());
        if (Intersection* p_ixn = ixn_opt.ptr()) {
            float brightness = cast_light_ray(*p_ixn);
            return p_ixn->material().color() * brightness;
        }
        else return _empty_color;
    }

    opt<Intersection> ixn_opt = trace(ray.origin(), ray.direction());
    if (Intersection* p_ixn = ixn_opt.ptr()) {

        // Get reflected color
        vec3 reflect_dir = ray.direction().reflect(p_ixn->normal());
        Ray reflected_ray = Ray(p_ixn->point(), reflect_dir);
        vec3 reflected_color = path_trace(reflected_ray, iteration + 1);

        // Get color at intersection
        float brightness = cast_light_ray(*p_ixn);
        const Material& material = p_ixn->material();
        vec3 color = material.color();
        float reflectivity = material.reflectivity();

        return lerp(color, reflected_color, reflectivity) * brightness;
    } 
    else return _empty_color;
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

float Raytracer::cast_light_ray(const Intersection& ixn) {
    vec3 light_dir = -_scene->directional_light_dir();
    // Not sure what's going on here actually
    // vec3 reflect_dir = ixn.direction().reflect(ixn.normal()).normalize();
    // float dot_prod = reflect_dir.dot(light_dir);
    // return max(dot_prod * dot_prod, 0.175f);
    float dot_product = light_dir.dot(ixn.normal());
    float dot_product_squared = dot_product * abs(dot_product);
    return max(dot_product_squared, 0.175f);
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
