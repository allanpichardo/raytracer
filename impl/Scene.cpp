//
// Created by Allan Pichardo on 2019-03-31.
//

#include "Scene.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <boost/tokenizer.hpp>
#include <SceneObject.h>
#include <Plane.h>
#include <Sphere.h>
#include <Mesh.h>
#include <Light.h>

Scene::Scene(std::string filename) {

    std::ifstream input(filename);
    std::string line;
    bool isFirst = true;

    std::vector<SceneObject*> allObjects;

    if(input.is_open()) {
        while (getline(input, line)) {
            if(isFirst) {
                totalObjects = std::stoi(line);
                isFirst = false;
            } else {
                parseLine(allObjects, line);
            }
        }
    }

    input.close();

    for(int i = 0; i < allObjects.size(); i++) {
        switch(allObjects[i]->type) {
            case SceneObject::camera:
                camera = (Camera*)allObjects[i];
                break;
            case SceneObject::plane:
            case SceneObject::sphere:
            case SceneObject::mesh:
                sceneObjects.push_back(allObjects[i]);
                break;
            case SceneObject::light:
                lights.push_back((Light*)allObjects[i]);
                break;
        }
    }

}

void Scene::parseLine(std::vector<SceneObject*> &objects, std::string &line) {
    boost::char_separator<char> sep(" ");
    boost::tokenizer< boost::char_separator<char> > tok(line, sep);
    std::vector<std::string> parts;
    for(boost::tokenizer< boost::char_separator<char> >::iterator beg = tok.begin(); beg != tok.end(); ++beg)
    {
        parts.push_back(*beg);
    }

    if(parts.size() > 0) {
        addToScene(objects, parts);
    }
}

constexpr unsigned int hash(const char *str, int h = 0) {
    return !str[h] ? 5381 : (hash(str, h+1)*33) ^ str[h];
}

void Scene::addToScene(std::vector<SceneObject*> &objects, std::vector<std::string> parts) {
    switch(hash(parts[0].c_str())) {
        case hash("camera"): {
            Camera* camera = new Camera();
            camera->type = SceneObject::Type::camera;
            objects.push_back(camera);
        }
        break;
        case hash("plane"): {
            Plane* plane = new Plane();
            plane->type = SceneObject::Type::plane;
            objects.push_back(plane);
        }
        break;
        case hash("sphere"): {
            Sphere* sphere = new Sphere();
            sphere->type = SceneObject::Type::sphere;
            objects.push_back(sphere);
        }
        break;
        case hash("mesh"):{
            Mesh* mesh = new Mesh();
            mesh->type = SceneObject::Type::mesh;
            objects.push_back(mesh);
        }
        break;
        case hash("light"):{
            Light* light = new Light();
            light->type = SceneObject::Type::light;
            objects.push_back(light);
        }
        break;
        default:
            setProperty(objects.back(), parts);
            break;
    }
}

void Scene::setProperty(SceneObject* object, std::vector<std::string> data) {

    switch(hash(data[0].c_str())) {
        case hash("pos:"):
            object->position = glm::vec3(std::stof(data[1]), std::stof(data[2]), std::stof(data[3]));
            break;
        case hash("fov:"):
            ((Camera*)object)->fieldOfView = std::stof(data[1]);
            break;
        case hash("f:"):
            ((Camera*)object)->focalLength = std::stof(data[1]);
            break;
        case hash("a:"):
            ((Camera*)object)->aspectRatio = std::stof(data[1]);
            break;
        case hash("nor:"):
            object->normal = glm::vec3(std::stof(data[1]), std::stof(data[2]), std::stof(data[3]));
            break;
        case hash("amb:"):
            object->ambient = glm::vec3(std::stof(data[1]), std::stof(data[2]), std::stof(data[3]));
            break;
        case hash("dif:"):
            object->diffuse = glm::vec3(std::stof(data[1]), std::stof(data[2]), std::stof(data[3]));
            break;
        case hash("spe:"):
            object->specular = glm::vec3(std::stof(data[1]), std::stof(data[2]), std::stof(data[3]));
            break;
        case hash("shi:"):
            object->shininess = std::stof(data[1]);
            break;
        case hash("file:"):
            ((Mesh*)object)->filename = data[1];
            break;
    }
}

Scene::~Scene() {
    for(int i = 0; i < sceneObjects.size(); i++) {
        delete sceneObjects[i];
    }
    sceneObjects.clear();

    for(int i = 0; i < lights.size(); i++) {
        delete lights[i];
    }
    lights.clear();

    delete camera;
    camera = nullptr;
}
