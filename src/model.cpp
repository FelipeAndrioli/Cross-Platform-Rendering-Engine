#include "../include/model.h"

Model::Model(const char *path, std::string id,bool flip_texture) {

    stbi_flip_vertically = flip_texture;
    model_id = id;
    loadModel(path);

    model_transformations = new Transformations();
    scale_handler = 1.0f;
    model_transformations->translation = glm::vec3(0.0f, 0.0f, 0.0f);
    model_transformations->scalation = glm::vec3(scale_handler);
    model_transformations->rotation = glm::vec3(0.0f);

    polygon_mode = GL_FILL;
    polygon_face = GL_FRONT_AND_BACK;
}

Model::~Model() {
    std::cout << "Destroying Model..." << std::endl;
    delete model_transformations;
}

void Model::Draw(Shader &shader) {

    /*
     polygon mode

     mode
        - GL_POINT
        - GL_LINE
        - GL_FILL
     face
        - GL_FRONT
        - GL_BACK
        - GL_FRONT_AND_BACK
     */
    
    //glPolygonMode(GL_FILL, GL_FRONT_AND_BACK);

    glPolygonMode(polygon_mode, polygon_face); 
    glEnable(GL_DEPTH_TEST);
    for(unsigned int i = 0; i < meshes.size(); i++) {
        meshes[i].Draw(shader);
    }
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
