
#ifndef MODEL_H
#define MODEL_H

#include "../../gl/Shader.h"
#include "Mesh.h"
#include "../../utils/ColorDef.h"
#include "../../MyneGlobals.h"
#include "OBJ_Loader.h"

class Model
{
public:
    Model(const char *path, Color tint = WHITE);
    void draw();

    void rotate(float angleRotation, glm::vec3 axis);
    void translate(glm::vec3 translation);
    void scale(glm::vec3 scale);
    
private:
    // model data
    std::vector<Mesh> meshes;
    std::string dir;

    std::vector<Texture> textures_loaded;

    Color tint; 

    void loadModel(std::string path);
};

#endif