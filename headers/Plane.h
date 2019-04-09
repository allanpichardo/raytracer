/*
 * Allan Pichardo
 * #40051123
 *
 * COMP 371
 * Final Project
 */

#ifndef RAYTRACER_PLANE_H
#define RAYTRACER_PLANE_H

#include <glm/glm.hpp>
#include "SceneObject.h"

class Plane: public SceneObject {
public:
    Plane() {type = plane;};
};

#endif //RAYTRACER_PLANE_H
