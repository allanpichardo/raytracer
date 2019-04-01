//
// Created by Allan Pichardo on 2019-03-31.
//

#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include <glm/glm.hpp>
#include "SceneObject.h"

class Camera: public SceneObject {
public:
    float fieldOfView;
    float focalLength;
    float aspectRatio;

private:
    float W, H;
    glm::vec3 n, u, v, C, L;

public:
    void initializeCoordinateSystem();
    inline float getViewWidth() const {return W;};
    inline float getViewHeight() const {return H;};
    inline glm::vec3 getN(){return n;};
    inline glm::vec3 getU() const {return u;};
    inline glm::vec3 getV() const {return v;};
    inline glm::vec3 getScreenCenter(){return C;};
    inline glm::vec3 getScreenCorner() const {return L;};
};

#endif //RAYTRACER_CAMERA_H
