#pragma once

#include <SFML/Graphics.hpp>
#include <random>
#include "constants.hpp"

class Ball{
    private:
        sf::CircleShape ball;
        const float SPEED = 180;
        sf::Vector2f velocity = {SPEED, SPEED};

        int type; // 0 = yin, 1 = yang

    public:
        Ball(int type);

        void update(float deltaTime);

        void draw(sf::RenderWindow& window);

        sf::Vector2f getPosition() const;
        float getRadius() const;
        sf::Vector2f getVelocity() const;

        bool isWhite() const;

        void setVelocity(sf::Vector2f newVelocity);
};