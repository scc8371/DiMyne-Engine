#include "MouseListener.h"

MouseListener* MouseListener::instance = nullptr;

MouseListener* MouseListener::getInstance(){
    if(instance == nullptr){
        instance = new MouseListener();
    }
    return instance;
}

MouseListener::MouseListener(){
    xPos = 0;
    yPos = 0;
    xLast = 0;
    yLast = 0;
    scrollX = 0;
    scrollY = 0;
    dragging = false;
}

void MouseListener::mousePosCallback(GLFWwindow* window, double xPos, double yPos){
    //sets last position for mouse
    MouseListener::getInstance()->xLast = MouseListener::getInstance()->xPos;
    MouseListener::getInstance()->yLast = MouseListener::getInstance()->yPos;

    //sets current position for mouse
    MouseListener::getInstance()->xPos = xPos;
    MouseListener::getInstance()->yPos = yPos;

    //check if dragging
    if(MouseListener::getInstance()->buttons[0]){
        MouseListener::getInstance()->dragging = true;
    }
    else{
        MouseListener::getInstance()->dragging = false;
    }
}

void MouseListener::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods){
    if(action == GLFW_PRESS){
        if(button < 3){
            MouseListener::getInstance()->buttons[button] = true;
        }
    }
    else if(action == GLFW_RELEASE){
        if(button < 3){
            MouseListener::getInstance()->buttons[button] = false;
        }
    }
}

void MouseListener::mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset){
    MouseListener::getInstance()->scrollX = xoffset;
    MouseListener::getInstance()->scrollY = yoffset;
}

void MouseListener::endFrame(){
    MouseListener::getInstance()->scrollX = 0;
    MouseListener::getInstance()->scrollY = 0;

    MouseListener::getInstance()->xLast = MouseListener::getInstance()->xPos;
    MouseListener::getInstance()->yLast = MouseListener::getInstance()->yPos;
}
