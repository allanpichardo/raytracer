/*
 * Allan Pichardo
 * #40051123
 *
 * COMP 371
 * Final Project
 */

#include <Ray.h>
#include <cstdlib>

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

/**
 * This convenience function delegates the intersection check
 * based on the type of scene object being checked. The distance
 * parameter is useful when comparing distances and is passed by
 * reference to save CPU time
 */
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

    //When d > 0, the normal of the surface is pointing
    //outward and invisible to the camera
    if(d < 0.0f) {
        t = glm::dot(triangle->vertices[0] - origin, triangle->normal) / d;

        if(t < 0.0f) {
            return false; //triangle plane is behind origin
        }

        intersection = origin + (t * direction);

        glm::vec3 ba = triangle->vertices[1] - triangle->vertices[0];
        glm::vec3 cb = triangle->vertices[2] - triangle->vertices[1];
        glm::vec3 ac = triangle->vertices[0] - triangle->vertices[2];

        glm::vec3 pa = intersection - triangle->vertices[0];
        glm::vec3 pb = intersection - triangle->vertices[1];
        glm::vec3 pc = intersection - triangle->vertices[2];

        float a = glm::dot(glm::cross(ba,pa), triangle->normal);
        float b = glm::dot(glm::cross(cb,pb), triangle->normal);
        float c = glm::dot(glm::cross(ac,pc), triangle->normal);

        return a >= 0.0f && b >= 0.0f && c >= 0.0f;
    }

    return false;
}

bool Ray::hasPlaneIntersection(Plane* plane, glm::vec3 &intersection, float &t) {
    float d = glm::dot(direction, plane->normal);

    //When d > 0, the normal of the surface is pointing
    //outward and invisible to the camera
    if(d < 0.0f) {
        t = glm::dot(plane->position - origin, plane->normal) / d;
        intersection = origin + (t * direction);
        return t >= 0.0f;
    }

    return false;
}

Ray Ray::toObject(glm::vec3 &origin, glm::vec3 &destination, float bias) {
    glm::vec3 dir = glm::normalize(destination - origin);
    glm::vec3 o = origin + bias;
    return Ray(o, dir);
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