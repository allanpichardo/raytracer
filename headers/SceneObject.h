/*
 * Allan Pichardo
 * #40051123
 *
 * COMP 371
 * Final Project
 */

#ifndef RAYTRACER_SCENEOBJECT_H
#define RAYTRACER_SCENEOBJECT_H

#include <glm/glm.hpp>

/**
 * The base class of all objects on the scene
 */
class SceneObject {
public:
    enum Type {
        camera, plane, sphere, mesh, light, triangle
    };
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
    Type type;

    virtual inline void setAmbient(glm::vec3 ambient) {this->ambient = ambient;};
    virtual inline void setDiffuse(glm::vec3 diffuse) {this->diffuse = diffuse;};
    virtual inline void setSpecular(glm::vec3 specular) {this->specular = specular;};
    virtual inline void setShininess(float shininess) {this->shininess = shininess;};
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
