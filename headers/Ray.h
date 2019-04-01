//
// Created by Allan Pichardo on 2019-04-01.
//

#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include <glm/glm.hpp>
#include "SceneObject.h"
#include "Camera.h"
#include "Pixel.h"
#include "Intersection.h"

class Ray {
private:
    glm::vec3 origin;
    glm::vec3 direction;

public:
    Ray(glm::vec3 &origin, glm::vec3 &direction);
    Intersection cast(SceneObject* object);
    static Ray toPixel(Camera &camera, Pixel &pixel);
    static Ray toObject(SceneObject &origin, SceneObject* destination);
};

#endif //RAYTRACER_RAY_H
