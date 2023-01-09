#ifndef SPRITE_H
#define SPRITE_H

#include "Texture.h"
#include "../utils/Vector2.h"
#include "../utils/Rectangle.h"
#include "../utils/Color.h"
#include "../rendering/SpriteBatch.h"
class Sprite2D{
public:
    /// @brief Creates a Sprite2D object
    /// @param texture Texture of the sprite
    /// @param source Source rectangle of the sprite on a sprite sheet (x, y, width, height)
    Sprite2D(Texture* texture, Vector2 size, Rectangle source = Rectangle(0, 0, 1, 1));

    /// @brief Draws the sprite using SpriteBatch
    /// @param position Position of the sprite
    /// @param color Color of the sprite (default: white, no transparency)
    virtual void draw(Vector2 position, Color color = Color(255, 255, 255, 255));

    /// @brief sets the SpriteBatch that all sprites use for drawing. 
    /// @brief Only use if you know what you are doing.
    /// @param spriteBatch SpriteBatch to use for drawing
    static void setSpriteBatch(SpriteBatch* spriteBatch);

private:
    Texture* texture;
    Rectangle source;
    Vector2 size;
    static SpriteBatch* sb;
};


#endif // SPRITE_H