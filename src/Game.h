//=============================================================================
//Description: This file initializes the application and creates the window.
//=============================================================================
#ifndef GAME_H
#define GAME_H

#include "rendering/SpriteBatch.h"

class Game
{
public:
    Game();
    
    virtual void initialize();
    virtual void update(float dt);

    virtual void draw(SpriteBatch* spriteBatch);
    
    //input
    virtual void keyState(int* key);
    virtual void mouseState(int* button);

    /// @brief delta time between frames
    /// @return (float) delta time
    float deltaTime() { return dt; };

private:
    float prevDt; 
    float dt;
};



#endif // APP_H