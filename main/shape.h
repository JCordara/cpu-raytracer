#ifndef SHAPE_H
#define SHAPE_H

#include "entity.h"
#include "intersection.h"

/**
 * CRTP Base class for all geometrically-defined entities in a scene. Calls 
 * derived implementation of check_intersection.
 */
template<class T>
class Shape : public Entity {
public:
    Intersection check_intersection(const Ray& ray) const override {
        return static_cast<const T*>(this)->check_intersection(ray);
    }
    virtual ~Shape() = default;
};

#endif // SHAPE_H
