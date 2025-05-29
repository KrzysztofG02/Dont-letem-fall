#include "Phase.h"

#include <algorithm>
#include <iostream>


Phase::Phase(unsigned short const &enemyTypesNumber,
    std::chrono::milliseconds const &enemySpawnCooldown_ms,
    unsigned const &totalEnemyCount,
    unsigned const &maxAliveEnemies,
    std::vector<unsigned short> const &spawnEnemyCumulativeProb,
    float const &xSpeedPerSecMultiplier,
    float const &ySpeedPerSecMultiplier,
    float const &prizeMultiplier,
    float const &penaltyMultiplier):
        _enemyTypesNumber(enemyTypesNumber),
        _enemySpawnCooldown_ms(enemySpawnCooldown_ms),
        _totalEnemyCount(totalEnemyCount),
        _maxAliveEnemies(maxAliveEnemies),
        _spawnEnemyCumulativeProb(spawnEnemyCumulativeProb),
        _xSpeedPerSecMultiplier(xSpeedPerSecMultiplier),
        _ySpeedPerSecMultiplier(ySpeedPerSecMultiplier),
        _prizeMultiplier(prizeMultiplier),
        _penaltyMultiplier(penaltyMultiplier) {}

Phase::~Phase() {}


unsigned short Phase::getEnemyTypesNumber() const
{
    return _enemyTypesNumber;
}

std::chrono::milliseconds Phase::getEnemySpawnCooldown() const
{
    return _enemySpawnCooldown_ms;
}

unsigned Phase::getTotalEnemyCount() const
{
    return _totalEnemyCount;
}

unsigned Phase::getMaxAliveEnemies() const
{
    return _maxAliveEnemies;
}

std::vector<unsigned short> const& Phase::getSpawnEnemyCumulativeProb() const
{
    return _spawnEnemyCumulativeProb;
}

float Phase::getXSpeedPerSecMultiplier() const
{
    return _xSpeedPerSecMultiplier;
}

float Phase::getYSpeedPerSecMultiplier() const
{
    return _ySpeedPerSecMultiplier;
}

float Phase::getPrizeMultiplier() const
{
    return _prizeMultiplier;
}

float Phase::getPenaltyMultiplier() const
{
    return _penaltyMultiplier;
}
