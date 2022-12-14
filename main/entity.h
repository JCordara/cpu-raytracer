#ifndef ENTITY_H
#define ENTITY_H

#include "../lib/optional.h"

class Intersection;
class Ray;

/**
 * Base class for all objects in a scene that can be rendered. Provides only
 * an interface for checking collisions and a virtual destructor.
 */
class Entity {
public:
    virtual opt<Intersection> check_intersection(const Ray& ray) const = 0;
    virtual ~Entity() = default;
};

#endif // ENTITY_H
