#include "src/App.h"
using namespace std;

class Game1 : public Game
{
public:
    void initialize() override
    {
        App::lockMouse(true);
    }
    void update(float dt) override
    {

    }
    void draw(SpriteBatch *sb) override
    {
        sb->colorWindow(BLACK);
    }
};

Game1 game;

int main()
{
    game = Game1();
    App app(&game);
}