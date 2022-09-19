#ifndef SCENE_H
#define SCENE_H

#include "../lib/vex3d.h"

class Entity;

/**
 * A scene is a container for entities in 3D space. Raytracer objects hold a
 * constant reference to a scene object that is used to generate the image. 
 * Scene provides a forward iterator over the entities in the scene.
 */
class Scene {
private:

    int _entity_count;
    Entity** _entities;
    
public:

    Scene();
    ~Scene();
    
    Entity* add_shape(Entity* s);

    // Forward iterator over shapes in scene
    class Iterator {
    private:

        Entity** m_ptr;

    public:

        Iterator(Entity** ptr);
        const Entity& operator*() const;
        const Entity* operator->() const;

        Iterator& operator++();

        friend bool operator== (const Iterator& a, const Iterator& b);
        friend bool operator!= (const Iterator& a, const Iterator& b);
    };

    Iterator begin() const;
    Iterator end() const;
    
};

#endif // SCENE_H
