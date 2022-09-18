#include "sphere.h"
#include "intersection.h"
#include "ray.h"

Sphere::Sphere(const vec3& origin, float radius, const vec3& color) {
    this->origin = origin;
    this->radius = radius;
    this->radius_sqr = radius * radius;
    this->color = color;
}

Intersection Sphere::check_intersection(const Ray& ray) const {
    vec3 v = ray.origin - origin;
    float a = ray.direction.dot(ray.direction);
    float b = 2.0f * ray.direction.dot(v);
    float c = v.dot(v) - radius_sqr;
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

    vec3 intersection_point = ray.origin + (ray.direction * t);
    vec3 normal = intersection_point - origin;
    normal = normal.normalize();
    return Intersection(intersection_point, normal, color);
}
