/*
 * Allan Pichardo
 * #40051123
 *
 * COMP 371
 * Final Project
 */

#ifndef RAYTRACER_TRIANGLE_H
#define RAYTRACER_TRIANGLE_H

#include "SceneObject.h"
#include <vector>
#include <glm/glm.hpp>

class Triangle: public SceneObject {
public:
    std::vector<glm::vec3> vertices;
    float area;

    Triangle() {type = triangle;};
};

#endif //RAYTRACER_TRIANGLE_H
