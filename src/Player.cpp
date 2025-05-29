#include "Player.h"

Player::Player(unsigned const &id,
    std::string const &textureSource,
    int const &health,
    unsigned const &kills,
    unsigned long const &points,
    sf::Keyboard::Key const &moveLeftButton,
    sf::Keyboard::Key const &moveRightButton,
    sf::Keyboard::Key const &shootButton,
    sf::Vector2f const &position,
    sf::Vector2f const &size,
    float const &xSpeedPerSec,
    float const &ySpeedPerSec):
        _id(id),
        _textureSource(textureSource),
        _health(health),
        _kills(kills),
        _points(points),
        _moveLeftButton(moveLeftButton),
        _moveRightButton(moveRightButton),
        _shootButton(shootButton),
        _size(size),
        _xSpeedPerSec(xSpeedPerSec),
        _ySpeedPerSec(ySpeedPerSec),
        _recentlyPressedMoveButton(sf::Keyboard::Unknown),
        _shootFlag(false)
{
    if(_textureSource != "")
    {
        _texture.loadFromFile(_textureSource);
        _sprite.setTexture(_texture);

        _sprite.setPosition(position);
        _sprite.setScale(_size.x / static_cast<float>(_texture.getSize().x),
                         _size.y / static_cast<float>(_texture.getSize().y));
    }
}

Player::Player(const Player& other)
{
    if(this != &other)
    {
        _id = other._id;

        _textureSource = other._textureSource;
        _texture = other._texture;

        _sprite = other._sprite;
        _sprite.setTexture(_texture);

        _health = other._health;
        _kills = other._kills;
        _points = other._points;
        _moveLeftButton = other._moveLeftButton;
        _moveRightButton = other._moveRightButton;
        _shootButton = other._shootButton;
        _size = other._size;
        _xSpeedPerSec = other._xSpeedPerSec;
        _ySpeedPerSec = other._ySpeedPerSec;
        _recentlyPressedMoveButton = other._recentlyPressedMoveButton;
        _shootFlag = other._shootFlag;
    }
}

Player::~Player() {}



unsigned Player::getId() const
{
    return _id;
}


std::string const& Player::getTextureSource() const
{
    return _textureSource;
}

sf::Texture const& Player::getTexture() const
{
    return _texture;
}

sf::Sprite const& Player::getForm() const
{
    return _sprite;
}


unsigned short Player::getHealth() const
{
    return _health;
}

unsigned Player::getKills() const
{
    return _kills;
}

unsigned long Player::getPoints() const
{
    return _points;
}


sf::Keyboard::Key Player::getMoveLeftButton() const
{
    return _moveLeftButton;
}

sf::Keyboard::Key Player::getMoveRightButton() const
{
    return _moveRightButton;
}

sf::Keyboard::Key Player::getShootButton() const
{
    return _shootButton;
}


float Player::getXSpeedPerSec() const
{
    return _xSpeedPerSec;
}

float Player::getYSpeedPerSec() const
{
    return _ySpeedPerSec;
}


sf::Keyboard::Key Player::getRecentlyPressedMoveButton() const
{
    return _recentlyPressedMoveButton;
}

bool Player::getShootFlag() const
{
    return _shootFlag;
}


sf::Vector2f Player::getPosition() const
{
    return _sprite.getPosition();
}

sf::Vector2f Player::getSize() const
{
    return _size;
}


sf::FloatRect Player::getGlobalBounds() const
{
    return _sprite.getGlobalBounds();
}

sf::Vector2f Player::getScale() const
{
    return _sprite.getScale();
}



void Player::setId(unsigned const &id)
{
    _id = id;
}


void Player::setTexture(std::string const &textureSource)
{
    _textureSource = textureSource;
    _texture.loadFromFile(_textureSource);
    _sprite.setTexture(_texture);
    _sprite.setScale(_size.x / static_cast<float>(_texture.getSize().x),
                     _size.y / static_cast<float>(_texture.getSize().y));
}


void Player::setHealth(unsigned short const &health)
{
    _health = health;
}

void Player::addHealthPoints(unsigned short const &healthPoints)
{
    _health += healthPoints;
}

void Player::subtractHealthPoints(unsigned short const &healthPoints)
{
    if(_health < healthPoints)
    {
        _health = 0;
    }
    else
    {
        _health -= healthPoints;
    }
}


void Player::setKills(unsigned const &kills)
{
    _kills = kills;
}

void Player::addKills(unsigned const &killPoints)
{
    _kills += killPoints;
}

void Player::subtractKills(unsigned const &killPoints)
{
    if(_kills < killPoints)
    {
        _kills = 0;
    }
    else
    {
        _kills -= killPoints;
    }
}


void Player::setPoints(unsigned long const &points)
{
    _points = points;
}

void Player::addPoints(unsigned long const &element)
{
    _points += element;
}

void Player::subtractPoints(unsigned long const &subtrahend)
{
    if(_points < subtrahend)
    {
        _points = 0;
    }
    else
    {
        _points -= subtrahend;
    }
}


void Player::setMoveLeftButton(sf::Keyboard::Key const &moveLeftButton)
{
    _moveLeftButton = moveLeftButton;
}

void Player::setMoveRightButton(sf::Keyboard::Key const &moveRightButton)
{
    _moveRightButton = moveRightButton;
}

void Player::setShootButton(sf::Keyboard::Key const &shootButton)
{
    _shootButton = shootButton;
}


void Player::setXSpeedPerSec(float const &xSpeedPerSec)
{
    _xSpeedPerSec = xSpeedPerSec;
}

void Player::setYSpeedPerSec(float const &ySpeedPerSec)
{
    _ySpeedPerSec = ySpeedPerSec;
}


void Player::setRecentlyPressedMoveButton(sf::Keyboard::Key const &recentlyPressedMoveButton)
{
    _recentlyPressedMoveButton = recentlyPressedMoveButton;
}

void Player::setShootFlag()
{
    _shootFlag = true;
}

void Player::clearShootFlag()
{
    _shootFlag = false;
}


void Player::setPosition(sf::Vector2f const &position)
{
    _sprite.setPosition(position);
}

void Player::setSize(sf::Vector2f const &size)
{
    _sprite.setScale(size.x / static_cast<float>(_texture.getSize().x),
                     size.y / static_cast<float>(_texture.getSize().y));
}


void Player::moveLeft(float const &x)
{
    _sprite.move(sf::Vector2f(-x, 0));
}

void Player::moveRight(float const &x)
{
    _sprite.move(sf::Vector2f(x, 0));
}


void Player::moveLeftWithTheSetVelocity(unsigned long const &elapsedUs)
{
    _sprite.move(sf::Vector2f(_xSpeedPerSec
        * static_cast<long double>(elapsedUs) / -1000000.L, 0.f));
}

void Player::moveRightWithTheSetVelocity(unsigned long const &elapsedUs)
{
    _sprite.move(sf::Vector2f(_xSpeedPerSec
        * static_cast<long double>(elapsedUs) / 1000000.L, 0.f));
}



