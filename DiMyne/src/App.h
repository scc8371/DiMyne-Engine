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

#include "camera/Camera.h"

#include "rendering/3d/Cube.h"

#include <glad/glad.h>

#ifdef DEBUG
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#endif

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
    static Shader* depthShader;
    static Shader* fontShader;

    Camera* camera;
    Cube* testCube;

    static SpriteBatch* spriteBatch; 

    /// @brief initializes glfw
    void initGLFW();

    void initSb();

    #ifdef DEBUG
    void initImGui();
    void updateImGui();
    #endif

    /// @brief updates glfw application and events
    void update();
};

#endif // APP_H