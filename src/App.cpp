#include "App.h"

using namespace std;
using namespace glm;

//window dimentions, can be changed.
float App::windowWidth = 1200;
float App::windowHeight = 800;

Shader* App::shader = nullptr;

Game* App::game = NULL;
GLFWwindow* App::window = NULL;

App::App(Game* game){
    //define default window size
    this->game = game;
    
    initGLFW();
    update();
}

void App::initGLFW(){
    std::cout << "Initializing GLFW" << std::endl;

    //initialize glfw
    if (!glfwInit()){
        cout << "GLFW failed to initialize!" << endl;
        return;
    }

    //define gl version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //create window
    window = glfwCreateWindow(windowWidth, windowHeight, "DiMyne Test Window", NULL, NULL);

    if(window == NULL){
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);

    gladLoadGL();

    shader = new Shader("resources/shader/default.vert", "resources/shader/default.frag");
    
    //alpha blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    std::cout << "Successfully initialized GLFW" << std::endl;
}

void App::update(){
    //update glfw
    glfwPollEvents();

    while(!glfwWindowShouldClose(window)){
        
        //update game     
        //game->update(glfwGetTime());
        //game->draw();


        //swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

App::~App(){
    glfwDestroyWindow(window);
    glfwTerminate();
    shader->del();
}