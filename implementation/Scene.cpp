//
// Created by Allan Pichardo on 2019-03-31.
//

#include "Scene.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <boost/tokenizer.hpp>
#include "SceneObject.h"
#include "Plane.h"
#include "Sphere.h"
#include "Mesh.h"
#include "Light.h"
#include "Loader.h"
#include <CImg.h>

Scene::Scene(unsigned int width, unsigned int height, const std::string &filename) {

    this->width = width;
    this->height = height;

    Loader::loadScene(filename, sceneObjects, lights, camera);

    if(isSceneLoaded()) {
        camera->initializeCoordinateSystem();
        if(width == 0 && height == 0) {
            this->width = (int)camera->getViewWidth();
            this->height = (int)camera->getViewHeight();
        }
        initializeScreen();
    } else {
        throw "Unable to load the scene";
    }
}

Scene::~Scene() {
    deallocateResources();
}

void Scene::initializeScreen() {
    screen = new Pixel*[height];
    for(int i = 0; i < height; i++) {
        screen[i] = new Pixel[width];
    }

    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            screen[i][j].initialize(width, height, j, i, camera);
        }
    }
}

bool Scene::isSceneLoaded() {
    return camera != nullptr && sceneObjects.size() > 0 && lights.size() > 0;
}

void Scene::renderToImage(const char* filename) {
    cimg_library::CImg<float> image(width, height, 1, 3, 0);
    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {
            image(i,j,0) = screen[j][i].color.x;
            image(i,j,1) = screen[j][i].color.y;
            image(i,j,2) = screen[j][i].color.z;
        }
    }
    image.save(filename);

    cimg_library::CImgDisplay main_disp(image, "Render");
    while(!main_disp.is_closed()) {
        main_disp.wait();
    }
}

Scene &Scene::operator=(const Scene& other) {
    if(this != &other) {
        deallocateResources();
        deepCopy(other);
    }
    return *this;
}

Scene::Scene(const Scene &other) {
    deepCopy(other);
}

void Scene::deallocateResources() {
    for(int i = 0; i < sceneObjects.size(); i++) {
        delete sceneObjects[i];
    }
    sceneObjects.clear();

    for(int i = 0; i < lights.size(); i++) {
        delete lights[i];
    }
    lights.clear();

    if(screen != nullptr) {
        delete camera;
        camera = nullptr;

        for(int i = 0; i < height; i++) {
            if(screen[i] != nullptr) {
                delete[] screen[i];
            }
        }
    }
}

void Scene::deepCopy(const Scene& other) {
    width = other.width;
    height = other.height;

    camera = new Camera();
    camera->type = SceneObject::Type::camera;
    camera->position = other.camera->position;
    camera->focalLength = other.camera->focalLength;
    camera->fieldOfView = other.camera->fieldOfView;
    camera->aspectRatio = other.camera->aspectRatio;
    camera->initializeCoordinateSystem();

    sceneObjects = std::vector<SceneObject*>();
    for(int i = 0; i < other.sceneObjects.size(); i++) {
        SceneObject* o;
        switch(other.sceneObjects[i]->type) {
            case SceneObject::Type::camera:
            case SceneObject::Type::light:
                continue;
            case SceneObject::Type::mesh:
                o = new Mesh();
                ((Mesh*)o)->filename = ((Mesh*)other.sceneObjects[i])->filename;
                break;
            case SceneObject::Type::sphere:
                o = new Sphere();
                break;
            case SceneObject::Type::plane:
                o = new Plane();
                break;
        }
        o->ambient = other.sceneObjects[i]->ambient;
        o->type = other.sceneObjects[i]->type;
        o->position = other.sceneObjects[i]->position;
        o->shininess = other.sceneObjects[i]->shininess;
        o->specular = other.sceneObjects[i]->specular;
        o->diffuse = other.sceneObjects[i]->diffuse;
        o->normal = other.sceneObjects[i]->normal;
    }

    lights = std::vector<Light*>();
    for(int i = 0; i < other.lights.size(); i++) {
        Light* o = new Light();
        o->ambient = other.lights[i]->ambient;
        o->type = other.lights[i]->type;
        o->position = other.lights[i]->position;
        o->shininess = other.lights[i]->shininess;
        o->specular = other.lights[i]->specular;
        o->diffuse = other.lights[i]->diffuse;
        o->normal = other.lights[i]->normal;
    }

    initializeScreen();
}
