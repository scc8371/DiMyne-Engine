#ifndef TEXTURE_H
#define TEXTURE_H

#include <opengl/opengl.h>
#include <stb/stb_image.h>

#include "../gl/Shader.h"

class Texture
{
public:
    enum TexType
    {
        DIFFUSE,
        SPECULAR,
        NORMAL,
        HEIGHT
    };
    
    /// @brief Creates a texture object
    /// @param imagePath Relative path to the texture image
    /// @param textureType Texture type (GL_TEXTURE_2D, GL_TEXTURE_3D, GL_TEXTURE_CUBE_MAP)
    /// @param textureSlot Texture slot (GL_TEXTURE0, GL_TEXTURE1, etc.)
    /// @param format Format of the texture (GL_RGB, GL_RGBA, etc.)
    /// @param pixelType Type of the pixel data (GL_UNSIGNED_BYTE, GL_FLOAT, etc.)
    Texture(const char *imagePath, GLenum textureType, GLenum textureSlot, GLenum format, GLenum pixelType, TexType type = TexType::DIFFUSE);

    /// @brief Creates a texture object
    /// @param imagePath Relative path to the texture image
    Texture(const char *imagePath);

    Texture(int width, int height);

    /// @brief
    void assignTextureUnit(Shader *shader, const char *uniform, GLuint unit);

    /// @brief Binds the texture
    void bind();

    /// @brief Unbinds the texture
    void unbind();

    /// @brief Deletes the texture
    void del();

    /// @brief get ID of the texture
    /// @return ID of the texture
    GLuint id();

    TexType texType = TexType::DIFFUSE;
    std::string path() { return texPath; };

private:
    GLuint ID;
    GLenum _glTexType;
    std::string texPath;
};

#endif // TEXTURE_H