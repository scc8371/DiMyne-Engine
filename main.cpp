#include "src/App.h"

using namespace std;

Texture* texture = NULL;

Sprite2D* jorje = NULL;
Sprite2D* jorje2 = NULL;

Font* font = NULL;

class Game1 : public Game{
    public:
        Game1() : Game(){
            cout << "Game1 constructor" << endl;
        }
        void initialize() override{
            texture = new Texture("resources/content/jorje_poster.png");
            jorje = new Sprite2D(texture, Vector2(100, 100), Rectangle(0, 0, 1, 1));

            font = new Font("resources/font/font.ttf", 12);
        }
        void update(float dt) override{
            
        }
        void draw(SpriteBatch* sb) override{
            jorje->draw(Vector2(0, 0));
            sb->colorWindow(WHITE);
            font->draw("hello world", Vector2(500, 100), BLACK);
        }
};

Game1 game;

int main(){
    game = Game1();
    App app(&game);
}