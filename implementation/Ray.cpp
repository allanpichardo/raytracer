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

bool Ray::cast(SceneObject *target, glm::vec3 &intersection) {
    switch(target->type) {
        case SceneObject::camera:break;
        case SceneObject::plane:break;
        case SceneObject::sphere:
            return hasSphereIntersection(dynamic_cast<Sphere *>(target), intersection);
        case SceneObject::mesh:break;
        case SceneObject::light:break;
    }
}

bool Ray::hasSphereIntersection(Sphere *target, glm::vec3 &intersection) {
    glm::vec3 c2e = origin - target->position;

    float a = glm::dot(direction, direction);
    float b = glm::dot(2.0f*direction, c2e);
    float c = glm::dot(c2e, c2e) - (target->radius * target->radius);

    float rad = (b*b) - 4.0f * a * c;

    if(rad < 0.0f) {
        return false;
    }

    float tPos = (-b + sqrt(rad)) / (2.0f * a);
    float tNeg = (-b - sqrt(rad)) / (2.0f * a);

    float t = std::fmin(tPos, tNeg);

    intersection = origin + (t * direction);

    return true;
}


