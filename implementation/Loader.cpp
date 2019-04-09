/*
 * Allan Pichardo
 * #40051123
 *
 * COMP 371
 * Final Project
 */

#include <fstream>
#include <boost/token_functions.hpp>
#include <boost/tokenizer.hpp>
#include <Plane.h>
#include <Sphere.h>
#include <Mesh.h>
#include "Loader.h"
#include "SceneObject.h"

/**
 * Reads and parses the scene file and places all scene objects
 * into a temporary std::vector. Then separates lights from
 * geometry objects. Meshes are discarded and instead their
 * triangles are kept
 */
void Loader::loadScene(const std::string &filename, std::vector<SceneObject*> &sceneObjects, std::vector<Light*> &lights,
                       Camera* &camera, boost::filesystem::path &scenePath) {

    std::ifstream input(filename);
    std::string line;
    bool isFirst = true;

    std::vector<SceneObject*> tempObjects;

    if(input.is_open()) {
        while (getline(input, line)) {
            if(isFirst) {
                isFirst = false;
            } else {
                parseLine(tempObjects, line, scenePath);
            }
        }
    }

    input.close();

    for(auto & object : tempObjects) {
        switch(object->type) {
            case SceneObject::camera:
                camera = (Camera*)object;
                break;
            case SceneObject::plane:
            case SceneObject::sphere:
                sceneObjects.push_back(object);
                break;
            case SceneObject::mesh:
                sceneObjects.insert(sceneObjects.end(), ((Mesh*)object)->getTriangles().begin(), ((Mesh*)object)->getTriangles().end());
                delete object;  //The Mesh* structure is no longer needed
                break;
            case SceneObject::light:
                lights.push_back((Light*)object);
                break;
        }
    }
}

void Loader::parseLine(std::vector<SceneObject*> &objects, std::string &line, boost::filesystem::path &scenePath) {
    boost::char_separator<char> sep(" ");
    boost::tokenizer< boost::char_separator<char> > tok(line, sep);
    std::vector<std::string> parts;
    for(boost::tokenizer< boost::char_separator<char> >::iterator beg = tok.begin(); beg != tok.end(); ++beg)
    {
        parts.push_back(*beg);
    }

    if(parts.size() > 0) {
        addToScene(objects, parts, scenePath);
    }
}

/**
 * String hashing function allows string
 * literals to be used with switch statement
 * sourced from
 * http://www.rioki.org/2016/03/31/cpp-switch-string.html
 */
constexpr unsigned int hash(const char *str, int h = 0) {
    return !str[h] ? 5381 : (hash(str, h+1)*33) ^ str[h];
}

void Loader::addToScene(std::vector<SceneObject*> &objects, std::vector<std::string> parts, boost::filesystem::path &scenePath) {
    switch(hash(parts[0].c_str())) {
        case hash("camera"): {
            Camera* camera = new Camera();
            objects.push_back(camera);
        }
            break;
        case hash("plane"): {
            Plane* plane = new Plane();
            objects.push_back(plane);
        }
            break;
        case hash("sphere"): {
            Sphere* sphere = new Sphere();
            objects.push_back(sphere);
        }
            break;
        case hash("mesh"):{
            Mesh* mesh = new Mesh();
            objects.push_back(mesh);
        }
            break;
        case hash("light"):{
            Light* light = new Light();
            objects.push_back(light);
        }
            break;
        default:
            setProperty(objects.back(), parts, scenePath);
            break;
    }
}

void Loader::setProperty(SceneObject* object, std::vector<std::string> data, boost::filesystem::path &scenePath) {

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
            object->setAmbient(glm::vec3(std::stof(data[1]), std::stof(data[2]), std::stof(data[3])));
            break;
        case hash("dif:"):
            object->setDiffuse(glm::vec3(std::stof(data[1]), std::stof(data[2]), std::stof(data[3])));
            break;
        case hash("spe:"):
            object->setSpecular(glm::vec3(std::stof(data[1]), std::stof(data[2]), std::stof(data[3])));
            break;
        case hash("shi:"):
            object->setShininess(std::stof(data[1]));
            break;
        case hash("file:"):
            ((Mesh*)object)->loadObj(data[1], scenePath);
            break;
        case hash("rad:"):
            ((Sphere*)object)->radius = std::stof(data[1]);
            break;
    }
}