//
// Created by Allan Pichardo on 2019-03-31.
//

#ifndef RAYTRACER_LIGHT_H
#define RAYTRACER_LIGHT_H

#include <glm/glm.hpp>
#include "SceneObject.h"

class Light: public SceneObject {
public:
    glm::vec3 color;

public:
    Light() {type = light; color = glm::vec3(1.0f);};
};

#endif //RAYTRACER_LIGHT_H
