#pragma once

#include <iostream> 
#include <vector>
#include <string>

#include "../libs/assimp/include/assimp/Importer.hpp"
#include "../libs/assimp/include/assimp/scene.h"
#include "../libs/assimp/include/assimp/postprocess.h"

#include "stb_image.h"

#include "../libs/glad/build/include/glad/glad.h"
#include "../libs/glfw/include/GLFW/glfw3.h"

#include "mesh.h"
#include "texture.h"

class Model {
    public:
        Model(const char *path);
        ~Model();
        std::vector<Mesh> meshes;
        std::vector<Texture> loaded_textures;
        std::string directory;
        bool gamma_correction;
        void Draw(Shader &shader);
    private:
        void loadModel(std::string path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType
                type, std::string typeName);
        unsigned int TextureFromFile(const char *path, const std::string 
                &directory, bool gamma = false);
};
