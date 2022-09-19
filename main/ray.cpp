#include "ray.h"

Ray::Ray(const vec3& origin, const vec3& direction):
    _origin(origin),
    _direction(direction),
    _direction_normalized(0)
{}


vec3 Ray::normalized_dir() {
    if (_direction_normalized == vec3(0)) {
        _direction_normalized = _direction_normalized.normalize();
    }
    return _direction_normalized;
}

vec3 Ray::origin() const {
    return _origin;
}

vec3 Ray::direction() const {
    return _direction;
}

void Ray::set_origin(const vec3& new_origin) {
    _origin = new_origin;
}

void Ray::set_direction(const vec3& new_direction) {
    _direction = new_direction;
}

