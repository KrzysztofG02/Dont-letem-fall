#include "Game.h"
#include "RNG.h"

using namespace std;


mt19937 RNG::mt(std::chrono::system_clock::now().time_since_epoch().count());

namespace phase
{
    //Phase
    unsigned short hudsInUse;
    unsigned short timersInUse;

    unsigned short *army;
    unsigned spawnsDuringPhase;
    //Phase/
}


void Game::loadPhase()
{
    phase::hudsInUse = 0;
    phase::timersInUse = 0;

    phase::spawnsDuringPhase = 0;
    _timers_us.push_back(chrono::microseconds(0));
    ++phase::timersInUse;

    _huds.push_back(sf::Text("Enemies Passes: " + to_string(_enemiesPasses) + '/' + to_string(_levels[_currLevelIdx].getEnemiesPasses()), _font, calcPercentageOfY(3)));
    ++phase::hudsInUse;
    _huds.back().setPosition((_window->getSize().x - _huds.back().getGlobalBounds().width) / 2, _huds[_huds.size() - 2].getGlobalBounds().height + calcPercentageOfY(1));
    _huds.back().setColor(sf::Color(144, 238, 144));

    _huds.push_back(sf::Text("Phase: " + to_string(_currPhaseIdx + 1), _font, this->calcPercentageOfX(3)));
    ++phase::hudsInUse;
    sf::FloatRect const &GB = _huds[_huds.size() - 2].getGlobalBounds();
    _huds.back().setPosition((_window->getSize().x - _huds.back().getGlobalBounds().width) / 2, GB.top + GB.height + calcPercentageOfY(1));

    this->setEnemiesPassesHUD();
    this->prepareObjects();

    phasePhasis = PhasePhasis::ongoing;
}

void Game::runPhase()
{
    this->updateEnemies();
}

void Game::quitPhase()
{
    this->clearPhase();

    if(++_currPhaseIdx < _levels[_currLevelIdx].getPhaseNumber())
    {
        phasePhasis = PhasePhasis::loading;
    }
    else
    {
        _levelPhasis = LevelPhasis::quitting;
    }
}

void Game::clearPhase()
{
    delete[] phase::army;
    phase::army = nullptr;

    for(unsigned short i = 0; i < phase::hudsInUse; ++i)
    {
        _huds.pop_back();
    }

    for(unsigned short i = 0; i < phase::timersInUse; ++i)
    {
        _timers_us.pop_back();
    }

    _enemies.clear();
}


void Game::setEnemiesPassesHUD()
{
    if(_enemiesPasses == _levels[_currLevelIdx].getEnemiesPasses())
    {
        _huds[_huds.size() - 2].setColor(sf::Color::Magenta);
    }
    else if(_enemiesPasses > 6)
    {
        _huds[_huds.size() - 2].setColor(sf::Color::Red);
    }
    else if(_enemiesPasses > 3)
    {
        _huds[_huds.size() - 2].setColor(sf::Color(255, 165, 0));
    }
    else if(_enemiesPasses > 0)
    {
        _huds[_huds.size() - 2].setColor(sf::Color::Yellow);
    }

    _huds[_huds.size() - 2].setString("Enemies Passes: "
                                      + to_string(_enemiesPasses) + '/'
                                      + to_string(_levels[_currLevelIdx].getEnemiesPasses()));
    _huds[_huds.size() - 2].setPosition((_window->getSize().x - _huds[_huds.size() - 2].getGlobalBounds().width) / 2,
                                        _huds[_huds.size() - 2].getPosition().y);
}



void Game::prepareObjects()
{
    vector<unsigned short> const &cumulativeProb = _levels[_currLevelIdx].getPhase(_currPhaseIdx).getSpawnEnemyCumulativeProb();
    pair<unsigned short, float> fractionalParts[cumulativeProb.size()];
    phase::army = new unsigned short[_levels[_currLevelIdx].getPhase(_currPhaseIdx).getTotalEnemyCount()];
    unsigned short enemyIdx = 0;

    for(unsigned short i = 0; i < cumulativeProb.size(); ++i)
    {
        fractionalParts[i].first = i;
        fractionalParts[i].second = static_cast<float>(_levels[_currLevelIdx].getPhase(_currPhaseIdx).getTotalEnemyCount() * cumulativeProb[i]) / 100.f;
        unsigned short j = static_cast<unsigned short>(fractionalParts[i].second);
        fractionalParts[i].second -= static_cast<float>(j);

        unsigned short const lastIdx = enemyIdx + j;
        for(; enemyIdx < lastIdx; ++enemyIdx)
        {
            phase::army[enemyIdx] = i;
        }
    }

    sort(fractionalParts, fractionalParts + cumulativeProb.size(),
         [](pair<unsigned short, float> const &a, pair<unsigned short, float> const &b) {return a.second > b.second;});

    for(unsigned short i = 0; enemyIdx < _levels[_currLevelIdx].getPhase(_currPhaseIdx).getTotalEnemyCount(); ++i, ++enemyIdx)
    {
        phase::army[enemyIdx] = fractionalParts[i].first;
    }

    shuffle(phase::army, phase::army + _levels[_currLevelIdx].getPhase(_currPhaseIdx).getTotalEnemyCount(), RNG::mt);
}


void Game::updateEnemies()
{
    auto enemy = _enemies.begin();

    while(enemy != _enemies.end())
    {
        if(this->checkEnemyCollisions(enemy))
        {
            continue;
        }

        (enemy++)->moveYWithTheSetVelocity(_elapsedIter_us.count() * _levels[_currLevelIdx].getPhase(_currPhaseIdx).getYSpeedPerSecMultiplier());
    }


    if(phase::spawnsDuringPhase >= _levels[_currLevelIdx].getPhase(_currPhaseIdx).getTotalEnemyCount())
    {
        if(_enemies.size() == 0)
        {
            _timers_us[0] += _elapsedIter_us;

            if(chrono::duration_cast<chrono::seconds>(_timers_us[0]) >= _levels[_currLevelIdx].getCooldownBetweenPhases())
            {
                phasePhasis = PhasePhasis::quitting;
            }

            return;
        }
    }
    else
    {
        this->enemySpawner();
    }
}

void Game::enemySpawner()
{
    _timers_us[0] += _elapsedIter_us;

    if(chrono::duration_cast<chrono::milliseconds>(_timers_us[0]) >= _levels[_currLevelIdx].getPhase(_currPhaseIdx).getEnemySpawnCooldown())
    {
        _timers_us[0] = chrono::microseconds(0);

        if(_enemies.size() < _levels[_currLevelIdx].getPhase(_currPhaseIdx).getMaxAliveEnemies())
        {
            _enemies.push_back(_modelEnemyTypesArray[phase::army[phase::spawnsDuringPhase++]]);
            _enemies.back().setPosition(
                sf::Vector2f(RNG::getRandomFrom0(static_cast<int>(_window->getSize().x - _enemies.back().getWidth())), 0));
        }
    }
}

bool Game::checkEnemyCollisions(std::list<Enemy>::iterator &enemy)
{
    if(   this->checkEnemyCollisionWithBorder(enemy)
       || this->checkEnemyCollisionWithPlayers(enemy)
       || this->checkEnemyCollisionWithBullets(enemy))
    {
        return true;
    }

    return false;
}

bool Game::checkEnemyCollisionWithBorder(std::list<Enemy>::iterator &enemy)
{
    auto const &enemyRectangle = enemy->getForm().getGlobalBounds();

    if(enemyRectangle.top + enemyRectangle.height > _window->getSize().y)
    {
        this->killEnemyByBorder(enemy);

        return true;
    }

    return false;
}

bool Game::checkEnemyCollisionWithPlayers(std::list<Enemy>::iterator &enemy)
{
    for(auto &player : _players)
    {
        if(checkEnemyCollisionWithPlayer(enemy, player))
        {
            this->killEnemyByPlayer(enemy, &player);

            return true;
        }
    }

    return false;
}

bool Game::checkEnemyCollisionWithPlayer(std::list<Enemy>::iterator &enemy, Player const &player)
{
    sf::FloatRect const &playerBounds = player.getGlobalBounds();
    sf::FloatRect intersection;

    if(playerBounds.intersects(enemy->getForm().getGlobalBounds(), intersection))
    {
        sf::Image const &playerImg = player.getTexture().copyToImage();
        auto const &scale = player.getScale();

        unsigned X[2] = {
            static_cast<unsigned>((static_cast<unsigned>(intersection.left) - static_cast<unsigned>(playerBounds.left)) / scale.x),
            static_cast<unsigned>((static_cast<unsigned>(intersection.left) + static_cast<unsigned>(intersection.width) - static_cast<unsigned>(playerBounds.left)) / scale.x)};

        unsigned Y[2] = {
            static_cast<unsigned>((static_cast<unsigned>(intersection.top) - static_cast<unsigned>(playerBounds.top)) / scale.y),
            static_cast<unsigned>((static_cast<unsigned>(intersection.top) + static_cast<unsigned>(intersection.height) - static_cast<unsigned>(playerBounds.top)) / scale.y)};

        for(auto const &y : Y)
        {
            for(unsigned x = X[0]; x <= X[1]; ++x)
            {
                if(playerImg.getPixel(x, y).a > 0)
                {
                    return true;
                }
            }
        }

        for(auto const &x : X)
        {
            for(unsigned y = Y[0] + 1; y < Y[1]; ++y)
            {
                if(playerImg.getPixel(x, y).a > 0)
                {
                    return true;
                }
            }
        }
    }

    return false;
}

bool Game::checkEnemyCollisionWithBullets(std::list<Enemy>::iterator &enemy)
{
    auto bullet = _bullets.begin();

    while(bullet != _bullets.end())
    {
        if(checkEnemyCollisionWithBullet(enemy, *bullet))
        {
            this->killEnemyByBullet(enemy, *bullet);
            this->destroyBullet(bullet);

            return true;
        }

        ++bullet;
    }

    return false;
}

bool Game::checkEnemyCollisionWithBullet(std::list<Enemy>::iterator &enemy, Bullet const &bullet)
{
    return enemy->getForm().getGlobalBounds().intersects(bullet.getForm().getGlobalBounds());
}


void Game::killEnemyByBorder(std::list<Enemy>::iterator &enemy)
{
    ++_enemiesPasses;
    this->setEnemiesPassesHUD();
    _enemies.erase(enemy++);
}

void Game::killEnemyByBullet(std::list<Enemy>::iterator &enemy, Bullet const &bullet)
{
    bullet.getShooter()->addPoints(static_cast<int>(enemy->getPrizeAmount() * _levels[_currLevelIdx].getPhase(_currPhaseIdx).getPrizeMultiplier()));
    _enemies.erase(enemy++);
}

void Game::killEnemyByPlayer(std::list<Enemy>::iterator &enemy, Player *player)
{
    player->subtractHealthPoints(static_cast<int>(enemy->getPenaltyAmount() * _levels[_currLevelIdx].getPhase(_currPhaseIdx).getPenaltyMultiplier()));
    _enemies.erase(enemy++);
}
