#ifndef MESH_H 
#define MESH_H

#include <opengl/opengl.h>

//glm math libraries
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <algorithm>

#include "../Texture.h"
#include "../../utils/Color.h"

//https://learnopengl.com/Model-Loading/Mesh

struct Vertex3D{
    /// @brief Creates a new Vertex, simplifies setting gl vertex attributes
    /// @param x x coordinate
    /// @param y y coordinate
    /// @param u u vertex attribute
    /// @param v v vertex attribute
    /// @param color color of the vertex
    Vertex3D(GLfloat x, GLfloat y, GLfloat z, GLfloat u, GLfloat v, Color color);
    Vertex3D();
    GLfloat x, y, z, u, v;
    GLfloat r, g, b, a;
    GLfloat normalX, normalY, normalZ;

    
};

class Mesh{
public:
    Mesh(std::vector<Vertex3D> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, bool doNormalCalculate = false);
    Mesh();

    void draw(Shader* shader);

    std::vector<Vertex3D> vertices;
    std::vector<unsigned int> indices;
    std::vector<glm::vec3> normals;
    
    unsigned int VAO;

    void scale(glm::vec3 scale);
    void translate(glm::vec3 translation);
    void rotate(float angleRotation, glm::vec3 axis);
    

private:
    unsigned int VBO, EBO;
    glm::mat4 model;
    void meshInit();
    void calculateNormals();
    glm::vec3 computeFaceNormal(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);

    std::vector<Texture> textures;
};

#endif