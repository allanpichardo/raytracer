/*
 * Allan Pichardo
 * #40051123
 *
 * COMP 371
 * Final Project
 */

#ifndef RAYTRACER_PIXEL_H
#define RAYTRACER_PIXEL_H

#include <glm/glm.hpp>
#include "Camera.h"

/**
 * Represents one pixel on screen.
 */
class Pixel {
public:
    glm::vec3 position, color;
    float width;
    float height;

    /**
     * Calculates the position and dimensions in world space of this pixel
     * based on the camera properties and the width/height resolution of the
     * result image
     */
    void initialize(const int &resolutionWidth, const int &resolutionHeight, const int &x, const int &y, const Camera* camera);
};

#endif //RAYTRACER_PIXEL_H
