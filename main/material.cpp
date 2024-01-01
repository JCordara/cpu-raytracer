#include "material.h"
#include "debug.h"

Material::Material() :
    _color(255, 255, 255),
    _reflectivity(0.5f)
{
    print("Material default ctor\n");
}

Material::Material(const vec3& color) :
    _color(color),
    _reflectivity(0.5f)
{
    print("Material color ctor\n");
}

Material::Material(const vec3& color, const float reflectivity) :
    _color(color),
    _reflectivity(reflectivity)
{}


const vec3& Material::color() const {
    return this->_color;
}

const float Material::reflectivity() const {
    return this->_reflectivity;
}
