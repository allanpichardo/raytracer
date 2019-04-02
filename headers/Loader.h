//
// Created by Allan Pichardo on 2019-04-01.
//

#ifndef RAYTRACER_LOADER_H
#define RAYTRACER_LOADER_H

#include <string>
#include <vector>
#include "SceneObject.h"
#include "Light.h"
#include "Camera.h"

class Loader {
public:
    static void loadScene(const std::string &filename, std::vector<SceneObject*> &sceneObjects, std::vector<Light*> &lights, Camera* &camera);
private:
    static void parseLine(std::vector<SceneObject*> &objects, std::string &line);
    static void addToScene(std::vector<SceneObject*> &objects, std::vector<std::string> parts);
    static void setProperty(SceneObject* object, std::vector<std::string> data);
};


#endif //RAYTRACER_LOADER_H
