//
// Created by Allan Pichardo on 2019-03-31.
//

#ifndef RAYTRACER_LIGHT_H
#define RAYTRACER_LIGHT_H

#include <glm/glm.hpp>

class Light {
private:
    glm::vec3 position;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

#endif //RAYTRACER_LIGHT_H
