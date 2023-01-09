#include "Sprite2D.h"

SpriteBatch* Sprite2D::sb = NULL;

void Sprite2D::setSpriteBatch(SpriteBatch* spriteBatch){
    sb = spriteBatch;
}

Sprite2D::Sprite2D(Texture* texture, Vector2 size, Rectangle source) : texture(texture){
    this->source = source;
    this->size = size;
}


void Sprite2D::draw(Vector2 position, Color color){
    sb->draw(*texture, source, Rectangle(position.x, position.y, size.x, size.y), color);
}