#ifndef SCENE_H
#define SCENE_H

#include "../lib/vex3d.h"

class Sphere;

/**
 * A scene is a container for objects in 3D space. Raytracer objects hold a
 * constant reference to a scene object that is used to generate the image. 
 * Object provides a forward read-only iterator over the objects in the scene.
 */
class Scene {
public:

    // TODO: Move to private
    int _shape_count;
    Sphere* _shapes;
    
    Scene();
    ~Scene();
    
    // TODO: Add Shape base class and replace with add_shape(const Shape&)
    void add_sphere(const Sphere& s);
    void add_sphere(const vec3& origin, float radius, const vec3& color);

    // Forward iterator over shapes in scene
    class Iterator {
    private:

        Sphere* m_ptr;

    public:

        Iterator(Sphere* ptr);
        const Sphere& operator*() const;
        const Sphere* operator->() const;

        Iterator& operator++();

        friend bool operator== (const Iterator& a, const Iterator& b);
        friend bool operator!= (const Iterator& a, const Iterator& b);
    };

    Iterator begin() const;
    Iterator end() const;
    
};

#endif // SCENE_H
