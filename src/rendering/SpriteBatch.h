#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H

#include <opengl/opengl.h>
#include <vector>
#include <map>
#include "Texture.h"
#include "../utils/Rectangle.h"
#include "../gl/Shader.h"
#include "../utils/Color.h"

#include <thread>
#include <stdio.h>

struct Vertex{
    /// @brief Creates a new Vertex, simplifies setting gl vertex attributes
    /// @param x x coordinate
    /// @param y y coordinate
    /// @param u u vertex attribute
    /// @param v v vertex attribute
    /// @param color color of the vertex
    Vertex(GLfloat x, GLfloat y, GLfloat u, GLfloat v, Color color);
    GLfloat x, y, u, v;
    GLfloat r, g, b, a;
};

class SpriteBatch{
public:
    /// @brief Creates a SpriteBatch object
    /// @param shader Shader to use for rendering
    SpriteBatch(Shader* shader);

    /// @brief Draws a texture to the screen
    /// @param texture Texture to draw
    /// @param source Source rectangle of the texture
    /// @param destination Destination rectangle of the texture 
    /// @param color Color of the texture (default: white, no transparency) 
    void draw(Texture texture, Rectangle source, Rectangle destination, Color color = Color(255, 255, 255, 255));

    void render();

    /// @brief Colors the gl window
    /// @param color Color of the window
    void colorWindow(Color color);

    /// @brief Colors the gl window
    /// @param r red value (0-255)
    /// @param g green value (0-255)
    /// @param b blue value (0-255)
    /// @param a alpha value (0-255)
    void colorWindow(float r, float g, float b, float a);


private:

    struct QueueEntry{
        QueueEntry(Texture texture, Shader* shader);

        Texture texture;
        std::vector<Vertex> quads;
        bool isUpdated;
        Shader* shader;

        void add(Rectangle source, Rectangle destination, Color color);
    };

private:
    std::vector<size_t> old;
    std::vector<QueueEntry> queue;
    std::vector<GLuint> VBOs;
    Shader* shader;

    size_t getHash(QueueEntry entry);
    size_t getHash(Vertex v);
};

#endif // SPRITEBATCH_H