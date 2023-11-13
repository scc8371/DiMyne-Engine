#include "Light.h"

Light::Light(glm::vec3 location, Color color){
    this->location = location;
    this->color = color;
}

void Light::update(){
    MyneGlobals::depthShader->use();
    MyneGlobals::depthShader->setVec3("lightColor", glm::vec3(this->color.r, this->color.g, this->color.b));
    MyneGlobals::depthShader->setVec3("lightPos", this->location);
}
