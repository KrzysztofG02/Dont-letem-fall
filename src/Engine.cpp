#include "Game.h"

using namespace std;



bool const Game::isRunning() const
{
    return _window->isOpen();
}


void Game::run() //engine
{
    _gameStage = GameStage::intro;
    _stagePhasis = StagePhasis::loading;

    _elapsedIter_us = chrono::microseconds(1); ///must be above 0
    chrono::steady_clock::time_point _endIter;
    chrono::steady_clock::time_point _startIter = chrono::steady_clock::now();

    while(this->isRunning())
    {
        this->pollEvents();
        this->update();
        this->render();

        _endIter = chrono::steady_clock::now();
        _elapsedIter_us = chrono::duration_cast<chrono::microseconds>(_endIter - _startIter);
        _startIter = _endIter;
    }
}


void Game::pollEvents()
{
    while(_window->pollEvent(_event))
    {
        switch(_event.type)
        {
            case sf::Event::Closed:
                _window->close();
                return;

            default: return;
        }
    }
}


void Game::update()
{
    (this->*_stageFunctions[_gameStage][_stagePhasis])();
}


void Game::render()
{
    _window->clear(_backgroundColor);

    for(auto const &enemy : _enemies)
        _window->draw(enemy.getForm());

    for(auto const &bullet : _bullets)
        _window->draw(bullet.getForm());

    for(auto const &player : _players)
        _window->draw(player.getForm());

    for(auto const &huds : _huds)
        _window->draw(huds);

    for(auto const &overlay : _overlays)
        _window->draw(overlay);

    for(auto const &text : _texts)
        _window->draw(text);

    _window->display();
}
