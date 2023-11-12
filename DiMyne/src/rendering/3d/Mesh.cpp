#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex3D> vertices, std::vector<unsigned int> indices, Texture texture) : texture(texture)
{
    this->vertices = vertices;
    this->indices = indices;
    this->model = glm::mat4(1.0f);

    meshInit();
};

Vertex3D::Vertex3D(GLfloat x, GLfloat y, GLfloat z, GLfloat u, GLfloat v, Color color)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->u = u;
    this->v = v;

    

    this->a = color.a / 255.0f;
    this->r = color.r / 255.0f;
    this->g = color.g / 255.0f;
    this->b = color.b / 255.0f;
}

void Mesh::scale(glm::vec3 scale)
{
    this->model = glm::scale(this->model, scale);
}

void Mesh::translate(glm::vec3 translate)
{
    this->model = glm::translate(this->model, translate);
}

void Mesh::rotate(float rotationAngle, glm::vec3 axis)
{
    this->model = glm::rotate(this->model, glm::radians(rotationAngle), axis);
}

void Mesh::meshInit()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex3D), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // vert position data
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void *)0);

    // vert uv data
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
                          sizeof(Vertex3D), (void *)(2 * sizeof(GLfloat)));

    // vert tint data
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex3D),
                          (void *)(5 * sizeof(GLfloat)));

    // //vertex normals
    // glEnableVertexAttribArray(1);
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

    // vertex texture coords
    // glEnableVertexAttribArray(2);
    // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::texCoords));

    glBindVertexArray(0);
};

Mesh::Mesh() : texture(NULL){};

void Mesh::draw(Shader *shader)
{
    shader->use();
    shader->setMat4("model", model);

    glActiveTexture(GL_TEXTURE0);
    texture.bind();

    // bind vao
    glBindVertexArray(VAO);

    // draw mesh
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    // unbind vao
    glBindVertexArray(0);

    // unbind texture
    texture.unbind();
}