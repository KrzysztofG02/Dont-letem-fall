#include "Game.h"

using namespace std;



namespace tie
{
    //Level
    unsigned short hudsInUse;
    //Level/
}



void Game::loadLevel()
{
    _backgroundColor = sf::Color(5, 3, 41);
    tie::hudsInUse = 0;

    _currPhaseIdx = 0;
    _enemiesPasses = 0;

    this->loadPlayers();
    this->loadHuds();

    _levelPhasis = LevelPhasis::ongoing;
    phasePhasis = PhasePhasis::loading;
}

void Game::loadPlayers()
{
    _players.push_back(Player(0, "textures/spaceship1.bmp", _levels[_currLevelIdx].getStartHealth(), 0, 0,
                              sf::Keyboard::Z, sf::Keyboard::C, sf::Keyboard::Space, sf::Vector2f(),
                              sf::Vector2f(this->calcPercentageOfY(15.f), this->calcPercentageOfY(15.f)),
                              this->calcPercentageOfX(70.f), 0.f));

    _players.back().setPosition(sf::Vector2f(
        _window->getSize().x * 0.25f,
        _window->getSize().y - _players.back().getGlobalBounds().height - calcPercentageOfY(1.f)));

    if(_mode == Mode::multiplayer)
    {
        _players.push_back(Player(1, "textures/spaceship2.bmp", _levels[_currLevelIdx].getStartHealth(), 0, 0,
                                  sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::RControl, sf::Vector2f(),
                                  sf::Vector2f(this->calcPercentageOfY(15.f), this->calcPercentageOfY(15.f)),
                                  this->calcPercentageOfX(70.f), 0.f));

        _players.back().setPosition(sf::Vector2f(
            _window->getSize().x * 0.75f - _players.back().getGlobalBounds().width,
            _window->getSize().y - _players.back().getGlobalBounds().height - calcPercentageOfY(1.f)));
    }
}

void Game::loadHuds()
{
    std::list<Player>::const_iterator playerIt = _players.begin();
    for(unsigned short i = 0; i < _players.size(); ++i, ++playerIt)
    {
        _huds.push_back(sf::Text("Player " + to_string(i + 1)
            + "\nHealth: " + to_string(playerIt->getHealth())
            + "\nPoints: " + to_string(playerIt->getPoints()), _font, calcPercentageOfY(3)));

        ++tie::hudsInUse;
    }

    _huds[0].setPosition(this->calcPercentageOfX(2), 0);

    if(_mode == Mode::multiplayer)
    {
        _huds[1].setPosition(_window->getSize().x - _huds[1].getGlobalBounds().width
                             - this->calcPercentageOfX(2), 0);
    }

    _huds.push_back(sf::Text("Level " + to_string(_currLevelIdx + 1), _font, calcPercentageOfY(3)));
    ++tie::hudsInUse;
    _huds.back().setPosition((_window->getSize().x - _huds.back().getGlobalBounds().width) / 2, 0);
}

void Game::runLevel()
{
    if(_players.empty() || _enemiesPasses >= _levels[_currLevelIdx].getEnemiesPasses())
    {
        _stagePhasis = StagePhasis::gameover;
        _gameoverStage = GameoverStage::loading;
        return;
    }

    if(this->switchPause())
    {
        _levelPhasis = LevelPhasis::paused;
        _pausePhasis = PausePhasis::loading;

        return;
    }

    this->updatePlayers();
    this->updateBullets();

    switch(phasePhasis)
    {
        case PhasePhasis::loading:
            this->loadPhase();
            return;

        case PhasePhasis::ongoing:
            this->runPhase();
            return;

        case PhasePhasis::quitting:
            this->quitPhase();
            return;

        default: return;
    }
}

void Game::pauseLevel()
{
    switch(_pausePhasis)
    {
        case PausePhasis::loading:
            this->loadPause();
            return;

        case PausePhasis::ongoing:
            this->runPause();
            return;

        case PausePhasis::quitting:
            this->quitPause();
            return;

        default: return;
    }
}

void Game::quitLevel()
{
    this->clearLevel();

    if(++_currLevelIdx < _levels.size())
    {
        _levelPhasis = LevelPhasis::loading;
    }
    else
    {
        _stagePhasis = StagePhasis::quitting;
    }
}

void Game::clearLevel()
{
    if(phasePhasis != PhasePhasis::quitting && phasePhasis != PhasePhasis::null)
    {
        this->clearPhase();
    }

    _players.clear();
    _bullets.clear();

    for(unsigned short i = 0; i < tie::hudsInUse; ++i)
    {
        _huds.pop_back();
    }

    tie::hudsInUse = 0;

    _enemiesPasses = 0;
}


void Game::updateBullets()
{
    auto bullet = _bullets.begin();
    while(bullet != _bullets.end())
    {
        auto const &bulletRectangle = bullet->getForm().getGlobalBounds();

        if(bulletRectangle.top + bulletRectangle.height > _window->getSize().y)
        {
            this->destroyBullet(bullet);
        }
        else
        {
            bullet->moveUpWithTheSetVelocity(_elapsedIter_us.count());
            ++bullet;
        }
    }

    for(auto &player : _players)
    {
        if(sf::Keyboard::isKeyPressed(player.getShootButton()))
        {
            if(!player.getShootFlag())
            {
                _bullets.push_back(Bullet(&player, sf::Vector2f(player.getPosition().x
                    + static_cast<float>(player.getGlobalBounds().width) / 2.f
                    - player.getGlobalBounds().width / 12.f,
                    player.getPosition().y),
                    player.getGlobalBounds().width / 12.f));

                _bullets.back().setYSpeedPerSec(this->calcPercentageOfY(75));

                if(player.getId() == 0)
                {
                    _bullets.back().setFillColour(sf::Color(198, 198, 198));
                }
                else
                {
                    _bullets.back().setFillColour(sf::Color(154, 0, 243));
                }
            }

            player.setShootFlag();
        }
        else
        {
            player.clearShootFlag();
        }
    }
}

void Game::destroyBullet(std::list<Bullet>::iterator &bullet)
{
    _bullets.erase(bullet++);
}


void Game::updatePlayers()
{
    for(list<Player>::iterator it = _players.begin(); it != _players.end();)
    {
        _huds[it->getId()].setString("Player " + to_string(it->getId() + 1)
           + "\nHealth: " + to_string(it->getHealth())
           + "\nPoints: " + to_string(it->getPoints()));

        if(it->getHealth() == 0)
        {
            _huds[it->getId()].setColor(sf::Color(166, 166, 166));
            _players.erase(it++);
        }
        else
        {
            this->updatePlayerMove(it);
            ++it;
        }
    }
}

void Game::updatePlayerMove(std::list<Player>::iterator &player)
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
}
