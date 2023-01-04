#ifndef APP_H
#define GLFW_INCLUDE_NONE

//THIS WILL HOLD ALL OF THE FILES THAT ARE ESSENTIAL TO THE ENGINE
#define GLFW_INCLUDE_NONE

//opengl libraries
#include <opengl/opengl.h>
#include <stb/stb_image.h>

//glm math libraries
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>


//vector 
#include <vector>

#include <iostream>

#include "Game.h"
#include "ResourceManager.h"
#include "gl/Shader.h"

class App
{
    static float windowWidth;
    static float windowHeight;

    static GLFWwindow* window;

    static ResourceManager* resourceManager;
    static Shader* shader;

    /// @brief initializes glfw
    void initGLFW();

    /// @brief updates glfw application and events
    void update();

public:

    static Game* game;

    /// @brief Creates a new application with the specified width and height
    /// @param width width in pixels of the window that is generated
    /// @param height height in pixels of the window that is generated
    App(Game* game);
    ~App();

    /// @brief Changes the size of the window created by the application
    /// @param width new width in pixels of the window
    /// @param height new height in pixels of the window
    static void changeWindowSize(int width, int height);
};

#endif // APP_H