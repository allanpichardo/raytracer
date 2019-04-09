/*
 * Allan Pichardo
 * #40051123
 *
 * COMP 371
 * Final Project
 */

#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H

#include <glm/glm.hpp>
#include "SceneObject.h"

class Sphere: public SceneObject {
public:
    float radius{};

public:
    Sphere() {type = sphere;};
};

#endif //RAYTRACER_SPHERE_H
