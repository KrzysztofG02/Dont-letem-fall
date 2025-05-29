#ifndef ENEMY_H
#define ENEMY_H


#include <cstdint>

#include <SFML/Graphics/RectangleShape.hpp>


class Enemy
{
private:
    unsigned _id;

    sf::RectangleShape _form;

    float _xSpeedPerSec;
    float _ySpeedPerSec;

    float _xDefMoveUnit;
    float _yDefMoveUnit;

    unsigned long _prizeAmount;
    unsigned long _penaltyAmount;


public:
    Enemy(unsigned const &id = 0, sf::Vector2f const &position = sf::Vector2f(),
          sf::Vector2f const &size = sf::Vector2f(100, 100), float const &outlineThickness = 1.f,
          sf::Vector2f const &scale = sf::Vector2f(1.f, 1.f),
          sf::Color const &fillColour = sf::Color(255, 255, 255, 255),
          sf::Color const &outlineColour = sf::Color(0, 0, 0, 255),
          float const &xSpeedPerSec = 0.f, float const &ySpeedPerSec = 100.f,
          float const &xDefMoveUnit = 1.f, float const &yDefMoveUnit = 1.f,
          unsigned long const &prizeAmount = 1, unsigned long const &penaltyAmount = 1);
    ~Enemy();


    void setID(unsigned const id);

    unsigned getID() const;


    sf::RectangleShape getForm() const;


    void setPosition(sf::Vector2f const position);
    void setXPosition(float const x);
    void setYPosition(float const y);

    sf::Vector2f getPosition() const;
    float getBottomPosition() const;
    float getRightPosition() const;


    void setSize(sf::Vector2f const size);
    void setXSize(float const x);
    void setYSize(float const y);

    sf::Vector2f getSize() const;


    void setOutlineThickness(float const t);

    float getOutlineThickness() const;


    void setScale(sf::Vector2f const scale);
    void setXScale(float const x);
    void setYScale(float const y);

    sf::Vector2f getScale() const;


    float getHeight() const;
    float getWidth() const;


    void setFillColour(sf::Color const colour);

    sf::Color getFillColour() const;


    void setOutlineColour(sf::Color const colour);

    sf::Color getOutlineColour() const;


    void setFillOpacity(uint8_t const a);
    void setOutlineOpacity(uint8_t const a);


    void setXSpeedPerSec(float const x);
    void setYSpeedPerSec(float const y);

    float getXSpeexPerSec() const;
    float getYSpeexPerSec() const;


    void setXDefMoveUnit(float const x);
    void setYDefMoveUnit(float const y);

    float getXDefMoveUnit() const;
    float getYDefMoveUnit() const;


    void move();
    void move(float const x , float const y);

    void moveWithTheSetVelocity(unsigned long const elapsedUs);
    void moveXWithTheSetVelocity(unsigned long const elapsedUs);
    void moveYWithTheSetVelocity(unsigned long const elapsedUs);

    void moveX();
    void moveX(float const x);

    void moveY();
    void moveY(float const y);


    bool contains(sf::Vector2f const viewPosition);


    void setPrizeAmount(unsigned long const prizeAmount);

    unsigned long getPrizeAmount() const;


    void setPenaltyAmount(unsigned long const penaltyAmount);

    unsigned long getPenaltyAmount() const;
};


#endif // ENEMY_H

