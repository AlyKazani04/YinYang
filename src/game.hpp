#pragma once

#include <SFML/Graphics.hpp>
#include "ball.hpp"
#include "constants.hpp"

class Game
{
    private:
        Ball yin;
        Ball yang;

        sf::Clock clock;

        sf::Color tileColors[HEIGHT][WIDTH];

        void updateBallTileInteraction(Ball& ball);
        
    public:
        
        Game();
        
        void update(float deltaTime);
        
        void render(sf::RenderWindow& window);
        
}; 