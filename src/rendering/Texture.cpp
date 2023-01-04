#include "Texture.h"

Texture::Texture(const char* imagePath, GLenum textureType, GLenum textureSlot, GLenum format, GLenum pixelType){
    this->textureType = textureType;
    
    int width, height, channels; 

    unsigned char* data = stbi_load(imagePath, &width, &height, &channels, 0);

    //generates texture data
    glGenTextures(1, &ID);

    glActiveTexture(textureSlot);
    glBindTexture(textureType, ID);

    //img resizing
    glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    //configures repeating textures
    glTexParameteri(textureType, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(textureType, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //assign texture to gl texture obj
    glTexImage2D(textureType, 0, format, width, height, 0, format, pixelType, data);
    glGenerateMipmap(textureType);

    //free image data
    stbi_image_free(data);

    //unbind gl texture
    glBindTexture(textureType, 0);
}

Texture::Texture(const char* image) 
    : Texture(image, GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE) {}

Texture::Texture(int width, int height){
    textureType = GL_TEXTURE_2D;

    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &ID);
    glBindTexture(textureType, ID);

    //img resizing
    glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    //repeating textures
    glTexParameteri(textureType, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(textureType, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    //assign texture to gl texture obj
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, 0);

    //generate mipmaps
    glGenerateMipmap(textureType);

    //unbind gl texture
    glBindTexture(textureType, 0);
}

GLuint Texture::id(){
    return ID;
}

void Texture::bind(){
    glBindTexture(textureType, ID);
}

void Texture::unbind(){
    glBindTexture(textureType, 0);
}

void Texture::del(){
    glDeleteTextures(1, &ID);
}


