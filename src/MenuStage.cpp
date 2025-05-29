#include "Game.h"

using namespace std;


namespace menu
{
    std::array<char const*, 4> constexpr optionStrings = {"PLAY SOLO", "PLAY DUO", "MUSIC ", "EXIT"};

    enum class MenuChoice: char
    {
        play,
        exit,
        null
    };
    MenuChoice menuChoice = MenuChoice::null;

    unsigned short timersInUse;
    unsigned short textsInUse;
}


void Game::loadMenu()
{
    menu::timersInUse = 0;
    menu::textsInUse = 0;

    _backgroundColor = sf::Color::Black;

    _previousHoveredOption = 0;
    _hoveredOption = 0;
    _recentlyPressedKey = sf::Keyboard::Return;

    _texts.push_back(sf::Text());
    ++menu::textsInUse;
    _texts[0].setString(_gameTitle);
    _texts[0].setFont(_font);
    _texts[0].setCharacterSize(calcPercentageOfY(10));
    _texts[0].setFillColor(sf::Color::White);
    _texts[0].setStyle(sf::Text::Bold);
    _texts[0].setPosition(_window->getSize().x / 2 - _texts[0].getGlobalBounds().width / 2, calcPercentageOfY(10));

    for(unsigned i = 0; i < menu::optionStrings.size(); ++i)
    {
        _texts.push_back(sf::Text());
        ++menu::textsInUse;
        _texts.back().setFont(_font);

        if(i == 2)
        {
            std::string str(menu::optionStrings[i]);
            str += this->isMusicPlaying() ? "OFF" : "ON";
            _texts.back().setString(str);
        }
        else
        {
            _texts.back().setString(menu::optionStrings[i]);
        }

        _texts.back().setCharacterSize(calcPercentageOfY(5));
        _texts.back().setFillColor(sf::Color::White);
        _texts.back().setPosition(_window->getSize().x / 2 - _texts.back().getGlobalBounds().width / 2,
                                  calcPercentageOfY(30 + i * 15));
    }

    _texts[1].setFillColor(sf::Color::Yellow);


    _stagePhasis = StagePhasis::ongoing;

    _timers_us.push_back(chrono::microseconds(0));
    _timers_us.push_back(chrono::microseconds(0));
    menu::timersInUse += 2;
}

void Game::runMenu()
{
    _timers_us[0] += _elapsedIter_us;
    _timers_us[1] += _elapsedIter_us;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
    {
        if(_recentlyPressedKey != sf::Keyboard::Return)
        {
            _recentlyPressedKey = sf::Keyboard::Return;

            switch(_hoveredOption)
            {
                case 0:
                    _stagePhasis = StagePhasis::quitting;
                    menu::menuChoice = menu::MenuChoice::play;
                    _mode = Mode::singleplayer;
                    return;

                case 1:
                    _stagePhasis = StagePhasis::quitting;
                    menu::menuChoice = menu::MenuChoice::play;
                    _mode = Mode::multiplayer;
                    return;

                case 2:
                    if(this->switchMusic())
                    {
                        _texts[3].setString("MUSIC OFF");
                    }
                    else
                    {
                        _texts[3].setString("MUSIC ON");
                    }

                    _texts[3].setPosition(_window->getSize().x / 2 - _texts[2].getGlobalBounds().width / 2,
                                          calcPercentageOfY(60));
                    return;

                case 3:
                    _stagePhasis = StagePhasis::quitting;
                    menu::menuChoice = menu::MenuChoice::exit;
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
            short const &&n = (i == 0 ? 1 : -1);

            if(_keys[i] == _recentlyPressedKey)
            {
                if(   _timers_us[0] > chrono::microseconds(200000)
                   && _timers_us[1] > chrono::microseconds(100000))
                {
                    _timers_us[1] = chrono::microseconds(0);

                    _previousHoveredOption = _hoveredOption;
                    _hoveredOption = (_hoveredOption + n) % menu::optionStrings.size();

                    _texts[_previousHoveredOption + 1].setFillColor(sf::Color::White);
                    _texts[_hoveredOption + 1].setFillColor(sf::Color::Yellow);
                }
            }
            else
            {
                _timers_us[0] = chrono::microseconds(0);
                _timers_us[1] = chrono::microseconds(0);
                _recentlyPressedKey = _keys[i];

                _previousHoveredOption = _hoveredOption;
                _hoveredOption = (_hoveredOption + n) % menu::optionStrings.size();

                _texts[_previousHoveredOption + 1].setFillColor(sf::Color::White);
                _texts[_hoveredOption + 1].setFillColor(sf::Color::Yellow);
            }

            return;
        }
    }

    _recentlyPressedKey = sf::Keyboard::Unknown;
}

void Game::quitMenu()
{
    switch(menu::menuChoice)
    {
        case menu::MenuChoice::play:
            this->clearMenu();

            _gameStage = GameStage::tie;
            _stagePhasis = StagePhasis::loading;
            return;

        case menu::MenuChoice::exit:
            _window->close();
            return;

        default: return;
    }
}


void Game::clearMenu()
{
    _previousHoveredOption = 0;
    _hoveredOption = 0;
    _recentlyPressedKey = sf::Keyboard::Unknown;

    for(unsigned i = 0; i < menu::timersInUse; ++i)
    {
        _timers_us.pop_back();
    }

    for(unsigned i = 0; i < menu::textsInUse; ++i)
    {
        _texts.pop_back();
    }
}
