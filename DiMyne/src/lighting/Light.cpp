#include "Light.h"

Light::Light(glm::vec3 location, Color color){
    this->location = location;
    this->color = color;
}

void Light::update(){
    MyneGlobals::depthShader->use();
    MyneGlobals::depthShader->setVec3("lightColor", glm::vec3(this->color.r / 255, this->color.g / 255, this->color.b / 255));
    MyneGlobals::depthShader->setVec3("lightPos", this->location);
}
