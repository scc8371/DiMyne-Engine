#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex3D> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, bool doNormalCalculate)
{
    this->vertices = vertices;
    this->indices = indices;
    this->model = glm::mat4(1.0f);

    this->textures = textures;
    this->normals = std::vector<glm::vec3>(this->vertices.size());

    if (doNormalCalculate)
    {
        calculateNormals();
    }

    meshInit();
};

void Mesh::calculateNormals()
{
    for (unsigned int i = 0; i < this->indices.size(); i += 3)
    {
        Vertex3D A = this->vertices[this->indices[i]];
        Vertex3D B = this->vertices[this->indices[i + 1LL]];
        Vertex3D C = this->vertices[this->indices[i + 2LL]];

        glm::vec3 normal = computeFaceNormal(glm::vec3(A.x, A.y, A.z), glm::vec3(B.x, B.y, B.z), glm::vec3(C.x, C.y, C.z));
        this->normals[this->indices[i]] += normal;
        this->normals[this->indices[i + 1LL]] += normal;
        this->normals[this->indices[i + 2LL]] += normal;
    }

    // normalize each normal
    for (unsigned int i = 0; i < this->normals.size(); i++)
    {
        this->normals[i] = glm::normalize(this->normals[i]);
        this->vertices[i].normalX = this->normals[i].x;
        this->vertices[i].normalY = this->normals[i].y;
        this->vertices[i].normalZ = this->normals[i].z;
    }
}

glm::vec3 Mesh::computeFaceNormal(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
{
    auto a = p3 - p2;
    auto b = p1 - p2;

    return glm::normalize(glm::cross(a, b));
}

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

    this->normalX = 0;
    this->normalY = 0;
    this->normalZ = 0;
}

Vertex3D::Vertex3D(){};

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
                          sizeof(Vertex3D), (void *)(3 * sizeof(GLfloat)));

    // vert tint data
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex3D),
                          (void *)(5 * sizeof(GLfloat)));

    // vertex normals
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void *)(9 * sizeof(GLfloat)));
};

Mesh::Mesh(){};

void Mesh::draw(Shader *shader)
{
    shader->use();
    shader->setMat4("model", model);

    unsigned int diffuseNum = 1;
    unsigned int specularNum = 1;
    unsigned int normalNum = 1;
    unsigned int heightNum = 1;

    for (int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);

        std::string num;
        std::string name;
        Texture::TexType type = textures[i].texType;

        switch (type)
        {
        case Texture::TexType::DIFFUSE:
            name = "texture_diffuse";
            num = std::to_string(diffuseNum++);
            break;
        case Texture::TexType::SPECULAR:
            name = "texture_specular";
            num = std::to_string(specularNum++);
            break;
        case Texture::TexType::NORMAL:
            name = "texture_normal";
            num = std::to_string(normalNum++);
            break;
        case Texture::TexType::HEIGHT:
            name = "texture_height";
            num = std::to_string(heightNum++);
            break;
        }

        glUniform1i(glGetUniformLocation(shader->ID, (name + num).c_str()), i);
        textures[i].bind();
    }
    // bind vao + draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
    // unbind vao
    glBindVertexArray(0);

    // unbind textures
    glActiveTexture(GL_TEXTURE0);
}