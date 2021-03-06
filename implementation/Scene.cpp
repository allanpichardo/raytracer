/*
 * Allan Pichardo
 * #40051123
 *
 * COMP 371
 * Final Project
 */

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
#include "Ray.h"
#include <future>
#include <boost/filesystem.hpp>
#include <cstdlib>
#include <ctime>
#include "ProgressBar.hpp"

/**
 * Loads the scene file and initializes all
 * data structures with the corresponding properties.
 */
Scene::Scene(unsigned int width, unsigned int height, const std::string &filename) {

    this->width = width;
    this->height = height;

    size_t found;
    found=filename.find_last_of("/\\");
    this->scenePath = boost::filesystem::path(filename.substr(0,found));

    Loader::loadScene(filename, sceneObjects, lights, camera, scenePath);

    if(isSceneLoaded()) {
        camera->initializeCoordinateSystem();
        if(width == 0 && height == 0) {
            this->width = (int)camera->getViewWidth();
            this->height = (int)camera->getViewHeight();
        }
        initializeScreen();
    } else {
        throw std::invalid_argument("Unable to load the scene");
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

/**
 * Creates 2 threads per logical core on the CPU to perform
 * the raytracing task. For each pixel on screen, the color
 * is calculated by calling the raytrace(x,y) function. After
 * all pixel colors are computed, the image is rendered to
 * screen and saved to disk at the given file path.
 */
void Scene::renderToImage(const char* filename) {
    unsigned int threads = std::thread::hardware_concurrency() * 2;
    int max = width * height;

    //These atomic integers are necessary to
    //keep track of which pixels have been
    //completed while avoiding race conditions
    //from the threads
    volatile std::atomic<int> count(0);
    volatile std::atomic<int> progress(0);

    ProgressBar progressBar(max, 70); //progress bar is for information purposes
    std::vector<std::future<void>> futures;
    futures.reserve(threads);

    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    std::cout << "Raytracing started with " << threads << " threads:" << std::endl;

    for(int i = 0; i < threads; i++) {
        futures.push_back(std::async(std::launch::async, [=, &threads, &count, &progress, &progressBar]() {
            while(true) {
                int index = count++;
                if(index >= max) {
                    break;
                }

                int x = index % width;
                int y = floor(index / width);

                raytrace(x, y); //actual color computation
                progress++;
            }
        }));
    }

    while (progress < max){
        progressBar.setTicks(progress);
        progressBar.display();
    }
    progressBar.display();
    progressBar.done();

    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end-start;
    std::cout << "Completed in " << elapsed.count() << " seconds." << std::endl;
    std::cout << "Saving image " << filename << std::endl;

    cimg_library::CImg<float> image(width, height, 1, 3, 0);
    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {
            image(i,j,0) = screen[j][i].color.x * 255.0f;
            image(i,j,1) = screen[j][i].color.y * 255.0f;
            image(i,j,2) = screen[j][i].color.z * 255.0f;
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

/**
 * Since all the scene objects are allocated
 * on the heap, and there may be hundreds
 * of them, they have to be destructed
 * under different scenarios
 */
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
                ((Mesh*)o)->loadObj(((Mesh*)other.sceneObjects[i])->getFilename(), this->scenePath);
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

void Scene::raytrace(int &x, int &y) {
    Ray ray = Ray::toPixel(*camera, screen[y][x]);
    //depth is initialized at +Infinity
    float depth = HUGE_VALF;
    for(auto & sceneObject : sceneObjects) {
        glm::vec3 intersection;
        //To avoid recomputing the depth
        //a reference is used to reuse the value
        //that was already computed during the
        //intersection test
        float d;
        if(ray.intersects(sceneObject, intersection, d)) {
            if(d < depth) {
                screen[y][x].color = getIlluminationAt(ray, sceneObject, intersection);
                depth = d;
            }
        }
    }
}

glm::vec3 Scene::getIlluminationAt(Ray &ray, SceneObject* &object, glm::vec3 &intersection) {
    glm::vec3 normal;
    float bias = 0.0001f;

    switch(object->type) {
        case SceneObject::plane:
        case SceneObject::triangle:
            normal = object->normal;
            break;
        case SceneObject::sphere:
            normal = glm::normalize(intersection - object->position);
            break;
        default:
            return glm::vec3(0.0f);
    }

    glm::vec3 lightContribution = glm::vec3(0.0f);
    for(auto & light : lights) {
        Ray shadowRay = Ray::toObject(intersection, light->position, bias);
        if(!shadowRay.isLightBlockedBy(object, light, sceneObjects)) {
            glm::vec3 l = shadowRay.direction;
            glm::vec3 r = (2.0f * glm::dot(l, normal) * normal) - l;
            glm::vec3 v = (camera->position != intersection) ? glm::normalize(camera->position - intersection) : glm::vec3(0.0f);

            float ln = fmax(0.0f, glm::dot(l,normal));
            float rv = fmax(0.0f, glm::dot(r,v));

            glm::vec3 dif = object->diffuse * light->diffuse * ln;
            glm::vec3 spe = object->specular * light->specular * pow(rv,object->shininess);

            lightContribution += (dif + spe);
        }
    }

    glm::vec3 color = object->ambient + lightContribution;

    return glm::clamp(color, 0.0f, 1.0f);
}
