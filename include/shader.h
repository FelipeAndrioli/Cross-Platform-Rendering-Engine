#pragma once

#include <iostream>

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

//#include <glm/glm.hpp>
#include "../libs/glm/glm/glm.hpp"
#include "../libs/glad/build/include/glad/glad.h"

/* Shader Class
 *
 * Function:
 *  Load the shaders path, compile and link them to a shader program.
 *  Set the shader as active or inactive (use/end).
 *  Set uniforms to the shaders.
 *
 * */

 class Shader {
    public:
        Shader();
        Shader(const char* vertexShaderPath, const char* fragmentShaderPath, const char* geometryShaderPath);
        unsigned int ID;
        void use();
        void end();
        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setFloat(const std::string &name, float value) const;
        void setDouble(const std::string &name, double value) const;
        void setVec2(const std::string &name, const glm::vec2 &value) const;
        void setVec2(const std::string &name, float x, float y) const;
        void setVec3(const std::string &name, const glm::vec3 &value) const;
        void setVec3(const std::string &name, float x, float y, float z) const;
        void setVec4(const std::string &name, const glm::vec4 &value) const;
        void setVec4(const std::string &name, float x, float y, float z, float w) const;
        void setMat2(const std::string &name, const glm::mat2 &mat2) const;
        void setMat3(const std::string &name, const glm::mat3 &mat3) const;
        void setMat4(const std::string &name, const glm::mat4 &mat4) const;
   private:
        void checkCompileErrors(unsigned int ID, std::string type);
};
