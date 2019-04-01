//
// Created by Allan Pichardo on 2019-04-01.
//

#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include <glm/glm.hpp>
#include "SceneObject.h"

class Ray {
private:
    glm::vec3 origin;
    glm::vec3 direction;

public:
    Ray(glm::vec3 &origin, glm::vec3 &direction);
    glm::vec3 intersection(SceneObject* object);
    static Ray traceToPixel(unsigned &x, unsigned &y);
    static Ray traceToObject(SceneObject* object);
};

#endif //RAYTRACER_RAY_H
