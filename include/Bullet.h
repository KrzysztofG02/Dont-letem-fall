#ifndef BULLET_H
#define BULLET_H

#include "Player.h"

#include <SFML/Graphics/CircleShape.hpp>


class Bullet
{
private:
    sf::CircleShape _form;

    Player *_shooter;

    float _xSpeedPerSec;
    float _ySpeedPerSec;


public:
    Bullet(Player *shooter = nullptr,
           sf::Vector2f const &position = sf::Vector2f(),
           float const &radius = 10.f, float const &outlineThickness = 1.f,
           sf::Vector2f const &scale = sf::Vector2f(1.f, 1.f),
           sf::Color const &fillColour = sf::Color(255, 255, 255, 255),
           sf::Color const &outlineColour = sf::Color(0, 0, 0, 255),
           float const &xSpeedPerSec = 0.f, float const &ySpeedPerSec = 1000.f);
    ~Bullet();



    sf::CircleShape getForm() const;

    Player* getShooter() const;
    void setShooter(Player* const shooter);


    void setPosition(sf::Vector2f const &position);
    void setXPosition(float const &x);
    void setYPosition(float const &y);

    sf::Vector2f getPosition() const;
    float getBottomPosition() const;
    float getRightPosition() const;


    void setRadius(float const &radius);

    float getRadius() const;


    void setOutlineThickness(float const &t);

    float getOutlineThickness() const;


    void setScale(sf::Vector2f const &scale);
    void setXScale(float const &x);
    void setYScale(float const &y);

    sf::Vector2f getScale() const;


    float getHeight() const;
    float getWidth() const;


    void setFillColour(sf::Color const &colour);

    sf::Color getFillColour() const;


    void setOutlineColour(sf::Color const &colour);

    sf::Color getOutlineColour() const;


    void setFillOpacity(unsigned short const &a);
    void setOutlineOpacity(unsigned short const &a);


    void setXSpeedPerSec(float const &x);
    void setYSpeedPerSec(float const &y);

    float getXSpeexPerSec() const;
    float getYSpeexPerSec() const;

    void moveUpWithTheSetVelocity(unsigned long const &elapsedUs);

    bool contains(sf::Vector2f const &viewPosition);
};

#endif // BULLET_H
