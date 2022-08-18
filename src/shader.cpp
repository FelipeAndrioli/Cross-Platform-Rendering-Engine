#include "../include/shader.h"

#include <iostream>

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath, const char* geometryShaderPath = nullptr) {
    std::string vertexShaderCode;
    std::string fragmentShaderCode;
    std::string geometryShaderCode;
    std::ifstream vertexShaderFile;
    std::ifstream fragmentShaderFile;
    std::ifstream geometryShaderFile;

    vertexShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fragmentShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    geometryShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    try {
        vertexShaderFile.open(vertexShaderPath);
        fragmentShaderFile.open(fragmentShaderPath);

        std::stringstream vShaderStream;
        std::stringstream fShaderStream;

        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();

        vertexShaderFile.close();
        fragmentShaderFile.close();

        vertexShaderCode = vShaderStream.str();
        fragmentShaderCode = fShaderStream.str();

        if (geometryShaderPath != nullptr) {
            geometryShaderFile.open(geometryShaderPath);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryShaderCode = gShaderStream.str();
        }

    } catch (std::ifstream::failure &e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
    }

    const char* vShaderCode = vertexShaderCode.c_str();
    const char* fShaderCode = fragmentShaderCode.c_str();
    const char* gShaderCode = nullptr;

    unsigned int VertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(VertexShader, 1, &vShaderCode, nullptr);
    glCompileShader(VertexShader);
    checkCompileErrors(VertexShader, "VERTEX");
   
    unsigned int FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(FragmentShader, 1, &fShaderCode, nullptr);
    glCompileShader(FragmentShader);
    checkCompileErrors(FragmentShader, "FRAGMENT");
    
    ID = glCreateProgram();

    glAttachShader(ID, VertexShader);
    glAttachShader(ID, FragmentShader);

    if (geometryShaderPath != nullptr) {
        gShaderCode = geometryShaderCode.c_str();
    
        unsigned int GeometryShader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(GeometryShader, 1, &gShaderCode, nullptr);
        glCompileShader(GeometryShader);
        checkCompileErrors(GeometryShader, "GEOMETRY");
        glAttachShader(ID, GeometryShader);
    }

    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");

    glDeleteShader(VertexShader);
    glDeleteShader(FragmentShader);

};

void Shader::checkCompileErrors(unsigned int ID, std::string type) {
    int success;
    char infoLog[1024];

    if (type != "PROGRAM") {
        glGetShaderiv(ID, GL_COMPILE_STATUS, &success);

        if (!success) {
            glGetShaderInfoLog(ID, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << std::endl;
        }
    } else {
        glGetProgramiv(ID, GL_LINK_STATUS, &success);

        if (!success) {
            glGetProgramInfoLog(ID, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR" << "\n" << infoLog << std::endl;
        }
    }
}

void Shader::use() {
    glUseProgram(ID);
}

void Shader::end() {
    glDeleteProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setDouble(const std::string &name, double value) const {
    glUniform1d(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec2(const std::string &name, const glm::vec2 &value) const {
    glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec2(const std::string &name, float x, float y) const {
    glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}

void Shader::setVec3(const std::string &name, const glm::vec3 &value) const {
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec3(const std::string &name, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void Shader::setVec4(const std::string &name, const glm::vec4 &value) const {
    glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setMat2(const std::string &name, const glm::mat2 &mat2) const {
    glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat2[0][0]);
}

void Shader::setMat3(const std::string &name, const glm::mat3 &mat3) const {
    glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat3[0][0]);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat4) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat4[0][0]);
}





