/*
 * Allan Pichardo
 * #40051123
 *
 * COMP 371
 * Final Project
 */

#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include <glm/glm.hpp>
#include "SceneObject.h"

/**
 * Represents a camera in space.
 * When initialized, calculates the coordinate space
 * of the view screen.
 */
class Camera: public SceneObject {
public:
    float fieldOfView{};
    float focalLength{};
    float aspectRatio{};

private:
    float W{}, H{};
    glm::vec3 n{}, u{}, v{}, C{}, L{};

public:
    Camera() {type = camera;};

    /**
     * Calculates the coordinate system of the
     * view screen.
     */
    void initializeCoordinateSystem();

    inline float getViewWidth() const {return W;};

    inline float getViewHeight() const {return H;};

    /**
     * Returns the normal of the screen
     */
    inline glm::vec3 getN(){return n;};

    /**
     * Returns the horizontal basis vector of the screen
     * @return
     */
    inline glm::vec3 getU() const {return u;};

    /**
     * Returns the vertical basis vector of the screen
     * @return
     */
    inline glm::vec3 getV() const {return v;};

    inline glm::vec3 getScreenCenter(){return C;};

    inline glm::vec3 getScreenCorner() const {return L;};
};

#endif //RAYTRACER_CAMERA_H
