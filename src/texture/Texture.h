#ifndef TEXTURE_H
#define TEXTURE_H

#include <opengl/opengl.h>
#include <stb/stb_image.h>

#include "../gl/Shader.h"

class Texture{
public:

    /// @brief Creates a texture object
    /// @param imagePath Relative path to the texture image
    /// @param textureType Texture type (GL_TEXTURE_2D, GL_TEXTURE_3D, GL_TEXTURE_CUBE_MAP)
    /// @param textureSlot Texture slot (GL_TEXTURE0, GL_TEXTURE1, etc.)
    /// @param format Format of the texture (GL_RGB, GL_RGBA, etc.)
    /// @param pixelType Type of the pixel data (GL_UNSIGNED_BYTE, GL_FLOAT, etc.)
    Texture(const char* imagePath, GLenum textureType, GLenum textureSlot, GLenum format, GLenum pixelType);

    /// @brief Creates a texture object
    /// @param imagePath Relative path to the texture image
    Texture(const char* imagePath);

    Texture(int width, int height);

    /// @brief 
    void assignTextureUnit(Shader* shader, const char* uniform, GLuint unit);

    void bind();
    void unbind();
    void setUniform(Shader* shader, const char* name);

    /// @brief Deletes the texture
    void del();

    /// @brief Bounds of the texture
    /// @return Bounds of the texture (GLfloat array of size 4)
    GLfloat* bounds();

    /// @brief Size of the texture
    int getSize();

private:
    GLuint ID;
    GLenum textureType;
};

#endif // TEXTURE_H