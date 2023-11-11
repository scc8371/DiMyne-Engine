#ifndef CUBE_H
#define CUBE_H

#include "../../gl/Shader.h"
#include "Mesh.h"
#include "../../utils/ColorDef.h"

class Cube{
public:
    Cube(float size, const char* texturePath);
    Cube();
    void draw(Shader* shader);

private:
    Mesh mesh;
};
#endif