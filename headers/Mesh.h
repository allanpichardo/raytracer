//
// Created by Allan Pichardo on 2019-03-31.
//

#ifndef RAYTRACER_MESH_H
#define RAYTRACER_MESH_H

#include <glm/glm.hpp>
#include "SceneObject.h"
#include "Triangle.h"
#include <string>
#include <vector>
#include <boost/filesystem.hpp>

class Mesh: public SceneObject {
public:

private:
    std::string filename;
    std::vector<Triangle*> triangles;

public:
    Mesh() {type = mesh;};
    void loadObj(std::string &filename, boost::filesystem::path &scenePath);
    inline std::string& getFilename() {return filename;};
    inline std::vector<Triangle*>& getTriangles() {return triangles;};
    void setAmbient(glm::vec3 ambient) override;
    void setDiffuse(glm::vec3 diffuse) override;
    void setSpecular(glm::vec3 specular) override;
    void setShininess(float shininess) override;
};

#endif //RAYTRACER_MESH_H
