//
// Created by Allan Pichardo on 2019-04-01.
//

#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include <glm/glm.hpp>
#include "SceneObject.h"
#include "Camera.h"
#include "Pixel.h"
#include "Sphere.h"
#include "Plane.h"
#include "Light.h"
#include <vector>

class Ray {
public:
    glm::vec3 origin;
    glm::vec3 direction;

private:
    bool hasSphereIntersection(Sphere* sphere, glm::vec3 &intersection, float &distance);
    bool hasPlaneIntersection(Plane* plane, glm::vec3 &intersection, float &distance);

public:
    Ray(glm::vec3 &origin, glm::vec3 &direction);
    bool intersects(SceneObject *target, glm::vec3 &intersection);
    bool intersects(SceneObject *target, glm::vec3 &intersection, float &distance);
    static Ray toPixel(Camera &camera, Pixel &pixel);
    static Ray toObject(glm::vec3 &origin, glm::vec3 &destination);
    bool isLightBlockedBy(SceneObject* currentObject, Light* light, std::vector<SceneObject*> sceneObjects);
};

#endif //RAYTRACER_RAY_H
