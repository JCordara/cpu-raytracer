#ifndef MATERIAL_H
#define MATERIAL_H

#include "../lib/vex3d.h"


class Material {
private:

    vec3 _color;
    float _reflectivity;

public:

    Material();
    Material(const vec3& color);
    Material(const vec3& color, const float reflectivity);

    const vec3& color() const;
    const float reflectivity() const;

};

#endif // MATERIAL_H
