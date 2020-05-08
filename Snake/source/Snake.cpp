#include "snake.h"


void Snake::rysuj(sf::RenderWindow &window)
{
    window.draw(body);
}
Snake::Snake()
{
    direct=1;
}
void Snake::ruch()
{
    switch(direct)
    {
        case 1: body.move(25,0);
        break;
        case 2: body.move(0,25);
        break;
        case 3: body.move(-25,0);
        break;
        case 4: body.move(0,-25);
        break;
    }
}

