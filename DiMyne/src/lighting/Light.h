#ifndef LIGHT_H
#define LIGHT_H

#include <glm/vec3.hpp>
#include "../utils/Color.h"
#include "../utils/ColorDef.h"
#include "../MyneGlobals.h"

class Light{
public:
    Light(glm::vec3 location, Color color = WHITE);
    
    glm::vec3 getLightLocation(){ return location; }
    Color getColor() { return color; }
    void update();
private:
    glm::vec3 location;
    Color color;
};
#endif