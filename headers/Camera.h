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

};

#endif //RAYTRACER_CAMERA_H
