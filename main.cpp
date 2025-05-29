#include "Game.h"

int main()
{
    Game game;
    game.run();

    return 0;
}

/*
#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>
using namespace std;

struct SquareData {
    sf::VertexArray square;
    sf::Vector2f velocity;
};

int main() {
    sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "SFML Click and Bounce", sf::Style::Fullscreen);

    std::list<SquareData> squares;

    // G³ówna pêtla gry
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
            {
                cout << squares.size() << '\n';
                window.close();
            }


            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                sf::VertexArray square(sf::Quads, 4);
                square[0].position = mousePos;
                square[1].position = sf::Vector2f(mousePos.x + 50, mousePos.y);
                square[2].position = sf::Vector2f(mousePos.x + 50, mousePos.y + 50);
                square[3].position = sf::Vector2f(mousePos.x, mousePos.y + 50);

                for(int i = 0; i < 4; ++i)
                {
                    square[i].color = sf::Color::Green;
                }

                sf::Vector2f velocity(0.25f, 0.0f);
                squares.push_back({square, velocity});
            }
        }

        // Ruch kwadratów
        for(auto it  = squares.begin(); it != squares.end(); ++it)
        {
            for(int i = 0; i < 4; ++i)
            {
                it->square[i].position += it->velocity;
            }

            // Odbicie od krawêdzi
            for(int i = 0; i < 4; ++i)
            {
                if(it->square[i].position.x + 50 >= window.getSize().x)
                {
                    it->velocity.x = -it->velocity.x;
                    squares.push_back({it->square, it->velocity});

                    squares.back().square[0].position = sf::Vector2f(it->square[0].position.x - 70, it->square[0].position.y - 10);
                    squares.back().square[1].position = sf::Vector2f(it->square[1].position.x - 70, it->square[1].position.y - 10);
                    squares.back().square[2].position = sf::Vector2f(it->square[2].position.x - 70, it->square[2].position.y - 10);
                    squares.back().square[3].position = sf::Vector2f(it->square[3].position.x - 70, it->square[3].position.y - 10);

                    break;
                }
                else if(it->square[i].position.x <= 0)
                {
                    it->velocity.x = -it->velocity.x;
                    squares.push_back({it->square, it->velocity});

                    squares.back().square[0].position = sf::Vector2f(it->square[0].position.x + 70, it->square[0].position.y + 10);
                    squares.back().square[1].position = sf::Vector2f(it->square[1].position.x + 70, it->square[1].position.y + 10);
                    squares.back().square[2].position = sf::Vector2f(it->square[2].position.x + 70, it->square[2].position.y + 10);
                    squares.back().square[3].position = sf::Vector2f(it->square[3].position.x + 70, it->square[3].position.y + 10);

                    break;
                }
            }
        }

        window.clear(sf::Color::Black);

        // Rysuj kwadraty za pomoc¹ sf::VertexArray
        for (const auto& square : squares) {
            window.draw(square.square);
        }

        window.display();
    }

    return 0;
}
*/
/*
#include <SFML/Graphics.hpp>
#include <iostream>
//This function returns vertex array by given number of triangles
sf::VertexArray newShape(int numberOfTriangles) {
    sf::VertexArray shape(sf::Triangles);
    //we are going trough every point in each triangle
    for (int i=0;i<3*numberOfTriangles;i++){
        //creating points of triangles as vertexes 1, 2 and 3
        sf::Vertex v1(sf::Vector2f(rand() % 800, rand() % 600));
        sf::Vertex v2(sf::Vector2f(v1.position.x - 7, v1.position.y - 20));
        sf::Vertex v3(sf::Vector2f(v1.position.x + 7, v1.position.y - 20));
        //setting color
        v1.color = v2.color = v3.color = sf::Color(49, 102, 156, 150);
        //rotating for random angle
        sf::Transform transform;
        transform.rotate(rand()%90, (v2.position.x + v3.position.x) / 2,v1.position.y - 10);
        v1.position = transform.transformPoint(v1.position);
        v2.position = transform.transformPoint(v2.position);
        v3.position = transform.transformPoint(v3.position);
        //appending them into vertex array
        shape.append(v1);
        shape.append(v2);
        shape.append(v3);

    }
    return shape;
}
//rotate function finds the middle of 3 vertexes and rotates them
void rotate(sf::VertexArray& array, double angle){
    for (int i=0;i<array.getVertexCount();i+=3){
        sf::Transform transform;
        transform.rotate(angle, (array[i+1].position.x + array[i+2].position.x) / 2, (array[i].position.y + array[i+1].position.y)/2);
        array[i].position = transform.transformPoint(array[i].position);
        array[i+1].position = transform.transformPoint(array[i+1].position);
        array[i+2].position = transform.transformPoint(array[i+2].position);
    }

}
int main() {
    sf::Clock dtClock, fpsTimer;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Too Slow");
    //creating new array with 30000 triangles
    sf::VertexArray shapes = newShape(100000);
    window.setFramerateLimit(60);
    while (window.isOpen()) {
        //event to close window on close button
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(50, 50, 50));
        //no need for for now, as you can rotate them all in function and draw them together
        rotate(shapes,5);
        window.draw(shapes);
        window.display();
        float dt = dtClock.restart().asSeconds();
        if (fpsTimer.getElapsedTime().asSeconds() > 1) {
            fpsTimer.restart();
            std::cout << ((1.0 / dt > 60) ? 60 : (1.0 / dt)) << std::endl;
        }
    }
}
*/


/*
#include "Player.h"
#include "Enemy.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <chrono>
using namespace std;

void initRenderWindow();
bool initFullScreenMode();
void initWindowMode();

void updatePlayers();
void updatePlayerMove(std::list<Player>::iterator &player);

uint8_t constexpr static _resNum = 10;
uint16_t constexpr static _resolutions[_resNum][2] = {
    {640, 360},
    {800, 450},
    {1024, 600},
    {1280, 720},
    {1366, 768},
    {1600, 900},
    {1920, 1080},
    //{2048, 1152},
    //{2560, 1440},
    {3072, 1728},
    {3840, 2160},
    {4096, 2304}};

list<Player> _players;
list<Enemy> _enemies;
char const static constexpr *_gameTitle = "Don't let'em fall";
sf::VideoMode _videoMode;
sf::RenderWindow *_window;
sf::Event _event;
std::chrono::microseconds _elapsedIter_us;

template <typename T>
T calcPercentageOfY(T const &pct)
{
    return _window->getSize().y * pct / 100;
}

template <typename T>
T calcPercentageOfX(T const &pct)
{
    return _window->getSize().x * pct / 100;
}


int main()
{
    initRenderWindow();

    _players.push_back(Player(0, "textures/spaceship1.bmp"));
    _players.back().setSize(sf::Vector2f(
        calcPercentageOfY(35.f),
        calcPercentageOfY(35.f)));
    _players.back().setXSpeedPerSec(
        calcPercentageOfX(25.f));


    sf::Font font;
    font.loadFromFile("fonts/Minecraft.ttf");

    sf::Text xd = sf::Text();

    xd.setString("Some text");
    xd.setColor(sf::Color::White);
    xd.setFont(font);

    //xd.setCharacterSize(calculateYValue(15, _window));
    //sf::Text xd2;

    //xd.setPosition((_window->getSize().x - xd.getGlobalBounds().width) / 2.f,
                   //_window->getSize().y / 2.f - xd.getGlobalBounds().height);

    //xd2.setPosition((_window->getSize().x - xd.getLocalBounds().width) / 2.f,
                   //_window->getSize().y / 2.f - xd.getLocalBounds().height);


    _elapsedIter_us = chrono::microseconds(1); ///must be above 0
    chrono::steady_clock::time_point _endIter;
    chrono::steady_clock::time_point _startIter = chrono::steady_clock::now();

    while(_window->isOpen())
    {
        _window->clear(sf::Color::Green);

        while(_window->pollEvent(_event))
        {
            switch(_event.type)
            {
                case sf::Event::Closed:
                    _window->close();
                    break;

                default: continue;
            }
        }
        updatePlayers();
        for(auto const &enemy : _enemies)
        _window->draw(enemy.getForm());

        for(auto const &player : _players)
            _window->draw(player.getForm());

        _window->display();

        _endIter = chrono::steady_clock::now();
        _elapsedIter_us = chrono::duration_cast<chrono::microseconds>(_endIter - _startIter);
        _startIter = _endIter;
    }

    delete _window;
    _window = nullptr;

    return 0;
}


void initRenderWindow()
{   ///get current desktop mode of a user
    _window = nullptr;
    _videoMode = sf::VideoMode::getDesktopMode();

    if(initFullScreenMode() == false)
    {
        initWindowMode();
    }

    _window->setMouseCursorVisible(false);
}

bool initFullScreenMode()
{   ///check if any of the predefined resolutions are equal to the user's
    for(unsigned short i = 0; i < _resNum; ++i)
    {
        if(   _resolutions[i][0] == _videoMode.width
           && _resolutions[i][1] == _videoMode.height)
        {
            _videoMode.width = _resolutions[i][0];  ///if so, create a window
            _videoMode.height = _resolutions[i][1]; ///in full-screen mode

            _window = new sf::RenderWindow(_videoMode, _gameTitle,
                                           sf::Style::Fullscreen);

            return true;
        }
    }

    return false;
}

void initWindowMode() ///if not, create the largest possible
{                           ///window with one of the predefined resolutions
    for(int i = _resNum - 1; i >= 0; --i)
    {
        if(   _resolutions[i][0] <= _videoMode.width
           && _resolutions[i][1] <= _videoMode.height)
        {
            _videoMode.width = _resolutions[i][0];  ///if so, create a window
            _videoMode.height = _resolutions[i][1]; ///in full-screen mode

            _window = new sf::RenderWindow(_videoMode, _gameTitle,
                                             sf::Style::Titlebar
                                           | sf::Style::Close);

            return;
        }
    }
}
//dodaj wszystko, co niezbedne
void updatePlayers() //called each time in update() function
{
    for(list<Player>::iterator it = _players.begin(); it != _players.end(); ++it)
    {
        updatePlayerMove(it);
    }
}

void updatePlayerMove(std::list<Player>::iterator &player)
{
    if(sf::Keyboard::isKeyPressed(player->getMoveLeftButton()))
    {
        if(sf::Keyboard::isKeyPressed(player->getMoveRightButton()))
        {
            if(player->getRecentlyPressedMoveButton() == player->getMoveRightButton())
            {
                if(player->getPosition().x + player->getGlobalBounds().width / 2.f > 0)
                {
                    player->moveLeftWithTheSetVelocity(_elapsedIter_us.count());
                }
            }
            else if(player->getPosition().x + player->getGlobalBounds().width / 2.f < _window->getSize().x)
            {
                player->moveRightWithTheSetVelocity(_elapsedIter_us.count());
            }
        }
        else if(player->getPosition().x + player->getGlobalBounds().width / 2.f > 0)
        {
            player->moveLeftWithTheSetVelocity(_elapsedIter_us.count());
            player->setRecentlyPressedMoveButton(player->getMoveLeftButton());
        }
    }
    else if(   sf::Keyboard::isKeyPressed(player->getMoveRightButton())
            && player->getPosition().x + player->getGlobalBounds().width / 2.f < _window->getSize().x)
    {
        player->moveRightWithTheSetVelocity(_elapsedIter_us.count());
        player->setRecentlyPressedMoveButton(player->getMoveRightButton());
    }
}*/
