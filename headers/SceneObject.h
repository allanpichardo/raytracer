//
// Created by Allan Pichardo on 2019-03-31.
//

#ifndef RAYTRACER_SCENEOBJECT_H
#define RAYTRACER_SCENEOBJECT_H

#include <glm/glm.hpp>

class SceneObject {
public:
    enum Type {
        camera, plane, sphere, mesh, light
    };
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
    Type type;

    virtual ~SceneObject() = default;
};

#endif //RAYTRACER_SCENEOBJECT_H
