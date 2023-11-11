
#ifndef CAMERA_H
#define CAMERA_H

#include "../gl/Shader.h"
#include "../events/WindowListener.h"
#include "../events/KeyListener.h"
#include "../events/MouseListener.h"

#include <opengl/opengl.h>

//glm math libraries
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>


class Camera{

public:
    Camera();

    void update(Shader* shader, float dt);

    glm::mat4* view() { return &m_view; }

    glm::mat4* projection() { return &m_proj; }

    float getFOV(){ return fov; }
    void setFOV(float newFOV){ fov = newFOV; }
    void processInput(float dt);

    void faceMouse();
private:
    glm::mat4 m_view;
    glm::mat4 m_proj;

    glm::vec3 up;

    glm::vec3 cameraPos;

    glm::vec3 cameraFront;
    glm::vec3 cameraUp;  
    glm::vec3 cameraRight;

    glm::vec3 cameraTarget;

    float fov;

    float yaw, pitch;

    bool firstMovementFrame;
};

#endif