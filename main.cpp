#include "src/App.h"

using namespace std;

Texture* texture = NULL;

Sprite2D* jorje = NULL;
Sprite2D* jorje2 = NULL;

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
        }
        void update(float dt) override{
            std::cout << "Currnet Mouse Position: " << App::mousePosition.x << ", " << App::mousePosition.y << std::endl;
        }
        void draw(SpriteBatch* sb) override{
            jorje->draw(Vector2(0, 0));
            jorje2->draw(Vector2(100, 0));
        }
};

Game1 game;

int main(){
    game = Game1();
    App app(&game);
}