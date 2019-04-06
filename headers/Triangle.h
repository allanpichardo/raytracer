//
// Created by Allan Pichardo on 2019-04-05.
//

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
