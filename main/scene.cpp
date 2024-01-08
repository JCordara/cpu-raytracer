#include "scene.h"
#include "shapes/shapes.h"

Scene::Scene() : 
    _entities(10),
    _directional_light_dir(0.4f, -0.6f, -0.75f)
{
    _directional_light_dir = _directional_light_dir.normalize();
}

Renderable* Scene::add_shape(Renderable* s) {
    _entities.append(s);
    return s;
}

vec3 Scene::directional_light_dir() const {
    return _directional_light_dir;
}

vector<Renderable*>::Iterator Scene::begin() const {
    return _entities.begin();
}

vector<Renderable*>::Iterator Scene::end() const {
    return _entities.end();
}
