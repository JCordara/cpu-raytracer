#ifndef SHAPE_H
#define SHAPE_H

#include "../renderable.h"
#include "../intersection.h"

/**
 * CRTP Base class for all geometrically-defined entities in a scene. Calls 
 * derived implementation of check_intersection.
 */
template<class T>
class Shape : public Renderable {
protected:

    Material _material;

public:

    Shape(const Material& m) : _material(m) {}

    opt<Intersection> check_intersection(const Ray& ray) const override {
        return static_cast<const T*>(this)->check_intersection(ray);
    }

    virtual const Material& material() const { return _material; }
    virtual void set_material(const Material& m) { _material = m; }

    virtual ~Shape() = default;
};

#endif // SHAPE_H
