/*
 * Allan Pichardo
 * #40051123
 *
 * COMP 371
 * Final Project
 */

#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H

#include <string>
#include <vector>
#include "Camera.h"
#include "SceneObject.h"
#include "Light.h"
#include "Pixel.h"
#include "Ray.h"
#include <boost/filesystem.hpp>

/**
 * Represents the whole scene. This class performs
 * all the raytracing calculations and renders
 * a bitmap image for output
 */
class Scene {
private:
    int width;
    int height;
    Camera* camera;
    std::vector<Light*> lights;
    std::vector<SceneObject*> sceneObjects;
    Pixel** screen;
    boost::filesystem::path scenePath;

public:
    const static int MAX_DEPTH = 10;

private:

    /**
     * Calculates the color at a given point of an
     * object
     */
    glm::vec3 getIlluminationAt(Ray &ray, SceneObject* &object, glm::vec3 &intersection);

    /**
     * Initialize the array of pixels that represent
     * the view screen
     */
    void initializeScreen();

    void deepCopy(const Scene& other);

    void deallocateResources();

    /**
     * Use raytracing to calculate the pixel color
     * at the given screen coordinates
     */
    inline void raytrace(int &x, int &y);

public:
    Scene() {camera = nullptr; screen = nullptr;};

    Scene(std::string filename) : Scene(0,0,filename) {};

    Scene(const Scene& other);

    Scene(unsigned int width, unsigned int height, const std::string &filename);

    ~Scene();

    Scene& operator=(const Scene& other);

    /**
     * Raytraces the image and outputs an image at the
     * given file path
     */
    void renderToImage(const char* filename);

    bool isSceneLoaded();

};

#endif //RAYTRACER_SCENE_H
