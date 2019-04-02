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
#include "Pixel.h"

class Scene {
private:
    int width;
    int height;
    Camera* camera;
    std::vector<Light*> lights;
    std::vector<SceneObject*> sceneObjects;
    Pixel** screen;

private:
    void initializeScreen();
    void deepCopy(const Scene& other);
    void deallocateResources();
    void raytrace();

public:
    Scene() {camera = nullptr; screen = nullptr;};
    Scene(std::string filename) : Scene(0,0,filename) {};
    Scene(const Scene& other);
    Scene(unsigned int width, unsigned int height, const std::string &filename);
    ~Scene();
    Scene& operator=(const Scene& other);
    void renderToImage(const char* filename);
    bool isSceneLoaded();
};

#endif //RAYTRACER_SCENE_H
