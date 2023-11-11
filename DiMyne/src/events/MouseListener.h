#ifndef MOUSELISTENER_H
#define MOUSELISTENER_H

#include <opengl/opengl.h>
#include "../utils/Vector2.h"

class MouseListener{
public:
    static MouseListener* getInstance();

    Vector2 getPos() { return Vector2(xPos, yPos); }
    Vector2 getLastPos() { return Vector2(xLast, yLast); }
    Vector2 getScroll() { return Vector2(scrollX, scrollY); }
    float getMouseSensitivity() {return mouseSensitivity; }
    void setMouseSensitivity(float val) {mouseSensitivity = val; }
    bool isLeftDown() { return buttons[0]; }
    bool isRightDown() { return buttons[1]; }
    bool isMiddleDown() { return buttons[2]; }
    bool isDragging() { return dragging; }

    static void mousePosCallback(GLFWwindow* window, double xPos, double yPos);
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    static void endFrame();



private: 

    MouseListener();
    static MouseListener* instance;

    float xPos, yPos, xLast, yLast, scrollX, scrollY;
    bool buttons[3] = { false, false, false };
    bool dragging;
    float mouseSensitivity = .1f;
};




#endif // MOUSELISTENER_H