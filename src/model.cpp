#include "../include/model.h"

Model::Model() {
    // used to create custom models
    generateCubeVertices();
    onCreate();
}

Model::Model(const char *path, std::string id,bool flip_texture) {

    stbi_flip_vertically = flip_texture;
    model_id = id;
    is_lightsource = false;
    loadModel(path);
    onCreate();
}

void Model::onCreate() {
    model_transformations = new Transformations();
    scale_handler = 1.0f;
    model_transformations->translation = glm::vec3(0.0f, 0.0f, 0.0f);
    model_transformations->scalation = glm::vec3(scale_handler);
    model_transformations->rotation = glm::vec3(0.0f);

    light_source = nullptr;

    basic_light = new BasicLight();
    basic_light->ambient = 1.0f;
    basic_light->diffuse = 0.0f;
    basic_light->specular = 0.0f;

    transformations_matrices = new TransformationsMatrices();
    transformations_matrices->projection = glm::mat4(1.0f);
    transformations_matrices->view = glm::mat4(1.0f);
    transformations_matrices->model = glm::mat4(1.0f);

    color = new Color();
    color->r = 0.7f;
    color->g = 0.7f;
    color->b = 0.7f;
    color->a = 0.7f;
}

Model::~Model() {
    std::cout << "Destroying Model..." << std::endl;
    delete model_transformations;
    delete transformations_matrices;
    delete basic_light;
}

void Model::onUpdate(Settings *settings, Camera *TheCamera) {
    transformations_matrices->projection = glm::perspective(TheCamera->Zoom, 
        (float)settings->resolution.x/(float)settings->resolution.y, 
        settings->near, settings->far);
    transformations_matrices->view = TheCamera->getViewMatrix();
 
    transformations_matrices->model = glm::mat4(1.0f);

    model_transformations->scalation = glm::vec3(scale_handler);
    transformations_matrices->model = glm::scale(transformations_matrices->model, 
        model_transformations->scalation);
    transformations_matrices->model = glm::translate(transformations_matrices->model,
        model_transformations->translation);
    transformations_matrices->model = glm::rotate(transformations_matrices->model, 
        model_transformations->rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    transformations_matrices->model = glm::rotate(transformations_matrices->model, 
        model_transformations->rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    transformations_matrices->model = glm::rotate(transformations_matrices->model, 
        model_transformations->rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

    if (is_lightsource) {
        light_source->color = glm::vec3(color->r, color->g, color->b);
        light_source->position = model_transformations->translation;
    }
}

void Model::debug() {
    std::cout << "Meshes size -> " << meshes.size() << std::endl;

    for (int i = 0; i < meshes.size(); i++) {
        for (int j = 0; j < meshes[i].vertices.size(); j++) {
            std::cout << "Position" << std::endl;
            std::cout << meshes[i].vertices[j].Position.x << " ";
            std::cout << meshes[i].vertices[j].Position.y << " ";
            std::cout << meshes[i].vertices[j].Position.z << " ";
            std::cout << std::endl;

            std::cout << "Normals" << std::endl;
            std::cout << meshes[i].vertices[j].Normal.x << " ";
            std::cout << meshes[i].vertices[j].Normal.y << " ";
            std::cout << meshes[i].vertices[j].Normal.z << " ";
            std::cout << std::endl;
        }

        std::cout << "Indices" << std::endl;
        for (int j = 0; j < meshes[i].indices.size(); j++) {
            std::cout << meshes[i].indices[j] << " ";
        }
        std::cout << std::endl;
    }
}

void Model::setUniforms(std::vector<LightSource*> light_sources, Camera *TheCamera) {
    attached_shader->use();
    attached_shader->setMat4("projection", transformations_matrices->projection);
    attached_shader->setMat4("view", transformations_matrices->view);
    attached_shader->setMat4("model", transformations_matrices->model);

    if (!light_source) {
        attached_shader->setFloat("light.ambient", basic_light->ambient);
        attached_shader->setFloat("light.diffuse", basic_light->diffuse);
        attached_shader->setFloat("light.specular", basic_light->specular);
        attached_shader->setFloat("light.shininess", basic_light->shininess);

        attached_shader->setVec3("material.color", glm::vec3(color->r, color->g, color->b));

        attached_shader->setVec3("viewPos", TheCamera->Position);

        for (int i = 0; i < light_sources.size(); i++) {
            attached_shader->setVec3("lightSource[" + std::to_string(i) + "].position", light_sources.at(i)->position);
            attached_shader->setVec3("lightSource[" + std::to_string(i) + "].color", light_sources.at(i)->color);
        }
    } else {
        attached_shader->setVec3("light_color", light_source->color);
    }
}

void Model::turnIntoLightsource(std::string id) {
    light_source = new LightSource();
    light_source->id = id;
    light_source->enable = true;
    light_source->color = glm::vec3(1.0f, 1.0f, 1.0f);
    light_source->position = model_transformations->translation;
    is_lightsource = true;
}

void Model::generateCubeVertices() {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    /* TODO
     *
     * - Refactor all of this and make it automatic instead of hard coded
     *      - Automate positions -> follow binary permutations seems to work
     *      - Automate normals -> need to understand how these normals are calculated
     *      - Automate indices -> need to understand how to generate automated indices
     * - The normals ARE be wrong
     * */


    Vertex vertex;
    vertex.Position = glm::vec3(-0.5f, -0.5f, 0.5f);    // 0
    vertex.Normal = glm::vec3(1.0f, 0.0f, 0.0f);
    vertex.TexCoords = glm::vec2(0.0f, 0.0f);
    vertices.push_back(vertex);
    vertex.Position = glm::vec3(0.5f, -0.5f, 0.5f);     // 1
    vertex.Normal = glm::vec3(0.0f, 1.0f, 0.0f);
    vertex.TexCoords = glm::vec2(0.0f, 0.0f);
    vertices.push_back(vertex);
    vertex.Position = glm::vec3(-0.5f, 0.5f, 0.5f);     // 2
    vertex.Normal = glm::vec3(1.0f, 0.0f, 0.0f);
    vertex.TexCoords = glm::vec2(0.0f, 0.0f);
    vertices.push_back(vertex);
    vertex.Position = glm::vec3(0.5f, 0.5f, 0.5f);      // 3
    vertex.Normal = glm::vec3(0.0f, 0.0f, -1.0f);
    vertex.TexCoords = glm::vec2(0.0f, 0.0f);
    vertices.push_back(vertex);
    vertex.Position = glm::vec3(-0.5f, -0.5f, -0.5f);   // 4
    vertex.Normal = glm::vec3(0.0f, 0.0f, 1.0f);
    vertex.TexCoords = glm::vec2(0.0f, 0.0f);
    vertices.push_back(vertex);
    vertex.Position = glm::vec3(0.5f, -0.5f, -0.5f);    // 5
    vertex.Normal = glm::vec3(0.0f, -1.0f, 0.0f);
    vertex.TexCoords = glm::vec2(0.0f, 0.0f);
    vertices.push_back(vertex);
    vertex.Position = glm::vec3(-0.5f, 0.5f, -0.5f);    // 6
    vertex.Normal = glm::vec3(0.0f, 0.0f, -1.0f);
    vertex.TexCoords = glm::vec2(0.0f, 0.0f);
    vertices.push_back(vertex);
    vertex.Position = glm::vec3(0.5f, 0.5f, -0.5f);     // 7
    vertex.Normal = glm::vec3(-1.0f, 0.0f, 0.0f);
    vertex.TexCoords = glm::vec2(0.0f, 0.0f);
    vertices.push_back(vertex);

    indices.push_back(2);
    indices.push_back(6);
    indices.push_back(7);
    indices.push_back(2);
    indices.push_back(3);
    indices.push_back(7);
   
    indices.push_back(0);
    indices.push_back(4);
    indices.push_back(5);
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(5);
    
    indices.push_back(0);
    indices.push_back(2);
    indices.push_back(6);
    indices.push_back(0);
    indices.push_back(4);
    indices.push_back(6);

    indices.push_back(1);
    indices.push_back(3);
    indices.push_back(7);
    indices.push_back(1);
    indices.push_back(5);
    indices.push_back(7);

    indices.push_back(0);
    indices.push_back(2);
    indices.push_back(3);
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(3);

    indices.push_back(4);
    indices.push_back(6);
    indices.push_back(7);
    indices.push_back(4);
    indices.push_back(5);
    indices.push_back(7);

    Mesh *new_mesh = new Mesh(vertices, indices, textures);
    meshes.push_back(*new_mesh);
}

void Model::loadModel(std::string path) {
    // read file via ASSIMP
    Assimp::Importer importer;

    const aiScene *scene = importer.ReadFile(path, 
            aiProcess_Triangulate | 
            aiProcess_FlipUVs | 
            aiProcess_GenSmoothNormals | 
            aiProcess_CalcTangentSpace);

    // check for errors
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }

    // retrieve the directory path of the filepath
    directory = path.substr(0, path.find_last_of('/'));

    // process ASSIMP's root node recursively
    Model::processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene) {
    // process all the node's meshes (if any)
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        // the node object only contains indices to index the actual objects
        // in the scene. The scene contains all the data, node is just to keep
        // stuff organized (like relations between nodes).
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }

    // after we've processed all of the meshes (if any) we then recursively
    // process each of the children nodes
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene) {
    // data to fill
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    // walk through each of the mesh's vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;
        // process vertex positions, normals and texture coordinates
        glm::vec3 util_vector;

        // posisions
        util_vector.x = mesh->mVertices[i].x;
        util_vector.y = mesh->mVertices[i].y;
        util_vector.z = mesh->mVertices[i].z;
        vertex.Position = util_vector; 

        if (mesh->HasNormals()) {
            util_vector.x = mesh->mNormals[i].x;
            util_vector.y = mesh->mNormals[i].y;
            util_vector.z = mesh->mNormals[i].z;
            vertex.Normal = util_vector;
        }

        // does the mesh contain texture coordinates?
        if (mesh->mTextureCoords[0]) {
            // a vertex can contain up to 8 different texture coordinates. We
            // thus make the assumption that we won't use models where a 
            // vertex can have multiple texture coordinates so we always take
            // the first set (0).
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;

            // tangent
            util_vector.x = mesh->mTangents[i].x;
            util_vector.y = mesh->mTangents[i].y;
            util_vector.z = mesh->mTangents[i].z;
            vertex.Tangent = util_vector;

            // bitangent
            util_vector.x = mesh->mBitangents[i].x;
            util_vector.y = mesh->mBitangents[i].y;
            util_vector.z = mesh->mBitangents[i].z;
            vertex.Bitangent = util_vector;
        } else {
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        }
        
        vertices.push_back(vertex);
    }

    // now we walk through each of the mesh's faces ( a face is a mesh its
    // triangle) and retrieve the corresponding vertex indices.
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];

        // retrieve all indices of the face and store them in the indices
        // vector.
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    // process material
    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
    // we assume a convention for sampler names in the shaders. Each diffuse
    // texture should be named as 'texture_diffuseN' where N is a sequential
    // number ranging from 1 to MAX_SAMPLER_NUMBER.
    // Same applies to other texture as the following list summarizes:
    // diffuse: texture_diffuseN
    // specular: texture_specularN
    // normal: texture_normalN
   
    // 1. diffuse maps 
    std::vector<Texture> diffuseMaps = loadMaterialTextures(material, 
            aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
       
    // 2. specular maps
    std::vector<Texture> specularMaps = loadMaterialTextures(material, 
            aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    // 3. normal maps
    std::vector<Texture> normalMaps = loadMaterialTextures(material, 
            aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

    // 4. height maps
    // Note -> Need to review 3 and 4 texture types names
    std::vector<Texture> heightMaps = loadMaterialTextures(material, 
            aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    // return a mesh object created from the extracted mesh data
    return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType
        type, std::string typeName) {

    std::vector<Texture> textures;

    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
        aiString util_str;
        mat->GetTexture(type, i, &util_str);
        // check if texture was loaded before and if so, continue next 
        // iteration: skip loading a new texture
        bool skip = false;
       
        for (unsigned int j = 0; j < textures_loaded.size(); j++) {
            if (textures_loaded[j].type == typeName) {
                textures.push_back(textures_loaded[j]);
                skip = true;
                break;
            }
        }

        if (!skip) {
            Texture texture;
            texture.id = TextureFromFile(util_str.C_Str(), directory);
            texture.type = typeName;
            texture.path = util_str.C_Str();
            textures.push_back(texture);
            textures_loaded.push_back(texture);
        } 
    }

    return textures;
}

unsigned int Model::TextureFromFile(const char *path, const std::string
        &directory, bool gamma) {

    stbi_set_flip_vertically_on_load(stbi_flip_vertically);
    std::string filename = std::string(path);
    filename = directory + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width;
    int height;
    int nrComponents;

    unsigned char *data = stbi_load(filename.c_str(), &width, &height, 
        &nrComponents, 0);

    if (data) {
        GLenum format;
        if (nrComponents == 1) {
            format = GL_RED;
        } else if (nrComponents == 3) {
            format = GL_RGB;
        } else if (nrComponents == 4) {
            format = GL_RGBA;
        }

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
                GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    } else {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        fprintf(stderr, "Cannot load file image %s\nSTB Reason: %s\n", 
            filename.c_str(), stbi_failure_reason());
        stbi_image_free(data);
    }

    return textureID;
}

glm::vec3 calculateModelPosition() {
    //TODO finish this function
    return glm::vec3(1.0f, 1.0f, 1.0f);
} 
