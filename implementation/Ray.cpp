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

bool Ray::intersects(SceneObject *target, glm::vec3 &intersection) {
    float t = 0.0f;
    return intersects(target, intersection, t);
}

bool Ray::intersects(SceneObject *target, glm::vec3 &intersection, float &distance) {
    switch(target->type) {
        case SceneObject::plane:
            return hasPlaneIntersection((Plane*)target, intersection, distance);
        case SceneObject::sphere:
            return hasSphereIntersection((Sphere*)target, intersection, distance);
        case SceneObject::triangle:
            return hasTriangleIntersection((Triangle*)target, intersection, distance);
        default:
            return false;
    }

}

bool Ray::hasSphereIntersection(Sphere* target, glm::vec3 &intersection, float &t) {
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

    t = std::fmin(tPos, tNeg);

    intersection = origin + (t * direction);

    return t > 0.0f;
}

bool Ray::hasTriangleIntersection(Triangle* triangle, glm::vec3 &intersection, float &t) {
    float d = glm::dot(direction, triangle->normal);

    if(abs(d) > 0.0f) {
        t = glm::dot(triangle->vertices[0] - origin, triangle->normal) / d;
        intersection = origin + (t * direction);

        glm::vec3 pa = triangle->vertices[0] - intersection;
        glm::vec3 pb = triangle->vertices[1] - intersection;
        glm::vec3 pc = triangle->vertices[2] - intersection;

        float a = glm::length(glm::cross(pb,pc)) / 2.0f;
        float b = glm::length(glm::cross(pa,pc)) / 2.0f;
        float c = glm::length(glm::cross(pa,pb)) / 2.0f;

        a /= triangle->area;
        b /= triangle->area;
        c /= triangle->area;

        float s = a + b + c;

        return s >= 0.0f && s <= 1.0f;
    }

    return false;
}

bool Ray::hasPlaneIntersection(Plane* plane, glm::vec3 &intersection, float &t) {
    float d = glm::dot(direction, plane->normal);

    if(abs(d) > 0.0f) {
        t = glm::dot(plane->position - origin, plane->normal) / d;
        intersection = origin + (t * direction);
        return t >= 0.0f;
    }

    return false;
}

Ray Ray::toObject(glm::vec3 &origin, glm::vec3 &destination) {
    glm::vec3 dir = glm::normalize(destination - origin);
    return Ray(origin, dir);
}

bool Ray::isLightBlockedBy(SceneObject* currentObject, Light* light, std::vector<SceneObject*> sceneObjects) {
    float t;
    float lightT = glm::length(light->position - origin);
    glm::vec3 intersection;
    for(auto & object : sceneObjects) {
        if(currentObject != object && intersects(object, intersection, t)) {
            if(t < lightT) {
                return true;
            }
        }
    }

    return false;

}