/*
 * Allan Pichardo
 * #40051123
 *
 * COMP 371
 * Final Project
 */

#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include <glm/glm.hpp>
#include "SceneObject.h"
#include "Camera.h"
#include "Pixel.h"
#include "Sphere.h"
#include "Plane.h"
#include "Light.h"
#include "Triangle.h"
#include <vector>

/**
 * Represents a ray with an origin and direction
 */
class Ray {
public:
    glm::vec3 origin;
    glm::vec3 direction;

private:

    bool hasSphereIntersection(Sphere* sphere, glm::vec3 &intersection, float &distance);

    bool hasPlaneIntersection(Plane* plane, glm::vec3 &intersection, float &distance);

    bool hasTriangleIntersection(Triangle* triangle, glm::vec3 &intersection, float &distance);

public:
    Ray(glm::vec3 &origin, glm::vec3 &direction);

    bool intersects(SceneObject *target, glm::vec3 &intersection);

    bool intersects(SceneObject *target, glm::vec3 &intersection, float &distance);

    /**
     * Creates a ray going from the center of the camera to the
     * given pixel
     */
    static Ray toPixel(Camera &camera, Pixel &pixel);

    /**
     * Creates a ray going from any point in space towards any
     * other point. The optional bias paramter offsets the origin
     * point of the vector by a small amount to compensate for
     * shadow acne.
     */
    static Ray toObject(glm::vec3 &origin, glm::vec3 &destination, float bias = 0.0f);

    /**
     * Returns true if a shadow ray from currentObject to light is
     * obscured by any of the other scene objects
     */
    bool isLightBlockedBy(SceneObject* currentObject, Light* light, std::vector<SceneObject*> sceneObjects);
};

#endif //RAYTRACER_RAY_H
