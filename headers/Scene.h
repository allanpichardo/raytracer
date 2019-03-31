//
// Created by Allan Pichardo on 2019-03-31.
//

#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H

#include <string>
#include <vector>
#include "Camera.h"
#include "SceneObject.h"
#include "Light.h"

class Scene {
public:
    int totalObjects;
    Camera* camera;
    std::vector<Light*> lights;
    std::vector<SceneObject*> sceneObjects;

private:
    void parseLine(std::vector<SceneObject*> &objects, std::string &line);
    void addToScene(std::vector<SceneObject*> &objects, std::vector<std::string> parts);
    void setProperty(SceneObject* object, std::vector<std::string> data);

public:
    Scene(std::string filename);
    ~Scene();
};

#endif //RAYTRACER_SCENE_H
