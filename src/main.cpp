#include <SFML/Graphics.hpp>
#include "game.hpp"

int main(){

    sf::RenderWindow window;
    window.create(sf::VideoMode({TILESIZE * WIDTH, TILESIZE * HEIGHT}), "YinYang", sf::Style::Default);

    sf::View view(sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(TILESIZE * WIDTH, TILESIZE * HEIGHT)));
    
    view.setViewport(sf::FloatRect({0.f, 0.f}, {1.f, 1.f})); // Stretch
    window.setView(view);
    
    sf::Clock clock;
    
    Game game;
    window.setFramerateLimit(60);

    while(window.isOpen()){

        while(const std::optional event = window.pollEvent()){
            if(event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }
        { // update loop
            float deltaTime = clock.restart().asSeconds();
            game.update(deltaTime);
        }

        { // draw loop
            window.clear();

            game.render(window);

            window.display();
        }
    }

    return 0;
}