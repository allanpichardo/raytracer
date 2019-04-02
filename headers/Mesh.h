//
// Created by Allan Pichardo on 2019-03-31.
//

#ifndef RAYTRACER_MESH_H
#define RAYTRACER_MESH_H

#include <glm/glm.hpp>
#include "SceneObject.h"
#include <string>

class Mesh: public SceneObject {
public:
    std::string filename;

public:
    Mesh() {type = mesh;};
};

#endif //RAYTRACER_MESH_H
