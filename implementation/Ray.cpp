//
// Created by Allan Pichardo on 2019-04-01.
//

#include <Ray.h>

Ray::Ray(glm::vec3 &origin, glm::vec3 &direction) {
    this->origin = origin;
    this->direction = direction;
}

Ray Ray::toPixel(Camera &camera, Pixel &pixel) {
    glm::vec3 dir = glm::normalize(pixel.position - camera.position);
    return Ray(camera.position, dir);
}
