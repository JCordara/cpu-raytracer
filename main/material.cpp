#include "material.h"
#include "debug.h"

Material::Material() :
    Material(vec3(255, 255, 255), 0.0f, 1.0f, 1.0f)
{}

Material::Material(const vec3& color) :
    Material(color, 0.0f, 1.0f, 1.0f)
{}

Material::Material(const vec3& color, const float reflectivity) :
    Material(color, reflectivity, 1.0f, 1.0f)
{}

Material::Material(const vec3& color, const float reflectivity, const float opacity) :
    Material(color, reflectivity, opacity, 1.0f)
{}

Material::Material(const vec3& color, const float reflectivity, const float opacity, const float refractive_index) :
    _color(color),
    _reflectivity(reflectivity),
    _opacity(opacity),
    _refractive_index(refractive_index)
{}


const vec3& Material::color() const {
    return this->_color;
}

const float Material::reflectivity() const {
    return this->_reflectivity;
}

const float Material::opacity() const {
    return this->_opacity;
}

const float Material::refractive_index() const {
    return this->_refractive_index;
}
