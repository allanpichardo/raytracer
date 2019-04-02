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
    friend inline bool operator==(const SceneObject& lhs, const SceneObject& rhs);
};

bool operator==(const SceneObject &lhs, const SceneObject &rhs) {
    return lhs.position == rhs.position &&
    lhs.normal == rhs.normal &&
    lhs.ambient == rhs.ambient &&
    lhs.diffuse == rhs.diffuse &&
    lhs.specular == rhs.specular &&
    lhs.shininess == rhs.shininess &&
    lhs.type == rhs.type;
}

#endif //RAYTRACER_SCENEOBJECT_H
