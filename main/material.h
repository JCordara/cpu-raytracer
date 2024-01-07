#ifndef MATERIAL_H
#define MATERIAL_H

#include "../lib/vex3d.h"


class Material {
private:

    vec3 _color;
    float _reflectivity;
    float _opacity;
    float _refractive_index;

public:

    Material();
    Material(const vec3& color);
    Material(const vec3& color, const float reflectivity);
    Material(const vec3& color, const float reflectivity, const float opacity);
    Material(const vec3& color, const float reflectivity, const float opacity, const float refractive_index);

    const void fresnel(const vec3& incident, const vec3& normal, float n1, float n2, /* out */ float* kr, /* out */ float* kt) const;

    const vec3& color() const;
    const float reflectivity() const;
    const float refractive_index() const;
    const float opacity() const;

};

#endif // MATERIAL_H
