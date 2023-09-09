#include "src/App.h"
using namespace std;
Texture *player;
Sprite2D *playerSprite;
Vector2 playerPosition(100, 200);
Vector2 playerVelocity(0, 0);
Rectangle playerHitbox(0, 0, 0, 0);

Texture *ground;
Sprite2D *groundSprite;
Rectangle groundHitbox(0, 0, 0, 0);

const float gravity = 10.0f;

const float movementSpeed = 75.0f;
const float acceleration = 150.0f;
const float deceleration = 200.0f;
const float jumpSpeed = 5.0f;
bool isJumping = true;

class Game1 : public Game
{
public:
    void initialize() override
    {
        player = new Texture("resources/content/player.png");
        playerSprite = new Sprite2D(player, Vector2(50, 85));
        playerHitbox = Rectangle(playerPosition.x, playerPosition.y, 50, 85);

        ground = new Texture("resources/content/tile.png");
        groundSprite = new Sprite2D(ground, Vector2(2000, 500));
        groundHitbox = Rectangle(0, 500, 2000, 500);
    }
    void update(float dt) override
    {
        playerHitbox = Rectangle(playerPosition.x, playerPosition.y, 50, 85);
        // gravity
        playerVelocity.y += gravity * dt;
        playerPosition.y += playerVelocity.y;

        if (groundHitbox.intersects(playerHitbox))
        {
            Rectangle intersection = groundHitbox.getIntersection(playerHitbox);

            if (intersection.y > 0.01)
            {
                playerPosition.y -= intersection.height;
                playerVelocity.y = 0;
                isJumping = false;
            }
        }

        // Handle player input for movement
        if (KeyListener::isKeyPressed(GLFW_KEY_A))
        {
            // Accelerate left
            playerVelocity.x -= acceleration * dt;
        }
        else if (KeyListener::isKeyPressed(GLFW_KEY_D))
        {
            // Accelerate right
            playerVelocity.x += acceleration * dt;
        }
        else
        {
            // Decelerate when not moving
            if (playerVelocity.x > 0)
            {
                playerVelocity.x -= deceleration * dt;
            }
            else if (playerVelocity.x < 0)
            {
                playerVelocity.x += deceleration * dt;
            }
        }

        // Limit the maximum speed
        if (playerVelocity.x > movementSpeed)
        {
            playerVelocity.x = movementSpeed;
        }
        else if (playerVelocity.x < -movementSpeed)
        {
            playerVelocity.x = -movementSpeed;
        }

        // Handle jumping
        if (KeyListener::isKeyPressed(GLFW_KEY_SPACE) && !isJumping)
        {
            playerVelocity.y = -jumpSpeed; // Apply initial upward velocity
            isJumping = true;              // Set jumping state
        }

        // Update player position based on velocity
        playerPosition.x += playerVelocity.x * dt;
    }
    void draw(SpriteBatch *sb) override
    {
        sb->colorWindow(WINDOWS_COLOR);
        playerSprite->draw(playerPosition);
        groundSprite->draw(Vector2(0, 500));
    }
};

Game1 game;

int main()
{
    game = Game1();
    App app(&game);
}