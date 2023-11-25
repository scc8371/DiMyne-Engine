#include "Texture.h"

Texture::Texture(const char* imagePath, GLenum glTexType, GLenum textureSlot, GLenum format, GLenum pixelType, TexType type){
    this->_glTexType = glTexType;
    this->texType = type;
    
    int width, height, channels; 

    unsigned char* data = stbi_load(imagePath, &width, &height, &channels, 0);
    texPath = imagePath;

    //generates texture data
    glGenTextures(1, &ID);

    glActiveTexture(textureSlot);
    glBindTexture(_glTexType, ID);

    //img resizing
    glTexParameteri(_glTexType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(_glTexType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    //configures repeating textures
    glTexParameteri(_glTexType, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(_glTexType, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //assign texture to gl texture obj
    glTexImage2D(_glTexType, 0, format, width, height, 0, format, pixelType, data);
    glGenerateMipmap(_glTexType);

    //free image data
    stbi_image_free(data);

    //unbind gl texture
    glBindTexture(_glTexType, 0);
}

Texture::Texture(const char* image) 
    : Texture(image, GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE) {}

Texture::Texture(int width, int height){
    _glTexType = GL_TEXTURE_2D;
	
	glActiveTexture(GL_TEXTURE0);	
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);

	//Configures image resizing
	glTexParameteri(_glTexType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(_glTexType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//configures repeating textures
	glTexParameteri(_glTexType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(_glTexType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, 0);

	glGenerateMipmap(_glTexType);

	//Unbinds openGL texture so we cannot accidentally modify it.
	glBindTexture(_glTexType, 0);
}

GLuint Texture::id(){
    return ID;
}

void Texture::bind(){
    glBindTexture(_glTexType, ID);
}

void Texture::unbind(){
    glBindTexture(_glTexType, 0);
}

void Texture::del(){
    glDeleteTextures(1, &ID);
}


