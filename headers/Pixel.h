//
// Created by Allan Pichardo on 2019-04-01.
//

#ifndef RAYTRACER_PIXEL_H
#define RAYTRACER_PIXEL_H

#include <glm/glm.hpp>
#include "Camera.h"

class Pixel {
public:
    glm::vec3 position, color;
    float width;
    float height;

    void initialize(const int &resolutionWidth, const int &resolutionHeight, const int &x, const int &y, const Camera* camera);
};

#endif //RAYTRACER_PIXEL_H
