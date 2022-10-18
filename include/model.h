#pragma once

#include <iostream> 
#include <vector>
#include <string>

#include "../libs/assimp/include/assimp/Importer.hpp"
#include "../libs/assimp/include/assimp/scene.h"
#include "../libs/assimp/include/assimp/postprocess.h"

#include "../libs/glad/build/include/glad/glad.h"
#include "../libs/glfw/include/GLFW/glfw3.h"

#include "../src/util/transformations.h"

#include "../src/ui/ui_model.h"

#include "mesh.h"

#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class Model {
    public:
        Model(const char *path, std::string id, bool flip_texture);
        ~Model();
        
        std::vector<Mesh> meshes;
        std::vector<Texture> textures_loaded;
        std::string directory;
       
        bool gamma_correction;
        bool stbi_flip_vertically; 
       
        std::string model_id;

        void enableFeature(GLenum feature);
        void disableFeature(GLenum feature);
        void Draw(Shader &shader);

        Transformations *model_transformations;
        float scale_handler;

        GLenum polygon_mode;
        GLenum polygon_face;
        bool depth_test;
    private:
        void loadModel(std::string path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType
            type, std::string typeName);
        unsigned int TextureFromFile(const char *path, const std::string 
                &directory, bool gamma = false);
};
