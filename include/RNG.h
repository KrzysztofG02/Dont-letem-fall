#ifndef RNG_H
#define RNG_H


#include <random>
#include <chrono>
#include <algorithm>


class RNG
{
public:
    static std::mt19937 mt;

public:
    static unsigned short getRandomFrom1To100()
    {
        std::uniform_int_distribution<unsigned short> dist(1, 100);
        return dist(mt);
    }

    static unsigned getRandomFrom0(unsigned const &max)
    {
        std::uniform_int_distribution<unsigned> dist(0, max);
        return dist(mt);
    }

    static int getRandom(int const &min, int const &max)
    {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(mt);
    }
};

#endif // RNG_H
