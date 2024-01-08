#ifndef SCENE_H
#define SCENE_H

#include "../lib/vex3d.h"
#include "../lib/vector.h"

class Renderable;

/**
 * A scene is a container for entities in 3D space. Raytracer objects hold a
 * constant reference to a scene object that is used to generate the image. 
 * Scene provides a forward iterator over the entities in the scene.
 */
class Scene {
private:

    vector<Renderable*> _entities;

    vec3 _directional_light_dir;
    
public:

    Scene();
    
    Renderable* add_shape(Renderable* s);

    vec3 directional_light_dir() const;

    vector<Renderable*>::Iterator begin() const;
    vector<Renderable*>::Iterator end() const;
    
};

#endif // SCENE_H
