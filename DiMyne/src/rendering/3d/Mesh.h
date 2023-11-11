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
    GLfloat x, y, z, u, v;
    GLfloat r, g, b, a;
};

class Mesh{
public:
    Mesh(std::vector<Vertex3D> vertices, std::vector<unsigned int> indices, Texture texture);
    Mesh();

    void draw(Shader* shader);

    std::vector<Vertex3D> vertices;
    std::vector<unsigned int> indices;
    
    unsigned int VAO;

    void scale(glm::vec3 scale);
    void translate(glm::vec3 translation);
    void rotate(float angleRotation, glm::vec3 axis);

private:
    unsigned int VBO, EBO;
    glm::mat4 model;
    void meshInit();

    Texture texture;
};

#endif