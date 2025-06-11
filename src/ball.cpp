#include "ball.hpp"

Ball::Ball(int type)
{
    ball.setRadius(10);
    if(type == 0)
    {
        this->type = 0;
        ball.setPosition({WIDTH / 2 * TILESIZE - 102, HEIGHT / 2 * TILESIZE});
        ball.setFillColor(sf::Color::Black);
        ball.setOutlineColor(sf::Color::White);
    }
    if(type == 1)
    {
        this->type = 1;
        ball.setPosition({3 * WIDTH / 4 * TILESIZE, 3 * HEIGHT / 4 * TILESIZE});
        velocity = {-SPEED, -SPEED};
        ball.setFillColor(sf::Color::White);
        ball.setOutlineColor(sf::Color::Black);
    }

    ball.setOutlineThickness(1);
}

void Ball::update(float deltaTime)
{
    if(ball.getPosition().x - ball.getRadius() <= 0)
    {
        velocity.x = -velocity.x;
    }

    if(ball.getPosition().x + ball.getRadius() >= TILESIZE * WIDTH)
    {
        velocity.x = -velocity.x;
    }

    if(ball.getPosition().y - ball.getRadius() <= 0 || ball.getPosition().y + ball.getRadius() >= TILESIZE * HEIGHT)
    {
        velocity.y = -velocity.y;
    }

    ball.move(velocity * deltaTime);
}

void Ball::draw(sf::RenderWindow& window)
{
    window.draw(ball);
}

sf::Vector2f Ball::getPosition() const{ return ball.getPosition(); }

float Ball::getRadius() const{ return ball.getRadius(); }

sf::Vector2f Ball::getVelocity() const{ return velocity; }

bool Ball::isWhite() const{ return ball.getFillColor() == sf::Color::White; }

void Ball::setVelocity(sf::Vector2f newVelocity)
{
    velocity = newVelocity;
}
