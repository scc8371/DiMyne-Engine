#ifndef SHADER_H
#define SHADER_H

#include <opengl/opengl.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cerrno>

#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/type_ptr.hpp>

/// @brief Reads a file and returns its contents
/// @param filename file path
/// @return file contents
std::string get_file_contents(const char* filename);

class Shader
{
public:
    /// @brief GLuint ID of the shader
    GLuint ID;
    
    /// @brief VAO binded to the shader
    static GLuint VAO;

    /// @brief Creates a new Shader object 
    /// @param vertexPath file path of the vertex shader
    /// @param fragmentPath file path of the fragment shader
    Shader(const char* vertexPath, const char* fragmentPath);

    /// @brief Uses the shader
    void use();

    /// @brief Deletes the shader
    void del();

    /// @brief Links an attribute to a VBO to be used in the shader
    /// @param vbo vbo to be linked
    /// @param layout layout location of the attribute
    /// @param numComponents number of components of the attribute
    /// @param type type of the attribute (GL_FLOAT, GL_INT, etc.)
    /// @param stride stride of the attribute (0 if no stride)
    /// @param offset offset of the attribute (0 if no offset)
    void linkAttrib(GLuint vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);

    /// @brief Links a matrix4 to a uniform variable in the shader
    /// @param name Name of uniform variable in the shader
    /// @param matrix Matrix to link to the uniform variable
    void setMat4(const std::string& name, const glm::mat4& matrix);

    void setVec3(const std::string& name, const glm::vec3& vector);

    /// @brief Binds the VAO to the shader
    void bind();

    /// @brief Unbinds the VAO from the shader
    void unbind();
};

#endif // SHADER_H