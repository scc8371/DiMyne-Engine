#include "src/App.h"

using namespace std;

Texture* texture = NULL;

Sprite2D* jorje = NULL;
Sprite2D* jorje2 = NULL;

Song* audio1 = NULL;

Font* font = NULL;

class Game1 : public Game{
    public:
        Game1() : Game(){
            cout << "Game1 constructor" << endl;
        }
        void keyState(int* key) override{
            cout << "Game1 keyState" << endl;
        }
        void mouseState(int* button) override{
            cout << "Game1 mouseState" << endl;
        }
        void initialize() override{
            texture = new Texture("resources/content/jorje_poster.png");
            jorje = new Sprite2D(texture, Vector2(100, 100), Rectangle(0, 0, 1, 1));
            jorje2 = new Sprite2D(texture, Vector2(100, 100), Rectangle(0, 0, 1, 1));

            audio1 = new Song("resources/audio/track5.wav");

            font = new Font("resources/font/font.ttf", 32);

            std::cout << "playing audio1 " << std::endl;
            App::audio.play(*audio1);
        }
        void update(float dt) override{
        }
        void draw(SpriteBatch* sb) override{
            jorje->draw(Vector2(0, 0));
            jorje2->draw(Vector2(100, 0));

            sb->colorWindow(Color(255, 255, 255, 255));

            font->draw("hello world", Vector2(500, 100));
        }
};

Game1 game;

int main(){
    game = Game1();
    App app(&game);
}