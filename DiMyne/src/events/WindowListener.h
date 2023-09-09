#ifndef WINDOWLISTENER_H
#define WINDOWLISTENER_H

#include <opengl/opengl.h>
#include "../gl/Shader.h"

//glm math libraries
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>

class WindowListener{
public:
    static WindowListener* getInstance();

    static void windowSizeCallback(GLFWwindow* window, int width, int height);
    static void windowPosCallback(GLFWwindow* window, int xPos, int yPos);
    static void windowIconifyCallback(GLFWwindow* window, int iconified);
    static void windowFocusCallback(GLFWwindow* window, int focused);
    static void windowCloseCallback(GLFWwindow* window);
    static void resizeBuffer(int width, int height);
    static void resizeBuffer(Shader* shader);
   

    static int getWidth();
    static int getHeight();
    static bool isIconified();
    static bool isFocused();
    static bool isClosing();
    static void setShader(Shader* shader);
    static void setFontShader(Shader* shader);

private:
    WindowListener();
    static WindowListener* instance;
    static Shader* shader;
    static Shader* fontShader;

    static int width, height;
    static bool iconified, focused, closing;
};



#endif // WINDOWLISTENER_H