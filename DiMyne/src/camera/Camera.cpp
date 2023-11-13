
#include "Camera.h"

Camera::Camera()
{
    std::cout << "[DiMyne] Initializing camera..." << std::endl;
    this->cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    this->cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    this->cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    this->fov = 90.0f;
    this->yaw = -90.0f;
    this->pitch = 0.0f;
    this->firstMovementFrame = false;

    std::cout << "[DiMyne] Camera initialized." << std::endl;
};

void Camera::update(Shader *shader, float dt)
{
    m_proj = glm::perspective(glm::radians(fov), (float)WindowListener::getWidth() / (float)WindowListener::getHeight(), 0.1f, 100.0f);
    m_view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    try
    {
        shader->use();

        // send projection data to shader...
        GLuint projID = glGetUniformLocation(shader->ID, "projection");
    
        glUniformMatrix4fv(projID, 1, GL_FALSE, glm::value_ptr(m_proj));

        // send view data to shader...
        GLuint viewID = glGetUniformLocation(shader->ID, "view");
        glUniformMatrix4fv(viewID, 1, GL_FALSE, glm::value_ptr(m_view));

        shader->setVec3("viewPos", cameraPos);
    }
    catch (std::exception &e)
    {
        std::cout << "[DiMyne] Problem with shader in Camera!" << std::endl;
    }

    faceMouse();
    processInput(dt);
};

void Camera::processInput(float dt)
{
    float cameraSpeed = .5f;
    if(KeyListener::isKeyPressed(GLFW_KEY_LEFT_SHIFT)) cameraSpeed *= 2;
    if (KeyListener::isKeyPressed(GLFW_KEY_W))
        cameraPos += cameraSpeed * cameraFront * dt;
    if (KeyListener::isKeyPressed(GLFW_KEY_S))
        cameraPos -= cameraSpeed * cameraFront * dt;
    if (KeyListener::isKeyPressed(GLFW_KEY_A))
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * dt;
    if (KeyListener::isKeyPressed(GLFW_KEY_D))
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * dt;
}

void Camera::faceMouse(){
    Vector2 currentPos = MouseListener::getInstance()->getPos();
    Vector2 lastPos = MouseListener::getInstance()->getLastPos();
    float sensitivity = MouseListener::getInstance()->getMouseSensitivity();

    if(!firstMovementFrame){
        if(currentPos - lastPos != Vector2(0, 0)) firstMovementFrame = true;
        return;
    }

    Vector2 offset = Vector2(currentPos.x - lastPos.x, lastPos.y - currentPos.y);
    offset *= sensitivity;

    yaw += offset.x;
    pitch += offset.y;

    if(pitch > 89.0f){
        pitch = 89.0f;
    }
    if(pitch < -89.0f){
        pitch = -89.0f;
    }

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}