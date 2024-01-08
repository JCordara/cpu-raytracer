#include "plane.h"
#include "../intersection.h"
#include "../ray.h"

Plane::Plane(const vec3& origin, const vec3& normal, const Material& material) : 
    Shape(material)
{
    _origin = origin;
    _normal = normal.normalize();
    _height = _origin.dot(-_normal);
}

opt<Intersection> Plane::check_intersection(const Ray& ray) const {
    float vd = _normal.dot(ray.direction());
    if (float_eq(vd, 0.0f)) return opt<Intersection>::none();   // Ray is parallel to plane

    float tmp = _normal.dot(ray.origin()) + _height;
    float t = -tmp / vd;

    if (t < EPSILON) return opt<Intersection>::none(); // Plane is behind ray, no intersection
    vec3 normal = (vd > 0.0f) ? -_normal : _normal;
    vec3 intersection_point = ray.origin() + (ray.direction() * t);
    float dist_sqr = (intersection_point - ray.origin()).magnitude2();

    return opt<Intersection>(
        Intersection(
            intersection_point,
            normal,
            ray.direction(),
            dist_sqr,
            material(),
            false
        )
    );
}

vec3 Plane::normal() {
    return _normal;
}

void Plane::set_normal(const vec3& normal) {
    _normal = normal;
}

