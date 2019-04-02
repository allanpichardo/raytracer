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

class Ray {
public:
    glm::vec3 origin;
    glm::vec3 direction;

private:
    bool hasSphereIntersection(Sphere* sphere, glm::vec3 &intersection);
    bool hasPlaneIntersection(Plane* plane, glm::vec3 &intersection);

public:
    Ray(glm::vec3 &origin, glm::vec3 &direction);
    bool cast(SceneObject* target, glm::vec3 &intersection);
    static Ray toPixel(Camera &camera, Pixel &pixel);
    static Ray toObject(SceneObject &origin, SceneObject* destination);
};

#endif //RAYTRACER_RAY_H
