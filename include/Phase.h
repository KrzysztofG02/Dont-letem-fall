#ifndef PHASE_H
#define PHASE_H

#include <chrono>
#include <vector>


class Phase
{
private:
    unsigned short _enemyTypesNumber;
    std::chrono::milliseconds _enemySpawnCooldown_ms;
    unsigned _totalEnemyCount;
    unsigned _maxAliveEnemies;
    std::vector<unsigned short> _spawnEnemyCumulativeProb;

    float _xSpeedPerSecMultiplier;
    float _ySpeedPerSecMultiplier;
    float _prizeMultiplier;
    float _penaltyMultiplier;


public:
    Phase(unsigned short const &enemyTypesNumber = 1,
          std::chrono::milliseconds const &enemySpawnCooldown_ms = std::chrono::milliseconds(500),
          unsigned const &totalEnemyCount = 50,
          unsigned const &maxAliveEnemies = 10,
          std::vector<unsigned short> const &spawnEnemyCumulativeProb = {50, 80, 100},
          float const &xSpeedPerSecMultiplier = 1.f,
          float const &ySpeedPerSecMultiplier = 1.f,
          float const &prizeMultiplier = 1.f,
          float const &penaltyMultiplier = 1.f);
    ~Phase();

    unsigned short getEnemyTypesNumber() const;
    std::chrono::milliseconds getEnemySpawnCooldown() const;
    unsigned getTotalEnemyCount() const;
    unsigned getMaxAliveEnemies() const;
    std::vector<unsigned short> const& getSpawnEnemyCumulativeProb() const;
    float getXSpeedPerSecMultiplier() const;
    float getYSpeedPerSecMultiplier() const;
    float getPrizeMultiplier() const;
    float getPenaltyMultiplier() const;
};

#endif // PHASE_H
