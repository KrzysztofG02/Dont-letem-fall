#include "Bullet.h"


Bullet::Bullet(Player *shooter, sf::Vector2f const &position,
    float const &radius, float const &outlineThickness,
    sf::Vector2f const &scale, sf::Color const &fillColour,
    sf::Color const &outlineColour, float const &xSpeedPerSec,
    float const &ySpeedPerSec):
        _shooter(shooter)
{
    _form.setPosition(position);
    _form.setRadius(radius);
    _form.setOutlineThickness(outlineThickness);
    _form.setScale(scale);
    _form.setFillColor(fillColour);
    _form.setOutlineColor(outlineColour);

    _xSpeedPerSec = xSpeedPerSec;
    _ySpeedPerSec = ySpeedPerSec;
}

Bullet::~Bullet() {}



sf::CircleShape Bullet::getForm() const
{
    return _form;
}


Player* Bullet::getShooter() const
{
    return _shooter;
}

void Bullet::setShooter(Player* const shooter)
{
    _shooter = shooter;
}


void Bullet::setPosition(sf::Vector2f const &position)
{
    _form.setPosition(position);
}

void Bullet::setXPosition(float const &x)
{
    _form.setPosition(x, _form.getPosition().y);
}

void Bullet::setYPosition(float const &y)
{
    _form.setPosition(_form.getPosition().x, y);
}


sf::Vector2f Bullet::getPosition() const
{
    return _form.getPosition();
}

float Bullet::getBottomPosition() const
{
    return _form.getGlobalBounds().top + _form.getGlobalBounds().width;
}

float Bullet::getRightPosition() const
{
    return _form.getPosition().x + _form.getGlobalBounds().height;
}



void Bullet::setRadius(float const &radius)
{
     _form.setRadius(radius);
}

float Bullet::getRadius() const
{
    return _form.getRadius();
}



void Bullet::setOutlineThickness(float const &t)
{
    _form.setOutlineThickness(t);
}


float Bullet::getOutlineThickness() const
{
    return _form.getOutlineThickness();
}



void Bullet::setScale(sf::Vector2f const &scale)
{
    _form.setScale(scale);
}

void Bullet::setXScale(float const &x)
{
    _form.setScale(x, _form.getScale().y);
}

void Bullet::setYScale(float const &y)
{
    _form.setScale(_form.getScale().x, y);
}


sf::Vector2f Bullet::getScale() const
{
    return _form.getScale();
}



float Bullet::getHeight() const
{
    return _form.getGlobalBounds().height;
}

float Bullet::getWidth() const
{
    return _form.getGlobalBounds().width;
}



void Bullet::setFillColour(sf::Color const &colour)
{
    _form.setFillColor(colour);
}

sf::Color Bullet::getFillColour() const
{
    return _form.getFillColor();
}



void Bullet::setOutlineColour(sf::Color const &colour)
{
    _form.setOutlineColor(colour);
}

sf::Color Bullet::getOutlineColour() const
{
    return _form.getOutlineColor();
}



void Bullet::setFillOpacity(unsigned short const &a)
{
    sf::Color colour = _form.getFillColor();
    colour.a = a;
    _form.setFillColor(colour);
}

void Bullet::setOutlineOpacity(unsigned short const &a)
{
    sf::Color colour = _form.getOutlineColor();
    colour.a = a;
    _form.setOutlineColor(colour);
}



void Bullet::setXSpeedPerSec(float const &x)
{
    _xSpeedPerSec = x;
}

void Bullet::setYSpeedPerSec(float const &y)
{
    _ySpeedPerSec = y;
}


float Bullet::getXSpeexPerSec() const
{
    return _xSpeedPerSec;
}

float Bullet::getYSpeexPerSec() const
{
    return _ySpeedPerSec;
}




void Bullet::moveUpWithTheSetVelocity(unsigned long const &elapsedUs)
{
    _form.move(sf::Vector2f(0.f, _ySpeedPerSec * static_cast<long double>(elapsedUs) / -1000000.L));
}




bool Bullet::contains(sf::Vector2f const &viewPosition)
{
    return _form.getGlobalBounds().contains(viewPosition);
}
