#ifndef FONT_H
#define FONT_H

#include <ft2build.h>
#include FT_FREETYPE_H
#include <iostream>
#include <math.h>

#include "../utils/Vector2.h"
#include "../utils/Rectangle.h"
#include "Texture.h"
#include "SpriteBatch.h"
#include "../events/WindowListener.h"

struct CharacterInfo{
    float ax,ay,
          bw, bh, b1, bt,
          tx, tw, th;
};

struct Point{
    GLfloat x, y, s, t;
};

class Font{
public:
    Font();
    Font(const char* fontPath, int fontSize);
    void draw(const char* text, Vector2 position, Color color = Color(255, 255, 255, 255));
    Vector2 size(std::string text);

    /// @brief Sets the spritebatch to use for drawing the font
    /// @brief Only use if you know what you are doing.
    /// @param spriteBatch SpriteBatch to use for drawing.
    static void setSpriteBatch(SpriteBatch* spriteBatch);

private:
    float fontSize;
    Texture* texture;
    CharacterInfo info[128];
    FT_Library FT;
    static SpriteBatch* sb;
};

#endif //FONT_H