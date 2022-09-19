#include "sphere.h"
#include "intersection.h"
#include "ray.h"

Sphere::Sphere(const vec3& center, float radius, const vec3& color) {
    this->_center = center;
    this->_radius = radius;
    this->_color = color;
}

Intersection Sphere::check_intersection(const Ray& ray) const {
    vec3 v = ray.get_origin() - _center;
    float a = ray.get_direction().dot(ray.get_direction());
    float b = 2.0f * ray.get_direction().dot(v);
    float c = v.dot(v) - (_radius * _radius);
    float disc = (b * b) - (4 * a * c);

    if (disc < 0) { // No collision
        return Intersection::none();
    }

    float disc_sqrt = sqrt(disc);
    float t0 = (-b + disc_sqrt) / (2 * a);
    float t1 = (-b - disc_sqrt) / (2 * a);
    
    if (t0 < 0 && t1 < 0) { // Collision is behind camera
        return Intersection::none();
    }

    float t = 0;
    if (t0 < t1 && t0 >= 0) t = t0;
    else t = t1;

    vec3 intersection_point = ray.get_origin() + (ray.get_direction() * t);
    vec3 normal = intersection_point - _center;
    normal = normal.normalize();
    return Intersection(intersection_point, normal, _color);
}

vec3 Sphere::get_center() {
    return _center;
}

vec3 Sphere::get_color() {
    return _color;
}

float Sphere::get_radius() {
    return _radius;
}

void Sphere::set_center(vec3 new_center) {
    _center = new_center;
}

void Sphere::set_color(vec3 new_color) {
    _color = new_color;
}

void Sphere::set_radius(float new_radius) {
    _radius = new_radius;
}
