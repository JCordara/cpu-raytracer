#include "scene.h"
#include "sphere.h"

Scene::Scene() : 
    _entities(10),
    _directional_light_dir(0.4f, -0.6f, -0.75f)
{
    _directional_light_dir = _directional_light_dir.normalize();
}

Entity* Scene::add_shape(Entity* s) {
    _entities.append(s);
    return s;
}

vec3 Scene::directional_light_dir() const {
    return _directional_light_dir;
}

vector<Entity*>::Iterator Scene::begin() const {
    return _entities.begin();
}

vector<Entity*>::Iterator Scene::end() const {
    return _entities.end();
}
