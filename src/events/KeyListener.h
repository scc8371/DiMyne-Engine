#ifndef KEYLISTENER_H
#define KEYLISTENER_H

#include <opengl/opengl.h>
#include <iostream>

class KeyListener
{
public:

    /// @brief Returns a singleton instance of the KeyListener class
    /// @return KeyListener* instance
    static KeyListener* getInstance();

    /// @brief Checks if a key is pressed
    /// @param key - GLFW key code
    /// @return bool - true if key is pressed, false if not
    static bool isKeyPressed(int key);


    /// @brief Callback function for GLFW key input
    /// @param window GLFW window
    /// @param key key code
    /// @param scancode scancode (platform specific) 
    /// @param action GLFW_PRESS, GLFW_RELEASE, GLFW_REPEAT
    /// @param mode GLFW_MOD_SHIFT, GLFW_MOD_CONTROL, GLFW_MOD_ALT, GLFW_MOD_SUPER 
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
private:
    static KeyListener* instance;
    KeyListener();
    bool keys[350];
};


#endif // KEYLISTENER_H