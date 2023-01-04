//=============================================================================
//Description: This file initializes the application and creates the window.
//=============================================================================
#ifndef GAME_H
#define GAME_H

class Game
{
public:
    Game();
    
    virtual void initialize();
    virtual void update(float dt);

    /// @brief unimplmented draw function
    virtual void draw();
    
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