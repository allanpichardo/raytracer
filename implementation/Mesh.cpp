//
// Created by Allan Pichardo on 2019-03-31.
//

#include "Mesh.h"
#include "OBJloader.h"
#include <boost/filesystem.hpp>
#include <Loader.h>

void Mesh::loadObj(std::string &filename, boost::filesystem::path &scenePath) {

    this->filename = scenePath.generic_string() + "/" + filename;

    std::vector<unsigned int> vertexIndices;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> uvs;

    if(loadOBJ(this->filename.c_str(), vertexIndices, vertices, normals, uvs)) {
        int v(0);
        for(auto& index : vertexIndices) {
            if(v % 3 == 0) {
                Triangle* triangle = new Triangle();
                triangle->ambient = ambient;
                triangle->diffuse = diffuse;
                triangle->specular = specular;
                triangle->shininess = shininess;
                triangles.push_back(triangle);
            }
            triangles.back()->vertices.push_back(vertices[index]);
            v++;
        }

        for(auto& triangle : triangles) {
            glm::vec3 ab = triangle->vertices[1] - triangle->vertices[0];
            glm::vec3 ac = triangle->vertices[2] - triangle->vertices[0];
            glm::vec3 bc = triangle->vertices[2] - triangle->vertices[1];
            triangle->normal = glm::normalize(glm::cross(ab, ac));
            triangle->area = glm::length(glm::cross(ab, ac)) / 2.0f;
        }
    } else {
        throw std::invalid_argument("Mesh could not be loaded");
    }
}

void Mesh::setAmbient(glm::vec3 ambient) {
    for(auto& triangle: triangles) {
        triangle->ambient = ambient;
    }
}

void Mesh::setDiffuse(glm::vec3 diffuse) {
    for(auto& triangle: triangles) {
        triangle->diffuse = diffuse;
    }
}

void Mesh::setSpecular(glm::vec3 specular) {
    for(auto& triangle: triangles) {
        triangle->specular = specular;
    }
}

void Mesh::setShininess(float shininess) {
    for(auto& triangle: triangles) {
        triangle->shininess = shininess;
    }
}