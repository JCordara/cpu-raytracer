#include "intersection.h"

Intersection::Intersection(vec3 point, vec3 normal, vec3 color) : 
    _point(point),
    _normal(normal), 
    _color(color), 
    valid(true) 
{}

Intersection Intersection::none() {
    Intersection empty_intersection;
    empty_intersection.valid = false;
    return empty_intersection;
}

vec3 Intersection::get_normal() {
    return _normal;
}

vec3 Intersection::get_color() {
    return _color;
}

vec3 Intersection::get_point() {
    return _point;
}

void Intersection::set_normal(const vec3& new_normal) {
    _normal = new_normal;
}

void Intersection::set_color(const vec3& new_color) {
    _color = new_color;
}

void Intersection::set_point(const vec3& new_point) {
    _point = new_point;
}

