#include "raytracer.h"
#include "camera.h"
#include "scene.h"
#include "ray.h"
#include "intersection.h"
#include "renderable.h"

#include "debug.h"

Raytracer::Raytracer(const Camera* camera, const Scene* scene) :
    _scene(scene),
    _camera(camera),
    _empty_color(255, 255, 255),
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
    print("Beginning raytracer image generation...\n");
    int pixel_index = 0;

    for (const vec3& virtual_pixel : _camera->image_surface()) {
        Ray initial_ray = Ray(_camera->pos(), virtual_pixel - _camera->pos());
        vec3 color_sample = _path_trace(initial_ray);

        _write_pixel(pixel_index++, color_sample);
    }

    return _framebuffer;
}


vec3 Raytracer::_get_reflected_color(const Ray& ray, const Intersection& ixn, int iteration) {
    if (ixn.exiting()) return _empty_color;  // Ignore internal reflections
    
    vec3 reflect_dir = ray.direction().reflect(ixn.normal());
    Ray reflected_ray = Ray(ixn.point(), reflect_dir);
    return _path_trace(reflected_ray, iteration + 1);
}


vec3 Raytracer::_get_refracted_color(const Ray& ray, const Intersection& ixn, int iteration) {
    if (ixn.material().opacity() > (1.0f - EPSILON)) return _empty_color;   // Skip if material is opaque

    const float material_refractive_index = ixn.material().refractive_index();
    bool exiting = ixn.exiting();
    float old_medium_refractive_index = exiting ? material_refractive_index : 1.0f;
    float new_medium_refractive_index = exiting ? 1.0f : material_refractive_index;
    vec3 normal = exiting ? -ixn.normal() : ixn.normal();

    vec3 refract_dir = ray.direction().refract(normal, old_medium_refractive_index, new_medium_refractive_index);
    Ray refracted_ray = Ray(ixn.point(), refract_dir);
    return _path_trace(refracted_ray, iteration + 1);
}


vec3 Raytracer::_get_diffuse_color(const Intersection& ixn) {
    float brightness = cast_light_ray(ixn);
    return ixn.material().color() * brightness;
}


vec3 Raytracer::_path_trace(const Ray& ray, unsigned int iteration) {
    // Base case raycast
    if (iteration >= _num_bounces) {
        opt<Intersection> ixn_opt = trace(ray.origin(), ray.direction());
        if (Intersection* p_ixn = ixn_opt.ptr()) {
            return _get_diffuse_color(*p_ixn);
        }
        else return _empty_color;
    }

    opt<Intersection> ixn_opt = trace(ray.origin(), ray.direction());

    if (Intersection* p_ixn = ixn_opt.ptr()) {

        vec3 diffuse_color = _get_diffuse_color(*p_ixn);
        vec3 reflected_color = _get_reflected_color(ray, *p_ixn, iteration);
        vec3 refracted_color = _get_refracted_color(ray, *p_ixn, iteration);

        // Get material properties
        const Material& material = p_ixn->material();
        float n1 = 1.0f;
        float n2 = material.refractive_index();
        
        if (p_ixn->exiting()) {  // swap if ray originated inside object
            n1 = material.refractive_index();
            n2 = 1.0f;
        }

        // Color mixing
        float kr = 0.0f, kt = 0.0f;
        material.fresnel(ray.direction(), p_ixn->normal(), n1, n2, &kr, &kt);
        // if (material.opacity() >= (1.0f - EPSILON)) print("kt` = %.2f\n", kt);
        float transparency_ratio = (1.0f - material.opacity()) / 1.0f;
        kt *= transparency_ratio;
        kr += material.reflectivity();
        float total = kr + kt + material.opacity();
        kr /= total;
        kt /= total;
        float kd = material.opacity() / total;

        float sum = kd + kr + kt;
        if (sum > (1.0f + EPSILON))
            print("%.2f + %.2f + %.2f = %.2f\n", kd, kr, kt, sum);

        return (
            (diffuse_color   * kd) +
            (reflected_color * kr) +
            (refracted_color * kt)
        );
    } 

    else return _empty_color;
}

opt<Intersection> Raytracer::trace(const vec3& origin, const vec3& direction) {
    _intersection_pool.clear();
    Ray ray(origin + (direction * 0.01f), direction);   // Push ray slightly away from last intersection
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
