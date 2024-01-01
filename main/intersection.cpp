#include "intersection.h"

Intersection::Intersection() : _material(Material()) {}

Intersection::Intersection(
    const vec3& point, 
    const vec3& normal,
    const vec3& direction,
    float dist_sqr,
    const Material& material
) : 
    _normal(normal), 
    _point(point),
    _direction(direction),
    _dist_sqr(dist_sqr),
    _material(material)
{}

const vec3& Intersection::normal() const {
    return _normal;
}

const vec3& Intersection::point() const {
    return _point;
}

const vec3& Intersection::direction() const {
    return _direction;
}

const float& Intersection::dist_sqr() const {
    return _dist_sqr;
}

const Material& Intersection::material() const {
    return _material;
}


void Intersection::set_normal(const vec3& new_normal) {
    _normal = new_normal;
}

void Intersection::set_point(const vec3& new_point) {
    _point = new_point;
}

void Intersection::set_direction(const vec3& new_direction) {
    _direction = new_direction;
}

void Intersection::set_dist_sqr(const float& new_dist_sqr) {
    _dist_sqr = new_dist_sqr;
}
