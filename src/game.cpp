#include "game.hpp"

Game::Game() : yin(0), yang(1)
{
    for(int y = 0; y < HEIGHT; ++y){
        for(int x = 0; x < WIDTH; ++x){
            if(x < WIDTH/2)
                tileColors[y][x] = sf::Color::White;
            else
                tileColors[y][x] = sf::Color::Black;
        }
    }
}

void Game::updateBallTileInteraction(Ball& ball)
{
    sf::Vector2f pos = ball.getPosition();
    float radius = ball.getRadius();

    float right = pos.x + radius;
    float left =  pos.x - radius;
    float bottom = pos.y + radius;
    float top = pos.y - radius;

    struct Collision{
        int tileX, tileY;
        sf::Vector2f normal; // Normal vector of the collision
    };

    std::vector<Collision> collisions;

    if(right >= 0 && right < WIDTH * TILESIZE)
    {
        int tileX = (int)(right / TILESIZE);
        int tileY = (int)(pos.y / TILESIZE);
        collisions.push_back({tileX, tileY, {-1, 0}});
    }

    if(left >= 0 && left < WIDTH * TILESIZE)
    {
        int tileX = (int)(left / TILESIZE);
        int tileY = (int)(pos.y / TILESIZE);
        collisions.push_back({tileX, tileY, {1, 0}});
    }

    if(bottom >= 0 && bottom < HEIGHT * TILESIZE)
    {
        int tileX = (int)(pos.x / TILESIZE);
        int tileY = (int)(bottom / TILESIZE);
        collisions.push_back({tileX, tileY, {0, -1}});
    }

    if(top >= 0 && top < HEIGHT * TILESIZE)
    {
        int tileX = (int)(pos.x / TILESIZE);
        int tileY = (int)(top / TILESIZE);
        collisions.push_back({tileX, tileY, {0, 1}});
    }

    for(const auto& c : collisions)
    {
        if(c.tileX < 0 || c.tileX >= WIDTH || c.tileY < 0 || c.tileY >= HEIGHT)
            continue;
        
        sf::Color& tile = tileColors[c.tileY][c.tileX];
        bool isWhite = ball.isWhite();

        bool isSame = (isWhite && tile == sf::Color::White) ||
                            (!isWhite && tile == sf::Color::Black);

        if(isSame)
        {
            tile = (tile == sf::Color::White) ? sf::Color::Black : sf::Color::White;

            sf::Vector2f velocity = ball.getVelocity();

            if(c.normal.x != 0)
                velocity.x *= -1.f;
            if(c.normal.y != 0)
                velocity.y *= -1.f;

            ball.setVelocity(velocity);

            break; // only first valid collision
        }
    }
}

void Game::update(float deltaTime)
{
    if(clock.getElapsedTime().asSeconds() > 1.f)
    {
        yin.update(deltaTime);
        yang.update(deltaTime);
    }

    updateBallTileInteraction(yin);
    updateBallTileInteraction(yang);
}

void Game::render(sf::RenderWindow& window)
{
    for(int y = 0; y < HEIGHT; ++y){
        for(int x = 0; x < WIDTH; ++x){   
            float posX = x * TILESIZE;
            float posY = y * TILESIZE;
            
            sf::RectangleShape tileRect;
            tileRect.setPosition({posX, posY});
            tileRect.setSize({TILESIZE, TILESIZE});

            tileRect.setFillColor(tileColors[y][x]);

            window.draw(tileRect);
        }
    }
    yin.draw(window);
    yang.draw(window);
}