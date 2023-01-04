#ifndef SPRITE_H
#define SPRITE_H

#include "Texture.h"
#include "../utils/Vector2.h"
#include "../utils/Rectangle.h"
#include "../utils/Color.h"

class Sprite2D{
public:
    /// @brief Creates a Sprite2D object
    /// @param texture Texture of the sprite
    /// @param source Source rectangle of the sprite on a sprite sheet (x, y, width, height)
    Sprite2D(Texture texture, Rectangle source);

    /// @brief Creates a Sprite2D object
    /// @param texture Texture of the sprite
    /// @param x x coordinate of the source rectangle
    /// @param y y coordinate of the source rectangle
    /// @param width width of the source rectangle
    /// @param height height of the source rectangle
    Sprite2D(Texture texture, int x, int y, int width, int height);

    /// @brief Draws the sprite using SpriteBatch
    /// @param position Position of the sprite
    /// @param color Color of the sprite (default: white, no transparency)
    virtual void draw(Vector2 position, Color color = Color(255, 255, 255, 255));

protected:
    Texture texture;
    Rectangle source;

};


#endif // SPRITE_H