#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "../libs/glm/glm/glm.hpp"
//#include "../libs/glad/build/include/glad/glad.h"
#include "../libs/glad/include/glad/glad.h"

#include "./shader.h"

#define MAX_BONE_INFLUENCE 4

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
    int m_BoneIDs[MAX_BONE_INFLUENCE];
    int m_Weights[MAX_BONE_INFLUENCE];
};

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh {
    public:
        Mesh();
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, 
            std::vector<Texture> textures);
        ~Mesh();
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;
        unsigned int VAO;       
        unsigned int VBO;       
        unsigned int EBO;       
        void setupMesh();
};
