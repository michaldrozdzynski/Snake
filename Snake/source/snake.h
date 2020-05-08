#include <SFML/Graphics.hpp>

class Snake
{
public:
    sf::Sprite body;
    int direct;
    void ruch();
    void rysuj(sf::RenderWindow &window);
    Snake();
};
