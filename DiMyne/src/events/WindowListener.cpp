#include "WindowListener.h"

using namespace glm;

WindowListener* WindowListener::instance = nullptr;
int WindowListener::width = 0;
int WindowListener::height = 0;
bool WindowListener::iconified = false;
bool WindowListener::focused = false;
bool WindowListener::closing = false;

Shader* WindowListener::shader = nullptr;
Shader* WindowListener::fontShader = nullptr;

WindowListener* WindowListener::getInstance(){
    if(instance == nullptr){
        instance = new WindowListener();
    }
    return instance;
}

WindowListener::WindowListener(){
    width = 0;
    height = 0;
    iconified = false;
    focused = false;
    closing = false;
}

void WindowListener::windowSizeCallback(GLFWwindow* window, int width, int height){
    WindowListener::getInstance()->width = width;
    WindowListener::getInstance()->height = height;

    resizeBuffer(width, height);
}

void WindowListener::windowIconifyCallback(GLFWwindow* window, int iconified){
    if(iconified == GLFW_TRUE){
        WindowListener::getInstance()->iconified = true;
    }
    else{
        WindowListener::getInstance()->iconified = false;
    }
}

void WindowListener::windowFocusCallback(GLFWwindow* window, int focused){
    if(focused == GLFW_TRUE){
        WindowListener::getInstance()->focused = true;
    }
    else{
        WindowListener::getInstance()->focused = false;
    }
}


void WindowListener::setShader(Shader* shader){
    WindowListener::shader = shader;
}

void WindowListener::setFontShader(Shader* shader){
    WindowListener::fontShader = shader;
}

void WindowListener::resizeBuffer(int width, int height){

    if(shader == nullptr){
        std::cout << "Error: shader is not defined in WindowListener. " <<
         "Use WindowListener::setShader(Shader* shader) to set its shader." << std::endl;
         return;
    }

    glViewport(0, 0, width, height);
    mat4x4 projection = ortho(0.0f, (float)width, (float)height, 0.0f, -1.0f, 1.0f);

    try{
        shader->use();
        GLuint projID = glGetUniformLocation(shader->ID, "projection");
        glUniformMatrix4fv(projID, 1, GL_FALSE, value_ptr(projection));
    }
    catch(std::exception& e){
        std::cout << "Shader not defined" << std::endl;
    }

    try{
        fontShader->use();
        GLuint projID = glGetUniformLocation(fontShader->ID, "projection");
        glUniformMatrix4fv(projID, 1, GL_FALSE, value_ptr(projection));
    }   
    catch(std::exception& e){
        std::cout << "Font shader not defined" << std::endl;
    }
    
    WindowListener::getInstance()->width = width;
    WindowListener::getInstance()->height = height;
}

void WindowListener::resizeBuffer(Shader* shader){
    glViewport(0, 0, width, height);
    mat4x4 projection = ortho(0.0f, (float)width, (float)height, 0.0f, -1.0f, 1.0f);

    shader->use();
    GLuint projID = glGetUniformLocation(shader->ID, "projection");
    glUniformMatrix4fv(projID, 1, GL_FALSE, value_ptr(projection));
}

void WindowListener::windowCloseCallback(GLFWwindow* window){
    WindowListener::getInstance()->closing = true;
}

int WindowListener::getWidth(){
    return WindowListener::getInstance()->width;
}

int WindowListener::getHeight(){
    return WindowListener::getInstance()->height;
}

bool WindowListener::isIconified(){
    return WindowListener::getInstance()->iconified;
}

bool WindowListener::isFocused(){
    return WindowListener::getInstance()->focused;
}

bool WindowListener::isClosing(){
    return WindowListener::getInstance()->closing;
}



