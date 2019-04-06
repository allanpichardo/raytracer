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
#include <boost/filesystem.hpp>

class Loader {
public:
    static void loadScene(const std::string &filename, std::vector<SceneObject*> &sceneObjects, std::vector<Light*> &lights, Camera* &camera, boost::filesystem::path &scenePath);
private:
    static void parseLine(std::vector<SceneObject*> &objects, std::string &line, boost::filesystem::path &scenePath);
    static void addToScene(std::vector<SceneObject*> &objects, std::vector<std::string> parts, boost::filesystem::path &scenePath);
    static void setProperty(SceneObject* object, std::vector<std::string> data, boost::filesystem::path &scenePath);
};


#endif //RAYTRACER_LOADER_H
