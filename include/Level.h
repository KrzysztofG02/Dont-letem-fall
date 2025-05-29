#ifndef LEVEL_H
#define LEVEL_H

#include "Phase.h"

#include <chrono>
#include <vector>


class Level
{
private:
    unsigned short _startHealth;
    std::chrono::seconds _cooldownBetweenPhases_s;

    unsigned short _enemiesPasses;

    std::vector<Phase> _phases;


public:
    Level(unsigned short startHealth = 100,
          std::chrono::seconds cooldownBetweenPhases_s = std::chrono::seconds(5),
          unsigned short enemiesPasses = 0);
    ~Level();

    unsigned short getStartHealth() const;
    std::chrono::seconds getCooldownBetweenPhases() const;
    unsigned short getEnemiesPasses() const;
    unsigned short getPhaseNumber() const;
    Phase const& getPhase(unsigned short const &index) const;

    void setStartHealth(unsigned short const &startHealth);
    void setCooldownBetweenPhases_s(std::chrono::seconds const &cooldownBetweenPhases_s);
    void setEnemiesPasses(unsigned short &enemiesPasses);
    void addPhase(Phase const &phase);
    void removePhase(unsigned short const &index);
};

#endif // LEVEL_H
