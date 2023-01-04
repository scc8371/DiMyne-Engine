#include "Game.h"

/// @brief initializes the game loop
/// @return void
Game::Game(){
    prevDt = dt = 0;   
}

void Game::keyState(int* key){}
void Game::mouseState(int* button){}
void Game::initialize(){}
void Game::update(float dt){}
void Game::draw(){}