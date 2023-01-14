#include "Font.h"

SpriteBatch* Font::sb = nullptr;

Font::Font(const char* fontPath, int fontSize){

    if(FT_Init_FreeType(&FT)){
        std::cout << "Could not init FreeType Library" << std::endl;
        return;
    }

    FT_Face face;

    if(FT_New_Face(FT, fontPath, 0, &face)){
        std::cout << "Failed to load font" << std::endl;
        return;
    }

    FT_Set_Pixel_Sizes(face, 0, fontSize);
    this->fontSize = (float)fontSize;

    int width = 0, height = 0;

    for(int i = 32; i < 128; i++){
        if(FT_Load_Char(face, i, FT_LOAD_RENDER)){
            std::cout << "Failed to load Glyph" << std::endl;
            continue;
        }

        width += face->glyph->bitmap.width;
        height = std::max(height, (int)face->glyph->bitmap.rows);
    }

    int x = 0; 
    this->texture = new Texture(width, height);
    this->texture->bind();

    for(int i = 32; i < 128; i++){
        if(FT_Load_Char(face, i, FT_LOAD_RENDER)){
            printf("loading character %i failed\n", i);
            continue;
        }

        glTexSubImage2D(GL_TEXTURE_2D, 0, x, 0, face->glyph->bitmap.width,
        face->glyph->bitmap.rows, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

        // Store character info for later use
        info[i].ax = face->glyph->advance.x >> 6;
        info[i].ay = face->glyph->advance.y >> 6;
    
        info[i].bw = face->glyph->bitmap.width;
        info[i].bh = face->glyph->bitmap.rows;

        info[i].b1 = face->glyph->bitmap_left;
        info[i].bt = face->glyph->bitmap_top;

        info[i].tx = (float)x / width;
        info[i].tw = (float)face->glyph->bitmap.width / width;
        info[i].th = (float)face->glyph->bitmap.rows / height;

        x += face->glyph->bitmap.width;
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    this->texture->unbind();

    FT_Done_Face(face);

    std::cout << "successfully loaded font: " << fontPath << std::endl;
}

void Font::draw(const char* text, Vector2 location, Color color){
    Vector2 pos = location;

    //checks if the character is within the range of drawable characters
    for(int i = 0; i < strlen(text); i++){
        if(text[i] < 32 || text[i] >= 128){
            continue;
        }
        
        //extracts info for glyph that needs to be rendered
        CharacterInfo ch = info[(int)text[i]];

        int width = ch.bw;
        int height = ch.bh;
        int x = pos.x + ch.b1;
        int y = pos.y - ch.bt;

        Rectangle source(ch.tx, 0, ch.tw, ch.th);
        Rectangle bounds(x, y, width, height);

        sb->activateFont();
        sb->draw(*texture, source, bounds, color);      
        sb->activateDefault();   
            
        pos.x += ch.ax;
    }   
}

Vector2 Font::size(std::string text){
    Vector2 tempSize = Vector2(0, 0);

    for(int i = 0, size = text.size(); i < size; i++){
        if(text[i] < 32 || text[i] >= 128){
            continue;
        }

        CharacterInfo ch = info[(int)text[i]];

        tempSize.x += ch.bw;
    }

    tempSize.y = fontSize;
    return tempSize;
}

void Font::setSpriteBatch(SpriteBatch* spriteBatch){
    sb = spriteBatch;
}
