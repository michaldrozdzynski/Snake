#include <vector>
#include "snake.h"
#include <fstream>

void OnCreate(sf::Texture& head_T, sf::Texture& body_T, std::vector<Snake*>& snake, int& size, int difficult, sf::Sprite& wall1, sf::Sprite& wall2,
    sf::Sprite& wall3, sf::Sprite& wall4, sf::Sprite& apple);
void kierunek(int x, std::vector<Snake*>& snake);
void Apple(int size, sf::Sprite& apple, int DIFFICULT_LV, std::vector<Snake*> snake);
bool eat(int indeks,int x1,int y1, int difficult, std::vector<Snake*>& snake);
void grow(int& size, std::vector<Snake*>& snake, sf::Texture& body_T);
bool gameover(std::vector<Snake*>& snake, int size,int difficult);
void rekordy(int nowy);
std::string intToStr(int n);

int main()
{
    sf::RenderWindow window(sf::VideoMode(425, 450), "Snake",sf::Style::Close);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    std::vector<Snake*>snake;
    sf::Texture head, body;
    head.loadFromFile("img/head.png");
    body.loadFromFile("img/body.png");
    ////////////////////tło//////////////////
    sf::Texture background_T;
    background_T.loadFromFile("img/background.png");
    sf::Sprite background;
    background.setTexture(background_T);
    background.setPosition(0, 0);
    
    ///////////////jedzenie dla węża//////////////////
    sf::Texture apple_T;
    apple_T.loadFromFile("img/apple.png");
    sf::Sprite apple;
    apple.setTexture(apple_T);

    /////////////////przeszkody/////////////////////
    sf::Texture wall_T;
    wall_T.loadFromFile("img/wall.png");
    sf::Sprite wall1, wall2, wall3, wall4;
    wall1.setTexture(wall_T);
    wall2.setTexture(wall_T);
    wall3.setTexture(wall_T);
    wall4.setTexture(wall_T);

    ////////////////Sprite z napisem Speed//////////////
    sf::Texture speed_T;
    speed_T.loadFromFile("img/Speed.bmp");
    sf::Sprite speed;
    speed.setTexture(speed_T);
    speed.setPosition(100,50);

    ////////////////////////Sprite z napisem difficult level////////////////
    sf::Texture level_T;
    level_T.loadFromFile("img/Level.bmp");
    sf::Sprite level;
    level.setTexture(level_T);
    level.setPosition(12.5,50);

    ////////////////Sprite z napisem start//////////////////////
    sf::Texture start_T;
    start_T.loadFromFile("img/Start.bmp");
    sf::Sprite start;
    start.setTexture(start_T);
    start.setPosition(100,100);

    ///////////////////Sprity z napisami 1, 2 ,3////////////////////
    sf::Texture N1,N2,N3;
    sf::Sprite n1, n2, n3;
    N1.loadFromFile("img/1.bmp");
    n1.setTexture(N1);
    n1.setPosition(50,200);
    N2.loadFromFile("img/2.bmp");
    n2.setTexture(N2);
    n2.setPosition(187,200);
    N3.loadFromFile("img/3.bmp");
    n3.setTexture(N3);
    n3.setPosition(325,200);


    ///////////////////ustawienie czcionki i napisów/////////////////////////
    sf::Font font;
    font.loadFromFile("Arial.ttf");
    sf::Text text;
    text.setFont(font);
    text.setString("SCORE:");
    text.setCharacterSize(24);
    text.setPosition(0,423);
    sf::Text text2;
    text2.setFont(font);
    text2.setString("HIGH SCORE:");
    text2.setCharacterSize(24);
    text2.setPosition(180,423);
    sf::Text pkt;
     
    pkt.setFont(font);
    pkt.setCharacterSize(24);
    pkt.setPosition(95,423);

    sf::Text rekord;
    rekord.setFont(font);
    rekord.setCharacterSize(24);
    rekord.setPosition(341,423);


    int Rekord;
    std::ifstream plik2( "rekord.bin", std::ios::binary );
    if(!plik2.read(( char * ) & Rekord, sizeof Rekord ))
    Rekord = 0;

    int ilePunktow = 0;//pokazuje ile punktów zdobył gracz aktualnie
    int SPEED_LV, DIFFICULT_LV;
    int direct = 0;
    int size;
    int punkty = 0; //pokazuje ile punktów zdobędzie gracz za 1 jabłko
    int faza = 0; //0 - napis start, 1 - wybór szybkości, 2 - wybór mapy, 3- rozpoczęcie się gry
    int moveFrequensy = 0;


    while(window.isOpen())
    {
        pkt.setString(intToStr(ilePunktow));
        rekord.setString(intToStr(Rekord));
        //Vector2i pozycja = Mouse::getPosition(window);
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();

            switch (faza)
            {
            case 0:
                if (start.getGlobalBounds().contains(window.mapPixelToCoords(mousePos)))
                {
                    if (event.type == sf::Event::MouseButtonPressed)
                    {
                        if (event.mouseButton.button == sf::Mouse::Left)
                            faza++;
                    }
                }
            break;
            case 1:
            {
                if (n1.getGlobalBounds().contains(window.mapPixelToCoords(mousePos)))
                {
                    if (event.type == sf::Event::MouseButtonPressed)
                    {
                        if (event.mouseButton.button == sf::Mouse::Left)
                        {
                            faza++;
                            DIFFICULT_LV = 1;
                            punkty += 10;
                        }
                    }
                }
                else if (n2.getGlobalBounds().contains(window.mapPixelToCoords(mousePos)))
                {
                    if (event.type == sf::Event::MouseButtonPressed)
                    {
                        if (event.mouseButton.button == sf::Mouse::Left)
                        {
                            faza++;
                            DIFFICULT_LV = 2;
                            punkty += 20;
                        }
                    }
                }
                else if (n3.getGlobalBounds().contains(window.mapPixelToCoords(mousePos)))
                {
                    if (event.type == sf::Event::MouseButtonPressed)
                    {
                        if (event.mouseButton.button == sf::Mouse::Left)
                        {
                            faza++;
                            DIFFICULT_LV = 3;
                            punkty += 30;
                        }
                    }
                }
            }
            break;
            case 2:
            {
                if (n1.getGlobalBounds().contains(window.mapPixelToCoords(mousePos)))
                {
                    if (event.type == sf::Event::MouseButtonPressed)
                    {
                        if (event.mouseButton.button == sf::Mouse::Left)
                        {
                            faza++;
                            SPEED_LV = 15;
                            punkty += 10;
                            OnCreate(head, body, snake, size, DIFFICULT_LV, wall1, wall2,
                                wall3, wall4, apple);
                        }
                    }
                }
                else if (n2.getGlobalBounds().contains(window.mapPixelToCoords(mousePos)))
                {
                    if (event.type == sf::Event::MouseButtonPressed)
                    {
                        if (event.mouseButton.button == sf::Mouse::Left)
                        {
                            faza++;
                            SPEED_LV = 10;
                            punkty += 20;
                            OnCreate(head, body, snake, size, DIFFICULT_LV, wall1, wall2,
                                wall3, wall4, apple);                    
                        }
                    }
                }
                else if (n3.getGlobalBounds().contains(window.mapPixelToCoords(mousePos)))
                {
                    if (event.type == sf::Event::MouseButtonPressed)
                    {
                        if (event.mouseButton.button == sf::Mouse::Left)
                        {
                            faza++;
                            SPEED_LV = 5;
                            punkty += 30;
                            OnCreate(head, body, snake, size, DIFFICULT_LV, wall1, wall2,
                                wall3, wall4, apple);
                        }
                    }
                }
            }
            break;
            case 3:
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A) && direct != 3)
                {
                    direct = 3;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D) && direct != 1)
                {
                    direct = 1;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W) && direct != 4)
                {
                    direct = 4;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S) && direct != 2)
                {
                    direct = 2;
                }
            }
            }
           
        }

        if(faza == 3)
        {
            if(eat(0,apple.getPosition().x,apple.getPosition().y, DIFFICULT_LV, snake))
            {
                Apple(size, apple, DIFFICULT_LV, snake);
                grow(size, snake, body);
                ilePunktow += punkty;
            }
            if(moveFrequensy>SPEED_LV)
            {
                kierunek(direct,snake);
                for(int i=0; i<=size; i++)
                {
                    snake[i]->ruch();
                }
                moveFrequensy = 0;
            }
            if(moveFrequensy == 0)
            {
                for(int i=size; i>=1; i--)
                {
                    if(snake[i]->direct!=snake[i-1]->direct)
                    {
                        snake[i]->direct=snake[i-1]->direct;
                    }
                }
            }
            moveFrequensy++;
        }
        window.clear();
        window.draw(background);
        window.draw(text);
        window.draw(text2);
        window.draw(pkt);
        window.draw(rekord);
        if(faza == 0)
            window.draw(start);
        if(faza == 1)
        {
            window.draw(level);
            window.draw(n1);
            window.draw(n2);
            window.draw(n3);
        }
        if(faza == 2)
        {
            window.draw(speed);
            window.draw(n1);
            window.draw(n2);
            window.draw(n3);
        }

        if(faza == 3)
        {
            window.draw(apple);
            if(DIFFICULT_LV!=1){window.draw(wall1); window.draw(wall2);}
            if(DIFFICULT_LV==3){window.draw(wall3); window.draw(wall4);}
            for(int i=0; i<=size; i++)
            {
                snake[i]->rysuj(window);

            }
        }
        window.display();

        if(faza == 3  && gameover(snake, size, DIFFICULT_LV))
        {
            if(ilePunktow>Rekord)
            {
                Rekord = ilePunktow;
                rekordy(Rekord);
            }
            faza = 0;
            direct = 0;
            punkty = 0;
            ilePunktow = 0;
        }
    }

    return 0;
}

void rekordy(int nowy)
{
    std::ofstream plik( "rekord.bin",std::ios::binary );
    plik.write(( const char * ) & nowy, sizeof nowy );
}
void OnCreate(sf::Texture& head_T, sf::Texture& body_T, std::vector<Snake*>& snake, int& size,int difficult, sf::Sprite& wall1, sf::Sprite& wall2, 
    sf::Sprite& wall3, sf::Sprite& wall4, sf::Sprite& apple)
{
    size=2;
    snake.clear();
    snake.push_back(new Snake());
    snake.push_back(new Snake());
    snake.push_back(new Snake());

    snake[0]->body.setTexture(head_T);
    snake[1]->body.setTexture(body_T);
    snake[2]->body.setTexture(body_T);

    snake[0]->body.setPosition(100,100);
    snake[1]->body.setPosition(75,100);
    snake[2]->body.setPosition(50,100);

    switch(difficult)
    {
        case 2:
        {
            wall1.setTextureRect(sf::IntRect(0, 0, 25, 275));
            wall2.setTextureRect(sf::IntRect(0, 0, 25, 275));
            wall1.setPosition(75,75);
            wall2.setPosition(325,75);

            snake[0]->body.setPosition(100,25);
            snake[1]->body.setPosition(75,25);
            snake[2]->body.setPosition(50,25);
        }
        break;
        case 3:
        {
            wall1.setTextureRect(sf::IntRect(0, 0, 25, 175));
            wall2.setTextureRect(sf::IntRect(0, 0, 175, 25));
            wall3.setTextureRect(sf::IntRect(0, 0, 25, 175));
            wall4.setTextureRect(sf::IntRect(0, 0, 175, 25));
            wall1.setPosition(75,175);
            wall2.setPosition(175,325);
            wall4.setPosition(75,75);
            wall3.setPosition(325,75);
        }
        break;
    }

    Apple(size, apple, difficult, snake);
}
bool gameover(std::vector<Snake*>& snake, int size, int difficult)
{
    int X = snake[0]->body.getPosition().x;
    int Y = snake[0]->body.getPosition().y;

    switch (snake[0]->direct)
    {
    case 2:
    {
        X += -25;
    }
    break;
    case 3:
    {
        X += -25;
        Y += -25;
    }
    break;
    case 4:
    {
        Y += -25;
    }
    break;
    }
    for (int i = 1; i <= size; i++)
    {
        if (X == snake[i]->body.getPosition().x && Y == snake[i]->body.getPosition().y)
            return true;
    }
    if(X<0||X>400||Y<0||Y>400)
        return true;
    if(difficult==2)
    {
        if((X==75||X==325)&&Y>=75&&Y<=325)
        return true;
    }
    if(difficult==3)
    {
        if(Y==75&&X>=75&&X<=225)
        return true;
        if(Y==325&&X>=175&&X<=325)
        return true;
        if(X==75&&Y>=175&&Y<=325)
        return true;
        if(X==325&&Y>=75&&Y<=225)
        return true;
    }

    return false;
}
void grow(int& size, std::vector<Snake*>& snake, sf::Texture& body)
{
    size++;
    snake.push_back(new Snake());
    snake[size]->body.setTexture(body);
    int x=snake[size-1]->body.getPosition().x;
    int y=snake[size-1]->body.getPosition().y;
    snake[size]->direct = snake[size-1]->direct;


    switch(snake[size-1]->direct)
    {
    case 1:
        snake[size]->body.setPosition(x-25,y);
        break;
    case 2:
        snake[size]->body.setPosition(x,y-25);
        break;
    case 3:
        snake[size]->body.setPosition(x+25,y);
        break;
    case 4:
        snake[size]->body.setPosition(x,y+25);
        break;
    }
}

void kierunek(int x, std::vector<Snake*>& snake)
{
    switch(x)
    {
    case 1:
    {
        if(snake[0]->direct!=1&&snake[0]->direct!=3)
        {
            if(snake[0]->direct==4)
            {
                snake[0]->body.rotate(90);
                snake[0]->body.move(0,-25);
            }
            if(snake[0]->direct==2)
            {
                snake[0]->body.rotate(270);
                snake[0]->body.move(-25,0);
            }
            snake[0]->direct=1;
        }
    }
    break;
    case 2:
    {
        if(snake[0]->direct!=4&&snake[0]->direct!=2)
        {
            if(snake[0]->direct==3)
            {
                snake[0]->body.rotate(270);
                snake[0]->body.move(0,-25);
            }
            if(snake[0]->direct==1)
            {
                snake[0]->body.rotate(90);
                snake[0]->body.move(25,0);
            }
            snake[0]->direct=2;
        }
    }
    break;
    case 3:
    {
        if(snake[0]->direct!=1&&snake[0]->direct!=3)
        {
            if(snake[0]->direct==4)
            {
                snake[0]->body.rotate(270);
                snake[0]->body.move(25,0);
            }
            if(snake[0]->direct==2)
            {
                snake[0]->body.rotate(90);
                snake[0]->body.move(0,25);
            }
            snake[0]->direct=3;
        }
    }
    break;
    case 4:
    {
        if(snake[0]->direct!=2&&snake[0]->direct!=4)
        {
            if(snake[0]->direct==1)
            {
                snake[0]->body.rotate(270);
                snake[0]->body.move(0,25);
            }
            if(snake[0]->direct==3)
            {
                snake[0]->body.rotate(90);
                snake[0]->body.move(-25,0);
            }
            snake[0]->direct=4;
        }
    }
    break;

    }
}

void Apple(int size, sf::Sprite& apple,int DIFFICULT_LV, std::vector<Snake*> snake)
{
    srand(time( NULL ));
    int x,y;
    x=(rand()%17)*25;
    y=(rand()%17)*25;

    for(int i=0; i<=size; i++)
    {
        while(eat(i,x,y,DIFFICULT_LV,snake))
        {
            x=(rand()%17)*25;
            y=(rand()%17)*25;
            i=0;
        }
    }

    apple.setPosition(x,y);
}
bool eat(int indeks,int x1,int y1, int difficult,std::vector<Snake*>& snake)
{
    int x2,y2;
    x2=snake[indeks]->body.getPosition().x;
    y2=snake[indeks]->body.getPosition().y;


    if(indeks!=0)
    {
        if(x1==x2&&y1==y2)
            return true;
    }
    if(difficult==2)
    {
        if((x1==75||x1==325)&&y1>=75&&y1<=325)
        return true;
    }
    if(difficult==3)
    {
        if(y1==75&&x1>=75&&x1<=225)
        return true;
        if(y1==325&&x1>=175&&x1<=325)
        return true;
        if(x1==75&&y1>=175&&y1<=325)
        return true;
        if(x1==325&&y1>=75&&y1<=225)
        return true;
    }

    switch(snake[indeks]->direct)
    {
    case 1:
    {
        if(x1==x2&&y1==y2)
            return true;
    }
    break;
    case 2:
    {
        if(x1==x2-25&&y1==y2)
            return true;
    }
    break;
    case 3:
    {
        if(x1==x2-25&&y1==y2-25)
            return true;
    }
    break;
    case 4:
    {
        if(x1==x2&&y1==y2-25)
            return true;
    }
    break;
    }
    return false;

}
std::string intToStr(int n)
{
     std::string tmp, ret;
     if(n < 0) {
      ret = "-";
      n = -n;
     }
     do {
      tmp += n % 10 + 48;
      n -= n % 10;
     }
     while(n /= 10);
     for(int i = tmp.size()-1; i >= 0; i--)
      ret += tmp[i];
     return ret;
}


