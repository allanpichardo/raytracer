//
// Created by Allan Pichardo on 2019-03-31.
//

#ifndef RAYTRACER_PLANE_H
#define RAYTRACER_PLANE_H

#include <glm/glm.hpp>

class Plane {
private:
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 ambience;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
};

#endif //RAYTRACER_PLANE_H
