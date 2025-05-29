#include "Level.h"

#include <algorithm>
#include <iostream>

Level::Level(unsigned short startHealth,
             std::chrono::seconds cooldownBetweenPhases_s,
             unsigned short enemiesPasses):
    _startHealth(startHealth),
    _cooldownBetweenPhases_s(cooldownBetweenPhases_s),
    _enemiesPasses(enemiesPasses) {}

Level::~Level() {}


unsigned short Level::getStartHealth() const
{
    return _startHealth;
}

std::chrono::seconds Level::getCooldownBetweenPhases() const
{
    return _cooldownBetweenPhases_s;
}

unsigned short Level::getEnemiesPasses() const
{
    return _enemiesPasses;
}

unsigned short Level::getPhaseNumber() const
{
    return _phases.size();
}

Phase const& Level::getPhase(unsigned short const &index) const
{
    return _phases[index];
}


void Level::setStartHealth(unsigned short const &startHealth)
{
    _startHealth = startHealth;
}

void Level::setCooldownBetweenPhases_s(std::chrono::seconds const &cooldownBetweenPhases_s)
{
    _cooldownBetweenPhases_s = cooldownBetweenPhases_s;
}

void Level::addPhase(Phase const &phase)
{
    _phases.push_back(phase);
}

void Level::setEnemiesPasses(unsigned short &enemiesPasses)
{
    _enemiesPasses = enemiesPasses;
}

void Level::removePhase(unsigned short const &index)
{
    _phases.erase(_phases.begin() + index);
}
