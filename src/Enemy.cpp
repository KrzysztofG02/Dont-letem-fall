#include "Enemy.h"

Enemy::Enemy(unsigned const &id, sf::Vector2f const &position,
             sf::Vector2f const &size, float const &outlineThickness,
             sf::Vector2f const &scale, sf::Color const &fillColour,
             sf::Color const &outlineColour, float const &xSpeedPerSec,
             float const &ySpeedPerSec, float const &xDefMoveUnit,
             float const &yDefMoveUnit, unsigned long const &prizeAmount,
             unsigned long const &penaltyAmount)
{
    _id = id;

    _form.setPosition(position);
    _form.setSize(size);
    _form.setOutlineThickness(outlineThickness);
    _form.setScale(scale);
    _form.setFillColor(fillColour);
    _form.setOutlineColor(outlineColour);

    _xSpeedPerSec = xSpeedPerSec;
    _ySpeedPerSec = ySpeedPerSec;

    _xDefMoveUnit = xDefMoveUnit;
    _yDefMoveUnit = yDefMoveUnit;

    _prizeAmount = prizeAmount;
    _penaltyAmount = penaltyAmount;
}

Enemy::~Enemy() {}



void Enemy::setID(unsigned const id)
{
    _id = id;
}


unsigned Enemy::getID() const
{
    return _id;
}



sf::RectangleShape Enemy::getForm() const
{
    return _form;
}



void Enemy::setPosition(sf::Vector2f const position)
{
    _form.setPosition(position);
}

void Enemy::setXPosition(float const x)
{
    _form.setPosition(x, _form.getPosition().y);
}

void Enemy::setYPosition(float const y)
{
    _form.setPosition(_form.getPosition().x, y);
}


sf::Vector2f Enemy::getPosition() const
{
    return _form.getPosition();
}

float Enemy::getBottomPosition() const
{
    return _form.getGlobalBounds().top + _form.getGlobalBounds().width;
}

float Enemy::getRightPosition() const
{
    return _form.getPosition().x + _form.getGlobalBounds().height;
}



void Enemy::setSize(sf::Vector2f const size)
{
     _form.setSize(size);
}

void Enemy::setXSize(float const x)
{
    _form.setSize(sf::Vector2f(x, _form.getPosition().y));
}

void Enemy::setYSize(float const y)
{
    _form.setSize(sf::Vector2f(_form.getPosition().x, y));
}


sf::Vector2f Enemy::getSize() const
{
    return _form.getSize();
}



void Enemy::setOutlineThickness(float const t)
{
    _form.setOutlineThickness(t);
}


float Enemy::getOutlineThickness() const
{
    return _form.getOutlineThickness();
}



void Enemy::setScale(sf::Vector2f const scale)
{
    _form.setScale(scale);
}

void Enemy::setXScale(float const x)
{
    _form.setScale(x, _form.getScale().y);
}

void Enemy::setYScale(float const y)
{
    _form.setScale(_form.getScale().x, y);
}


sf::Vector2f Enemy::getScale() const
{
    return _form.getScale();
}



float Enemy::getHeight() const
{
    return _form.getGlobalBounds().height;
}

float Enemy::getWidth() const
{
    return _form.getGlobalBounds().width;
}



void Enemy::setFillColour(sf::Color const colour)
{
    _form.setFillColor(colour);
}

sf::Color Enemy::getFillColour() const
{
    return _form.getFillColor();
}



void Enemy::setOutlineColour(sf::Color const colour)
{
    _form.setOutlineColor(colour);
}

sf::Color Enemy::getOutlineColour() const
{
    return _form.getOutlineColor();
}



void Enemy::setFillOpacity(uint8_t const a)
{
    sf::Color colour = _form.getFillColor();
    colour.a = a;
    _form.setFillColor(colour);
}

void Enemy::setOutlineOpacity(uint8_t const a)
{
    sf::Color colour = _form.getOutlineColor();
    colour.a = a;
    _form.setOutlineColor(colour);
}



void Enemy::setXSpeedPerSec(float const x)
{
    _xSpeedPerSec = x;
}

void Enemy::setYSpeedPerSec(float const y)
{
    _ySpeedPerSec = y;
}


float Enemy::getXSpeexPerSec() const
{
    return _xSpeedPerSec;
}

float Enemy::getYSpeexPerSec() const
{
    return _ySpeedPerSec;
}



void Enemy::setXDefMoveUnit(float const x)
{
    _xDefMoveUnit = x;
}

void Enemy::setYDefMoveUnit(float const y)
{
    _yDefMoveUnit = y;
}


float Enemy::getXDefMoveUnit() const
{
    return _xDefMoveUnit;
}

float Enemy::getYDefMoveUnit() const
{
    return _yDefMoveUnit;
}



void Enemy::move()
{
    _form.move(sf::Vector2f(_xDefMoveUnit, _yDefMoveUnit));
}

void Enemy::move(float const x , float const y)
{
    _form.move(sf::Vector2f(x, y));
}


void Enemy::moveWithTheSetVelocity(unsigned long const elapsedUs)
{
    _form.move(sf::Vector2f(_xSpeedPerSec * static_cast<long double>(elapsedUs) / 1000000.L,
                            _ySpeedPerSec * static_cast<long double>(elapsedUs) / 1000000.L));
}

void Enemy::moveXWithTheSetVelocity(unsigned long const elapsedUs)
{
    _form.move(sf::Vector2f(_xSpeedPerSec * static_cast<long double>(elapsedUs) / 1000000.L, 0.f));
}

void Enemy::moveYWithTheSetVelocity(unsigned long const elapsedUs)
{
    _form.move(sf::Vector2f(0.f, _ySpeedPerSec * static_cast<long double>(elapsedUs) / 1000000.L));
}


void Enemy::moveX()
{
   _form.move(sf::Vector2f(_xDefMoveUnit, 0.f));
}

void Enemy::moveX(float const x)
{
    _form.move(sf::Vector2f(x, 0.f));
}


void Enemy::moveY()
{
    _form.move(sf::Vector2f(0.f, _yDefMoveUnit));
}

void Enemy::moveY(float const y)
{
    _form.move(sf::Vector2f(0.f, y));
}



bool Enemy::contains(sf::Vector2f const viewPosition)
{
    return _form.getGlobalBounds().contains(viewPosition);
}



void Enemy::setPrizeAmount(unsigned long const prizeAmount)
{
    _prizeAmount = prizeAmount;
}


unsigned long Enemy::getPrizeAmount() const
{
    return _prizeAmount;
}



void Enemy::setPenaltyAmount(unsigned long const penaltyAmount)
{
    _penaltyAmount = penaltyAmount;
}


unsigned long Enemy::getPenaltyAmount() const
{
    return _penaltyAmount;
}
