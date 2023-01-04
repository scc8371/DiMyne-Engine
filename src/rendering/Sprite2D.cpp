#include "Sprite2D.h"

Sprite2D::Sprite2D(Texture texture, Rectangle source) : texture(texture){
    this->source = source;
}

Sprite2D::Sprite2D(Texture texture, int x, int y, int width, int height) : texture(texture){
    this->source = Rectangle(x, y, width, height);
}

void Sprite2D::draw(Vector2 position, Color color){
    //draw using spriteBatch here
}