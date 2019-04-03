//
// Created by Allan Pichardo on 2019-03-31.
//

#ifndef RAYTRACER_LIGHT_H
#define RAYTRACER_LIGHT_H

#include <glm/glm.hpp>
#include "SceneObject.h"

class Light: public SceneObject {
public:
    float attenuation;

public:
    Light() {type = light; attenuation = 0.0001f;};
};

#endif //RAYTRACER_LIGHT_H
