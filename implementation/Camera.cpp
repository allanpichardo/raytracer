//
// Created by Allan Pichardo on 2019-03-31.
//

#include <Camera.h>

void Camera::initializeCoordinateSystem() {
    H = 2.0f * focalLength * tan(glm::radians(fieldOfView / 2.0f));
    W = H * aspectRatio;
    n = glm::normalize(position - glm::vec3(0,0,-focalLength));
    u = glm::normalize(glm::cross(glm::vec3(0,1,0), n));
    v = glm::cross(n,u);
    C = position - (n * focalLength);
    L = C - (u * W/2.0f) + (v * H/2.0f);
}
