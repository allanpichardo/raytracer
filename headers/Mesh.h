//
// Created by Allan Pichardo on 2019-03-31.
//

#ifndef RAYTRACER_MESH_H
#define RAYTRACER_MESH_H

#include <glm/glm.hpp>

class Mesh {
private:
    char* filename;
    glm::vec3 ambience;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
};

#endif //RAYTRACER_MESH_H
