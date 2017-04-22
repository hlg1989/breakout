#include "Shader.h"
#include "ShaderType.h"
#include "FileManager.h"
#include <GL/glew.h>
#include <iostream>
#include <string>
#include <stdexcept>

Shader::Shader(ShaderType type, const std::string& path) {
    std::cout << "Shader constructor" << std::endl;

    std::string source = FileManager::Instance().readAsText(path);

    this->id = glCreateShader(type);

    const GLchar* shaderSource = source.c_str();
    glShaderSource(this->id, 1, &shaderSource, nullptr);
    glCompileShader(this->id);

    this->checkCompilationStatus();
}

Shader::~Shader() {
    std::cout << "Shader destructor" << std::endl;
    glDeleteShader(this->id);
}

GLuint Shader::getId() const {
    return this->id;
}

void Shader::checkCompilationStatus() {
    GLint success;
    glGetShaderiv(this->id, GL_COMPILE_STATUS, &success);

    if (!success) {
        GLint LOG_LENGTH;
        glGetShaderiv(this->id, GL_INFO_LOG_LENGTH, &LOG_LENGTH);

        GLchar errorLog[LOG_LENGTH];

        glGetShaderInfoLog(this->id, LOG_LENGTH, nullptr, errorLog);
        std::cerr << errorLog << std::endl;
        throw std::runtime_error("Shader compilation failed");
    }
}
