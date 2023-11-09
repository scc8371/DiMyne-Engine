
#include "Camera.h"

Camera::Camera(){
    std::cout << "Initializing camera..." << std::endl;
    this->cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    this->cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    this->cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    this->fov = 60.0f;

    std::cout << "Camera initialized." << std::endl;
};

void Camera::update(Shader* shader, float dt){
    m_proj = glm::perspective(glm::radians(fov), (float)WindowListener::getWidth() / (float)WindowListener::getHeight(), 0.1f, 100.0f);
    m_view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    try{
        shader->use();

        //send projection data to shader...
        GLuint projID = glGetUniformLocation(shader->ID, "projection");
        glUniformMatrix4fv(projID, 1, GL_FALSE, value_ptr(m_proj));

        //send view data to shader...
        GLuint viewID = glGetUniformLocation(shader->ID, "view");
        glUniformMatrix4fv(viewID, 1, GL_FALSE, value_ptr(m_view));
    }
    catch(std::exception& e){
        std::cout << "Problem with shader in Camera!" << std::endl;
    }
};