//
// Created by Allan Pichardo on 2019-04-01.
//

#include <Ray.h>

Ray::Ray(glm::vec3 &origin, glm::vec3 &direction) {
    this->origin = origin;
    this->direction = direction;
}