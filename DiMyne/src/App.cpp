#include "App.h"

using namespace std;

//initial window dimensions, can be changed.
float App::windowWidth = 1200;
float App::windowHeight = 800;

Vector2 App::mousePosition = Vector2(0, 0);

Shader* App::shader = nullptr;
Shader* App::fontShader = nullptr;
Shader* App::depthShader = nullptr;

SoundPlayer App::audio = SoundPlayer();

Game* App::game = NULL;
GLFWwindow* App::window = NULL;

SpriteBatch* App::spriteBatch = NULL;

App::App(Game* game){
    //define default window size
    this->game = game;
    dt = 0;
    prevDt = 0;
      
    initGLFW();
    audio.initialize();
    game->initialize();

    #ifdef DEBUG
    initImGui();
    #endif
    
    initSb();
    Sprite2D::setSpriteBatch(spriteBatch);
    Font::setSpriteBatch(spriteBatch);

    camera = new Camera();
    
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
    fontShader = new Shader("resources/shader/default.vert", "resources/shader/fontShader.frag");
    depthShader = new Shader("resources/shader/depth.vert", "resources/shader/default.frag");
    
    //alpha blendings
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //set window listener shader, first buffer change
    WindowListener::setShader(shader);
    WindowListener::setFontShader(fontShader);

    WindowListener::resizeBuffer(windowWidth, windowHeight);
    WindowListener::resizeBuffer(fontShader);

    glfwSwapInterval(1);

    glfwSetCursorPosCallback(window, MouseListener::getInstance()->mousePosCallback);
    glfwSetMouseButtonCallback(window, MouseListener::getInstance()->mouseButtonCallback);
    glfwSetScrollCallback(window, MouseListener::getInstance()->mouseScrollCallback);
    glfwSetKeyCallback(window, KeyListener::getInstance()->keyCallback);
    glfwSetWindowSizeCallback(window, WindowListener::getInstance()->windowSizeCallback);
    glfwSetWindowCloseCallback(window, WindowListener::getInstance()->windowCloseCallback);

    std::cout << "Successfully initialized GLFW" << std::endl;
}

void App::initSb(){
    std::cout << "Initializing SpriteBatch..." << std::endl;
    spriteBatch = new SpriteBatch();

    //add img and font shaders
    spriteBatch->addDefualtShader(shader);
    spriteBatch->addFontShader(fontShader);
    
    std::cout << "Successfully initialized SpriteBatch" << std::endl;
}

void App::update(){
    

    //update glfw
    glfwPollEvents();

    while(!glfwWindowShouldClose(window)){

        //update dt
        dt = glfwGetTime() - prevDt;
        prevDt = glfwGetTime();
        
        #ifdef DEBUG
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //set imgui size
        ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);
        #endif
        
        //update camera view.
        camera->update(depthShader, dt);

        //update game   
        game->update(dt);
        audio.updateAudio();

        shader->use();  
        game->draw(spriteBatch);

        //update mouse position
        App::mousePosition = MouseListener::getInstance()->getPos();

        spriteBatch->render();

        if(KeyListener::isKeyPressed(GLFW_KEY_ESCAPE)){
            std::cout << "Closing window..." << std::endl;
            glfwSetWindowShouldClose(window, true);
        }

        MouseListener::endFrame();

        #ifdef DEBUG
        updateImGui();
        #endif

        //swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();       
    }
}

App::~App(){
    glfwDestroyWindow(window);
    glfwTerminate();

    shader->del();
    fontShader->del();

    delete spriteBatch;
    spriteBatch = nullptr;

    delete camera;
    camera = nullptr;

    #ifdef DEBUG
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    #endif
}

#ifdef DEBUG
void App::initImGui(){
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void App::updateImGui(){
    ImGui::Begin("Debug");
    ImGui::Text("FPS: %i", (int)(1/dt));
    ImGui::Text("Mouse Position: (%f, %f)", mousePosition.x, mousePosition.y);
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
#endif

