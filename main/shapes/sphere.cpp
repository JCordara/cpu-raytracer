#include "sphere.h"
#include "../intersection.h"
#include "../ray.h"

Sphere::Sphere(const vec3& center, float radius, const Material& material) : 
    Shape(material)
{
    this->_center = center;
    this->_radius = radius;
}

opt<Intersection> Sphere::check_intersection(const Ray& ray) const {
    vec3 v = ray.origin() - _center;
    float a = ray.direction().dot(ray.direction());
    float b = 2.0f * ray.direction().dot(v);
    float c = v.dot(v) - (_radius * _radius);
    float disc = (b * b) - (4 * a * c);

    // No collision
    if (disc < 0) return opt<Intersection>::none();

    float disc_sqrt = sqrt(disc);
    float t0 = (-b + disc_sqrt) / (2 * a);
    float t1 = (-b - disc_sqrt) / (2 * a);
    
    // Sphere is behind ray origin
    if (t0 < EPSILON && t1 < EPSILON) return opt<Intersection>::none();

    bool exiting = false;
    float t;
    if (t0 < EPSILON || t1 < EPSILON) {
        // If either collision is behind ray origin, ray is exiting the sphere
        exiting = true;
        t = (t0 < 0) ? t1 : t0;
    } else {
        // Both are confirmed positive values
        t = (t0 < t1) ? t0 : t1;
    }

    vec3 intersection_point = ray.origin() + (ray.direction() * t);
    vec3 normal = (intersection_point - _center).normalize();
    float dist_sqr = (intersection_point - ray.origin()).magnitude2();

    return opt<Intersection>(
        Intersection(
            intersection_point, 
            normal, 
            ray.direction(),
            dist_sqr,
            material(),
            exiting
        )
    );
}

vec3 Sphere::center() {
    return _center;
}

float Sphere::radius() {
    return _radius;
}

void Sphere::set_center(vec3 new_center) {
    _center = new_center;
}

void Sphere::set_radius(float new_radius) {
    _radius = new_radius;
}
