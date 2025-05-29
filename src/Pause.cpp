#include "Game.h"

using namespace std;


namespace pause
{
    std::array<char const*, 3> constexpr optionStrings = {"RESUME", "MUSIC ", "QUIT"};

    enum class MenuChoice: char
    {
        resume,
        quit,
        null
    };
    MenuChoice menuChoice = MenuChoice::null;

    unsigned short timersInUse;
    unsigned short overlaysInUse;
    unsigned short textsInUse;

    bool escFlag = false;
}



bool Game::switchPause()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        if(!pause::escFlag)
        {
            pause::escFlag = true;

            return true;
        }

        pause::escFlag = true;
    }
    else
    {
        pause::escFlag = false;
    }

    return false;
}

void Game::loadPause()
{
    pause::timersInUse = 0;
    pause::overlaysInUse = 0;
    pause::textsInUse = 0;

    _overlays.push_back(sf::RectangleShape(sf::Vector2f(_window->getSize().x, _window->getSize().y)));
    ++pause::overlaysInUse;
    _overlays.back().setFillColor(sf::Color(0, 0, 0, 170));

    for(unsigned i = 0; i < pause::optionStrings.size(); ++i)
    {
        _texts.push_back(sf::Text());
        ++pause::textsInUse;
        _texts.back().setFont(_font);

        if(i == 1)
        {
            std::string str(pause::optionStrings[i]);
            str += this->isMusicPlaying() ? "OFF" : "ON";
            _texts.back().setString(str);
        }
        else
        {
            _texts.back().setString(pause::optionStrings[i]);
        }

        _texts.back().setCharacterSize(calcPercentageOfY(5));
        _texts.back().setFillColor(sf::Color::White);
        _texts.back().setPosition(_window->getSize().x / 2 - _texts.back().getGlobalBounds().width / 2,
                                  calcPercentageOfY(30 + i * 15));
    }

    _texts[0].setFillColor(sf::Color::Yellow);

    _previousHoveredOption = 0;
    _hoveredOption = 0;
    _recentlyPressedKey = sf::Keyboard::Return;

    _timers_us.push_back(chrono::microseconds(0));
    _timers_us.push_back(chrono::microseconds(0));
    pause::timersInUse += 2;

    _pausePhasis = PausePhasis::ongoing;
}

void Game::runPause()
{
    _timers_us[0] += _elapsedIter_us;
    _timers_us[1] += _elapsedIter_us;

    if(this->switchPause())
    {
        _pausePhasis = PausePhasis::quitting;
        pause::menuChoice = pause::MenuChoice::resume;

        return;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
    {
        if(_recentlyPressedKey != sf::Keyboard::Return)
        {
            _recentlyPressedKey = sf::Keyboard::Return;

            switch(_hoveredOption)
            {
                case 0:
                    _pausePhasis = PausePhasis::quitting;
                    pause::menuChoice = pause::MenuChoice::resume;
                    return;

                case 1:
                    if(this->switchMusic())
                    {
                        _texts[1].setString("MUSIC OFF");
                    }
                    else
                    {
                        _texts[1].setString("MUSIC ON");
                    }

                    _texts[1].setPosition(_window->getSize().x / 2 - _texts[1].getGlobalBounds().width / 2,
                                          calcPercentageOfY(45));
                    return;

                case 2:
                    _pausePhasis = PausePhasis::quitting;
                    pause::menuChoice = pause::MenuChoice::quit;
                    return;

                default: return;
            }
        }

        return;
    }

    for(unsigned short i = 0; i < _numberOfKeys; ++i)
    {
        if(sf::Keyboard::isKeyPressed(_keys[i]))
        {
            if(_keys[i] == _recentlyPressedKey)
            {
                if(   _timers_us[0] > chrono::microseconds(200000)
                   && _timers_us[1] > chrono::microseconds(100000))
                {
                    _timers_us[1] = chrono::microseconds(0);

                    _previousHoveredOption = _hoveredOption;
                    _hoveredOption = (_hoveredOption + i + 1) % 3;

                    _texts[_previousHoveredOption].setFillColor(sf::Color::White);
                    _texts[_hoveredOption].setFillColor(sf::Color::Yellow);
                }
            }
            else
            {
                _timers_us[0] = chrono::microseconds(0);
                _timers_us[1] = chrono::microseconds(0);
                _recentlyPressedKey = _keys[i];

                _previousHoveredOption = _hoveredOption;
                _hoveredOption = (_hoveredOption + i + 1) % 3;

                _texts[_previousHoveredOption].setFillColor(sf::Color::White);
                _texts[_hoveredOption].setFillColor(sf::Color::Yellow);
            }

            return;
        }
    }

    _recentlyPressedKey = sf::Keyboard::Unknown;
}

void Game::quitPause()
{
    this->clearPause();

    switch(pause::menuChoice)
    {
        case pause::MenuChoice::resume:
            _levelPhasis = LevelPhasis::ongoing;
            return;

        case pause::MenuChoice::quit:
            _stagePhasis = StagePhasis::quitting;
            return;

        default: return;
    }
}

void Game::clearPause()
{
    for(unsigned i = 0; i < pause::timersInUse; ++i)
    {
        _timers_us.pop_back();
    }

    for(unsigned i = 0; i < pause::textsInUse; ++i)
    {
        _texts.pop_back();
    }

    for(unsigned i = 0; i < pause::overlaysInUse; ++i)
    {
        _overlays.pop_back();
    }
}
