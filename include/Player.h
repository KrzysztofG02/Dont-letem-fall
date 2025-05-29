#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <iostream>


class Player
{
private:
    unsigned _id;

    std::string _textureSource;
    sf::Texture _texture;
    sf::Sprite _sprite;

    unsigned short _health;
    unsigned _kills;
    unsigned long _points;

    sf::Keyboard::Key _moveLeftButton;
    sf::Keyboard::Key _moveRightButton;
    sf::Keyboard::Key _shootButton;

    sf::Vector2f _size;

    float _xSpeedPerSec;
    float _ySpeedPerSec;

    sf::Keyboard::Key _recentlyPressedMoveButton;
    bool _shootFlag;


public:
    Player(unsigned const &id = 0,
           std::string const &textureSource = "",
           int const &health = 0,
           unsigned const &kills = 0,
           unsigned long const &points = 0,
           sf::Keyboard::Key const &moveLeftButton = sf::Keyboard::Left,
           sf::Keyboard::Key const &moveRightButton = sf::Keyboard::Right,
           sf::Keyboard::Key const &shootButton = sf::Keyboard::Space,
           sf::Vector2f const &position = sf::Vector2f(),
           sf::Vector2f const &size = sf::Vector2f(100.f, 100.f),
           float const &xSpeedPerSec = 100.f,
           float const &ySpeedPerSec = 100.f);
    Player(const Player& other);
    ~Player();



    unsigned getId() const;

    std::string const& getTextureSource() const;
    sf::Texture const& getTexture() const;
    sf::Sprite const& getForm() const;

    unsigned short getHealth() const;
    unsigned getKills() const;
    unsigned long getPoints() const;

    sf::Keyboard::Key getMoveLeftButton() const;
    sf::Keyboard::Key getMoveRightButton() const;
    sf::Keyboard::Key getShootButton() const;

    float getXSpeedPerSec() const;
    float getYSpeedPerSec() const;

    sf::Keyboard::Key getRecentlyPressedMoveButton() const;
    bool getShootFlag() const;

    sf::Vector2f getPosition() const;
    sf::Vector2f getSize() const;

    sf::FloatRect getGlobalBounds() const;
    sf::Vector2f getScale() const;



    void setId(unsigned const &id);

    void setTexture(std::string const &textureSource);

    void setHealth(unsigned short const &health);
    void addHealthPoints(unsigned short const &healthPoints = 1);
    void subtractHealthPoints(unsigned short const &healthPoints = 1);

    void setKills(unsigned const &kills);
    void addKills(unsigned const &killPoints = 1);
    void subtractKills(unsigned const &killPoints = 1);

    void setPoints(unsigned long const &points);
    void addPoints(unsigned long const &element = 1);
    void subtractPoints(unsigned long const &subtrahend = 1);

    void setMoveLeftButton(sf::Keyboard::Key const &moveLeftButton);
    void setMoveRightButton(sf::Keyboard::Key const &moveRightButton);
    void setShootButton(sf::Keyboard::Key const &shootButton);

    void setXSpeedPerSec(float const &xSpeedPerSec);
    void setYSpeedPerSec(float const &ySpeedPerSec);

    void setRecentlyPressedMoveButton(sf::Keyboard::Key const &recentlyPressedMoveButton);
    void setShootFlag();
    void clearShootFlag();

    void setPosition(sf::Vector2f const &position);
    void setSize(sf::Vector2f const &size);

    void moveLeft(float const &x);
    void moveRight(float const &x);

    void moveLeftWithTheSetVelocity(unsigned long const &elapsedUs);
    void moveRightWithTheSetVelocity(unsigned long const &elapsedUs);
};

#endif // PLAYER_H
