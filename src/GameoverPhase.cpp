#include "Game.h"

using namespace std;


namespace gameover
{
    string const *gameOverText;
    chrono::microseconds constexpr static letterTransitionTime = chrono::microseconds(200000); //200 ms
    chrono::microseconds constexpr static cooldownTime = chrono::microseconds(5000000); //5 s

    float textHeight;

    unsigned short timersInUse;
    unsigned short overlaysInUse;
    unsigned short textsInUse;
}



void Game::loadGameover()
{
    gameover::timersInUse = 0;
    gameover::overlaysInUse = 0;
    gameover::textsInUse = 0;

    _timers_us.push_back(chrono::microseconds(0));
    ++gameover::timersInUse;

    _overlays.push_back(sf::RectangleShape(sf::Vector2f(_window->getSize().x, _window->getSize().y)));
    ++gameover::overlaysInUse;
    _overlays.back().setFillColor(sf::Color(0, 0, 0, 170));

    gameover::gameOverText = new string("GAME OVER");

    _texts.push_back(sf::Text("X", _font, this->calcPercentageOfY(20)));
    ++gameover::textsInUse;
    gameover::textHeight = _window->getSize().y / 2.f - _texts.back().getGlobalBounds().height;
    _texts.back().setString("");

    _gameoverStage = GameoverStage::ongoing;
}

void Game::runGameover()
{
    _timers_us.back() += _elapsedIter_us;

    if(_texts.back().getString().getSize() < gameover::gameOverText->size())
    {
        if(_timers_us.back() >= gameover::letterTransitionTime)
        {
            unsigned long integerPart = static_cast<unsigned long>(_timers_us.back() / gameover::letterTransitionTime);

            if((_texts.back().getString().getSize() + integerPart) > gameover::gameOverText->size())
            {
                _texts.back().setString(*gameover::gameOverText);
            }
            else
            {
                _texts.back().setString(gameover::gameOverText->substr(0, _texts.back().getString().getSize() + integerPart));
            }

            _texts.back().setPosition((_window->getSize().x - _texts.back().getGlobalBounds().width) / 2.0f,
                                       gameover::textHeight);

            _timers_us.back() -= integerPart * gameover::letterTransitionTime;
        }
    }
    else if(_timers_us.back() >= gameover::cooldownTime)
    {
        _gameoverStage = GameoverStage::quitting;
    }
}

void Game::quitGameover()
{
    this->clearGameover();

    gameover::timersInUse = 0;
    gameover::overlaysInUse = 0;
    gameover::textsInUse = 0;

    _stagePhasis = StagePhasis::quitting;
}

void Game::clearGameover()
{
    for(unsigned i = 0; i < gameover::timersInUse; ++i)
    {
        _timers_us.pop_back();
    }

    for(unsigned i = 0; i < gameover::textsInUse; ++i)
    {
        _texts.pop_back();
    }

    for(unsigned i = 0; i < gameover::overlaysInUse; ++i)
    {
        _overlays.pop_back();
    }
}
