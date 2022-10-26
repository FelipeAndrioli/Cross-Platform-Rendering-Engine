#pragma once

#include <iostream> 
#include <vector>
#include <string>

#include "../libs/assimp/include/assimp/Importer.hpp"
#include "../libs/assimp/include/assimp/scene.h"
#include "../libs/assimp/include/assimp/postprocess.h"
#include "../libs/glm/glm/glm.hpp"
#include "../libs/glm/glm/gtc/matrix_transform.hpp"

#include "../libs/glad/build/include/glad/glad.h"
#include "../libs/glfw/include/GLFW/glfw3.h"

#include "../src/util/transformations.h"
#include "../src/util/lighting.h"
#include "../src/util/settings.h"

#include "camera.h"
#include "mesh.h"

#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class Model {
    public:
        Model();
        Model(const char *path, std::string id, bool flip_texture);
        ~Model();
        
        std::string model_id;
        std::vector<Mesh> meshes;
        std::vector<Texture> textures_loaded;
        std::string directory;
       
        bool gamma_correction;
        bool stbi_flip_vertically; 

        float scale_handler;
        
        void onUpdate(Settings *settings, Camera *TheCamera);
        void setUniforms(Shader *shader);

        Transformations *model_transformations;
        TransformationsMatrices *transformations_matrices;
        BasicLight *basic_light;
        Shader *attached_shader;
        
        void generateCubeVertices();
        void debug();

    private:
        void loadModel(std::string path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType
            type, std::string typeName);
        unsigned int TextureFromFile(const char *path, const std::string 
                &directory, bool gamma = false);
        void onCreate();
};
