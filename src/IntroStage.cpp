#include "Game.h"

#include <chrono>
using namespace std;

namespace intro
{
    unsigned short constexpr static introDuration_s = 7;
    string const *authorNameAnimation;
    unsigned short gameNameText_alpaChannel;
    unsigned short authorTextLength;
    chrono::microseconds constexpr static fadeTransitionTime = chrono::microseconds(10000); //10 ms
    chrono::microseconds constexpr static letterTransitionTime = chrono::microseconds(120000); //120 ms

    unsigned short timersInUse;
    unsigned short textsInUse;
}


void Game::loadIntro()
{
    _backgroundColor = sf::Color::Black;

    intro::timersInUse = 0;
    intro::textsInUse = 0;

    intro::gameNameText_alpaChannel = 0;
    intro::authorTextLength = 0;

    _window->setMouseCursorVisible(false);

    _texts.push_back(sf::Text());
    ++intro::textsInUse;
    _texts[0].setFont(_font);
    _texts[0].setCharacterSize(calcPercentageOfY(18));
    _texts[0].setFillColor(sf::Color(255, 255, 255, 0));
    _texts[0].setString(_gameTitle);

    sf::FloatRect gameGB = _texts[0].getGlobalBounds();
    _texts[0].setOrigin(gameGB.width / 2, gameGB.height / 2);
    _texts[0].setPosition(_window->getSize().x / 2, gameGB.height / 2 + calcPercentageOfY(30));

    intro::authorNameAnimation = new string("by Christopher Gander");

    _texts.push_back(sf::Text());
    ++intro::textsInUse;
    _texts[1].setFont(_font);
    _texts[1].setCharacterSize(calcPercentageOfY(5));
    _texts[1].setString(*intro::authorNameAnimation);
    _texts[1].setOrigin(_texts[1].getGlobalBounds().width / 2, _texts[1].getGlobalBounds().height / 2);
    _texts[1].setPosition(_window->getSize().x / 2, _texts[0].getPosition().y + _texts[0].getGlobalBounds().height + calcPercentageOfY(8));
    _texts[1].setFillColor(sf::Color::White);
    _texts[1].setString("");


    _stagePhasis = StagePhasis::ongoing;

    _timers_us.push_back(chrono::microseconds(0));
    _timers_us.push_back(chrono::microseconds(0));
    intro::timersInUse += 2;
}

void Game::runIntro()
{
    _timers_us[0] += _elapsedIter_us;

    if(chrono::duration_cast<chrono::seconds>(_timers_us[0]).count() >= intro::introDuration_s)
    {
        _timers_us[0] = chrono::microseconds(0);
        _timers_us[1] = chrono::microseconds(0);

        _stagePhasis = StagePhasis::quitting;

        return;
    }

    if(intro::gameNameText_alpaChannel < 255)
    {
        _timers_us[1] += _elapsedIter_us;

        if(_timers_us[1] >= intro::fadeTransitionTime)
        {
            unsigned long integerPart = static_cast<unsigned long>(_timers_us[1] / intro::fadeTransitionTime);

            if((intro::gameNameText_alpaChannel += integerPart) > 255)
            {
                intro::gameNameText_alpaChannel = 255;
                _timers_us[1] = chrono::microseconds(0);
            }
            else
            {
                _timers_us[1] -= integerPart * intro::fadeTransitionTime;
            }

            _texts[0].setFillColor(sf::Color(255, 255, 255, intro::gameNameText_alpaChannel));
        }
    }
    else if(intro::authorTextLength < intro::authorNameAnimation->size())
    {
        _timers_us[1] += _elapsedIter_us;

        if(_timers_us[1] >= intro::letterTransitionTime)
        {
            unsigned long integerPart = static_cast<unsigned long>(_timers_us[1] / intro::letterTransitionTime);

            if((intro::authorTextLength += integerPart) > intro::authorNameAnimation->size())
            {
                intro::authorTextLength = intro::authorNameAnimation->size();
            }

            string text = intro::authorNameAnimation->substr(0, intro::authorTextLength);

            if(text.back() == ' ')
            {
                text = intro::authorNameAnimation->substr(0, ++intro::authorTextLength);
            }

            _texts[1].setString(text);

            _timers_us[1] -= integerPart * intro::letterTransitionTime;
        }
    }

}

void Game::quitIntro()
{
    this->clearIntro();

    _gameStage = GameStage::menu;
    _stagePhasis = StagePhasis::loading;
    _backgroundMusic.play();
}

void Game::clearIntro()
{
    delete intro::authorNameAnimation;
    intro::authorNameAnimation = nullptr;

    for(unsigned short i = 0; i < intro::timersInUse; ++i)
    {
        _timers_us.pop_back();
    }

    for(unsigned short i = 0; i < intro::textsInUse; ++i)
    {
        _texts.pop_back();
    }
}

