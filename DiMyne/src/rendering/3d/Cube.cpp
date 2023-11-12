#include "Cube.h"
Cube::Cube(){};
Cube::Cube(float size, const char* texturePath, Color tint){
    //create texture
    Texture texture = Texture(texturePath);

    //Create mesh vertices
    std::vector<Vertex3D> vertices = std::vector<Vertex3D>{
        Vertex3D(-.5, -.5, -.5, 0.0, 0.0, tint),
        Vertex3D(.5, -.5, -.5, 1.0, 0.0, tint),
        Vertex3D(.5, .5, -.5, 1.0, 1.0, tint),
        Vertex3D(-.5, .5, -.5, 0.0, 1.0, tint),
        Vertex3D(-.5, -.5, .5, 0.0, 0.0, tint),
        Vertex3D(.5, -.5, .5, 1.0, 0.0, tint),
        Vertex3D(.5, .5, .5, 1.0, 1.0, tint),
        Vertex3D(-.5, .5, .5, 0.0, 1.0, tint),

        Vertex3D(-.5, .5, -.5, 0.0, 0.0, tint),
        Vertex3D(-.5, -.5, -.5, 1.0, 0.0, tint),
        Vertex3D(-.5, -.5, .5, 1.0, 1.0, tint),
        Vertex3D(-.5, .5, .5, 0.0, 1.0, tint),
        Vertex3D(.5, -.5, -.5, 0.0, 0.0, tint),
        Vertex3D(.5, .5, -.5, 1.0, 0.0, tint),
        Vertex3D(.5, .5, .5, 1.0, 1.0, tint),
        Vertex3D(.5, -.5, .5, 0.0, 1.0, tint),

        Vertex3D(-.5, -.5, -.5, 0.0, 0.0, tint),
        Vertex3D(.5, -.5, -.5, 1.0, 0.0, tint),
        Vertex3D(.5, -.5, .5, 1.0, 1.0, tint),
        Vertex3D(-.5, -.5, .5, 0.0, 1.0, tint),
        Vertex3D(.5, .5, -.5, 0.0, 0.0, tint),
        Vertex3D(-.5, .5, -.5, 1.0, 0.0, tint),
        Vertex3D(-.5, .5, .5, 1.0, 1.0, tint),
        Vertex3D(.5, .5, .5, 0.0, 1.0, tint),
    };

    std::vector<unsigned int> indices = std::vector<unsigned int>{
        //front and back
        0, 3, 2,
        2, 1, 0,
        4, 5, 6,
        6, 7, 4,

        //left/right faces
        11, 8, 9,
        9, 10, 11,
        12, 13, 14,
        14, 15, 12,

        //bottom and top faces
        16, 17, 18,
        18, 19, 16,
        20, 21, 22,
        22, 23, 20
    };

    mesh = Mesh(vertices, indices, texture);

    mesh.scale(glm::vec3(size));
}

void Cube::draw(Shader* shader){
    mesh.draw(shader);
}

void Cube::rotate(float rotation, glm::vec3 axis){
    mesh.rotate(rotation, axis);
}

void Cube::scale(glm::vec3 scale){
    mesh.scale(scale);
}

void Cube::translate(glm::vec3 translation){
    mesh.translate(translation);
}
