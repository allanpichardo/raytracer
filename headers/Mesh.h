/*
 * Allan Pichardo
 * #40051123
 *
 * COMP 371
 * Final Project
 */

#ifndef RAYTRACER_MESH_H
#define RAYTRACER_MESH_H

#include <glm/glm.hpp>
#include "SceneObject.h"
#include "Triangle.h"
#include <string>
#include <vector>
#include <boost/filesystem.hpp>

/**
 * Represents a mesh composed of triangles.
 * The mesh keeps a std::vector of its component
 * triangles
 */
class Mesh: public SceneObject {
public:

private:
    std::string filename;
    std::vector<Triangle*> triangles;

public:
    Mesh() {type = mesh;};

    /**
     * Open a .obj file and populate the std::vector
     * of its triangles.
     */
    void loadObj(std::string &filename, boost::filesystem::path &scenePath);

    inline std::string& getFilename() {return filename;};

    inline std::vector<Triangle*>& getTriangles() {return triangles;};

    void setAmbient(glm::vec3 ambient) override;

    void setDiffuse(glm::vec3 diffuse) override;

    void setSpecular(glm::vec3 specular) override;

    void setShininess(float shininess) override;
};

#endif //RAYTRACER_MESH_H
