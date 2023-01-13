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
#include "gl/Shader.h"
#include "rendering/SpriteBatch.h"
#include "rendering/Sprite2D.h"

#include "events/KeyListener.h"
#include "events/MouseListener.h"
#include "events/WindowListener.h"
#include "rendering/Font.h"

#include "audio/Song.h"
#include "audio/Sound.h"
#include "audio/SoundPlayer.h"

#include "utils/ColorDef.h"

class App
{
public:
    static Game* game;

    static Vector2 mousePosition;
    static SoundPlayer audio;

    /// @brief Creates a new application with the specified width and height
    /// @param width width in pixels of the window that is generated
    /// @param height height in pixels of the window that is generated
    App(Game* game);
    ~App();

    /// @brief Changes the size of the window created by the application
    /// @param width new width in pixels of the window
    /// @param height new height in pixels of the window
    static void changeWindowSize(int width, int height);

private:
    static float windowWidth;
    static float windowHeight;

    float prevDt;
    float dt;

    static GLFWwindow* window;
    static Shader* shader;
    static Shader* fontShader;

    static SpriteBatch* spriteBatch; 

    /// @brief initializes glfw
    void initGLFW();

    void initSb();

    /// @brief updates glfw application and events
    void update();
};

#endif // APP_H