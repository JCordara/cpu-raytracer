#include "material.h"
#include "debug.h"

Material::Material() :
    Material(vec3(255, 255, 255), 0.0f, 1.0f, 1.5f)
{}

Material::Material(const vec3& color) :
    Material(color, 0.0f, 1.0f, 1.5f)
{}

Material::Material(const vec3& color, const float reflectivity) :
    Material(color, reflectivity, 1.0f, 1.5f)
{}

Material::Material(const vec3& color, const float reflectivity, const float opacity) :
    Material(color, reflectivity, opacity, 1.5f)
{}

Material::Material(const vec3& color, const float reflectivity, const float opacity, const float refractive_index) :
    _color(color),
    _reflectivity(reflectivity),
    _opacity(opacity),
    _refractive_index(refractive_index)
{}


const void Material::fresnel(const vec3& incident, const vec3& normal, float n1, float n2, /* out */ float* kr, /* out */ float* kt) const {
    float cosi = incident.normalize().dot(-normal);
    if (cosi < 0.0f) {
        *kr = 0.0f;
        *kt = 1.0f;
        return;
    }

    float cost = incident.refract(normal, n1, n2).dot(-normal);
    float x2i = n2 * cosi;
    float x1t = n1 * cost;
    float fr1 = (x2i - x1t) / (x2i + x1t);
    float fr2 = fr1 * fr1;
    float ft1 = (x1t - x2i) / (x2i + x1t);
    float ft2 = ft1 * ft1;
    *kr = (fr2 + ft2) / 2.0f;
    *kt = 1.0f - *kr;
}


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
