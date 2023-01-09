#include "KeyListener.h"

KeyListener* KeyListener::instance = nullptr;

KeyListener* KeyListener::getInstance(){
    if(instance == nullptr){
        instance = new KeyListener();
    }
    return instance;
}

KeyListener::KeyListener(){
    for(int i = 0; i < 350; i++){
        keys[i] = false;
    }
}

void KeyListener::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if(action == GLFW_PRESS){
        KeyListener::getInstance()->keys[key] = true;
    }
    else if(action == GLFW_RELEASE){
        KeyListener::getInstance()->keys[key] = false;
    }
}

bool KeyListener::isKeyPressed(int key){
    //check if key is in range
    if(key < 0 || key > 350){
        std::cout << "Key out of range" << std::endl;
        return false;
    }

    return KeyListener::getInstance()->keys[key];
}