#ifndef CUBE_H
#define CUBE_H

#include "../../gl/Shader.h"
#include "Mesh.h"
#include "../../utils/ColorDef.h"

class Cube{
public:
    Cube(float size, const char* texturePath, Color tint = WHITE);
    Cube();
    void draw(Shader* shader);

    void translate(glm::vec3 translate);
    void scale(glm::vec3 scale);
    void rotate(float rotation, glm::vec3 axis);


private:
    Mesh mesh;
};
#endif