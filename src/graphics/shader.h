#ifndef SHADER_H
#define SHADER_H

#define GLM_FORCE_RADIANS

#include <string>
#include <algorithm>
#include <GL/glew.h>
#include <iostream>
#include <assert.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>



class Shader
{
private:
    std::string vertexPath, fragmentPath, geometryPath;
    GLuint vertexShader, fragmentShader, geometryShader;
    GLuint program;
    void compileShader(std::string path, GLuint& shaderHandle, GLenum shaderType);
    void checkForCompileErrors(GLuint &handle, GLenum type);
    const std::string getShaderSource(std::string path);
    bool initialized;
    std::string name = "[UNNAMED]";
    std::map<std::string,GLint> uniforms;
    GLint getUniformLocation(std::string name);

public:
    Shader(){}
    Shader(std::string vertexPath, std::string fragmentPath, std::string geometryPath = "");
    void bind();
    void unbind(){glUseProgram(0);}
    void initialize(std::string vertexPath, std::string fragmentPath, std::string geometryPath = "");

    void setName(std::string  name){this->name = name;}
    std::string getName(){return name;}

    void setUniform(std::string name, int data, int index = -1);
    void setUniform(std::string name, float data, int index = -1);
    void setUniform(std::string name, const glm::vec2 &data, int index = -1);
    void setUniform(std::string name, const glm::vec3 &data, int index = -1);
    void setUniform(std::string name, const glm::vec4 &data, int index = -1);
    void setUniform(std::string name, const glm::mat2 &data, int index = -1);
    void setUniform(std::string name, const glm::mat3 &data, int index= -1);
    void setUniform(std::string name, const glm::mat4 &data, int index = -1);

    void setStructUniform(std::string structName, std::string attributeName, int data, int index = -1);
    void setStructUniform(std::string structName, std::string attributeName, float data, int index = -1);
    void setStructUniform(std::string structName, std::string attributeName, const glm::vec2& data, int index = -1);
    void setStructUniform(std::string structName, std::string attributeName, const glm::vec3& data, int index = -1);
    void setStructUniform(std::string structName, std::string attributeName, const glm::vec4& data, int index = -1);
    void setStructUniform(std::string structName, std::string attributeName, const glm::mat2& data, int index = -1);
    void setStructUniform(std::string structName, std::string attributeName, const glm::mat3& data, int index = -1);
    void setStructUniform(std::string structName, std::string attributeName, const glm::mat4& data, int index = -1);

    void setStructArrayUniform(std::string structName, int structIndex, std::string attributeName, int data, int attributeIndex = -1);
    void setStructArrayUniform(std::string structName, int structIndex, std::string attributeName, float data, int attributeIndex = -1);
    void setStructArrayUniform(std::string structName, int structIndex, std::string attributeName, const glm::vec2& data, int attributeIndex = -1);
    void setStructArrayUniform(std::string structName, int structIndex, std::string attributeName, const glm::vec3& data, int attributeIndex = -1);
    void setStructArrayUniform(std::string structName, int structIndex, std::string attributeName, const glm::vec4& data, int attributeIndex = -1);
    void setStructArrayUniform(std::string structName, int structIndex, std::string attributeName, const glm::mat2& data, int attributeIndex = -1);
    void setStructArrayUniform(std::string structName, int structIndex, std::string attributeName, const glm::mat3& data, int attributeIndex = -1);
    void setStructArrayUniform(std::string structName, int structIndex, std::string attributeName, const glm::mat4& data, int attributeIndex = -1);

private:
    inline std::string makeIndexUniform(std::string name, int index){return name + "[" + std::to_string(index) + "]";}
};

#endif // SHADER_H
