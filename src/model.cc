#define TINYOBJLOADER_IMPLEMENTATION
#include "../include/tiny_obj_loader.h"
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include "../include/main.h"

bool loadOBJ(const std::string& filename, std::vector<Vertex>& outVertices) {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filename.c_str())) {
        std::cerr << warn << err << std::endl;
        return false;
    }

    for (auto& shape : shapes) {
        for (auto& index : shape.mesh.indices) {
            Vertex v{};
            v.position = {
                attrib.vertices[3*index.vertex_index+0],
                attrib.vertices[3*index.vertex_index+1],
                attrib.vertices[3*index.vertex_index+2]
            };
            if (index.normal_index >= 0) {
                v.normal = {
                    attrib.normals[3*index.normal_index+0],
                    attrib.normals[3*index.normal_index+1],
                    attrib.normals[3*index.normal_index+2]
                };
            } else {
                v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
            }
            if (index.texcoord_index >= 0) {
                v.texcoord = {
                    attrib.texcoords[2*index.texcoord_index+0],
                    attrib.texcoords[2*index.texcoord_index+1]
                };
            } else {
                v.texcoord = glm::vec2(0.0f, 0.0f);
            }
            outVertices.push_back(v);
        }
    }
    return true;
}
