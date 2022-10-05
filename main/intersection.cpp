#include "intersection.h"

Intersection::Intersection(vec3 point, vec3 normal, vec3 color, vec3 direction) : 
    _point(point),
    _normal(normal), 
    _color(color),
    _direction(direction)
{}

vec3 Intersection::normal() {
    return _normal;
}

vec3 Intersection::color() {
    return _color;
}

vec3 Intersection::point() {
    return _point;
}

vec3 Intersection::direction() {
    return _direction;
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

void Intersection::set_direction(const vec3& new_direction) {
    _direction = new_direction;
}

