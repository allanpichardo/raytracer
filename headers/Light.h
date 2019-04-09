/*
 * Allan Pichardo
 * #40051123
 *
 * COMP 371
 * Final Project
 */

#ifndef RAYTRACER_LIGHT_H
#define RAYTRACER_LIGHT_H

#include <glm/glm.hpp>
#include "SceneObject.h"

/**
 * Represents a point light in the scene
 */
class Light: public SceneObject {
public:
    float attenuation;

public:
    Light() {type = light; attenuation = 0.0001f;};
};

#endif //RAYTRACER_LIGHT_H
