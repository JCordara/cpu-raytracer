#include "ray.h"

Ray::Ray(const vec3& origin, const vec3& direction) {
    this->origin = origin;
    this->direction = direction;
    this->_direction_normalized = vec3(0);
}

vec3 Ray::normalized_dir() {
    if (_direction_normalized == vec3(0)) {
        _direction_normalized = _direction_normalized.normalize();
    }
    return _direction_normalized;
}
