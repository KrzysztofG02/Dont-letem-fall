#include "Game.h"

using namespace std;



bool Game::isMusicPlaying()
{
    return _backgroundMusic.getStatus() == sf::Music::Playing;
}

void Game::playMusic()
{
    _backgroundMusic.play();
}

void Game::pauseMusic()
{
    _backgroundMusic.pause();
}

void Game::stopMusic()
{
    _backgroundMusic.stop();
}

bool Game::switchMusic()
{
    if(this->isMusicPlaying())
    {
        this->pauseMusic();

        return false;
    }
    else
    {
        this->playMusic();
    }

    return true;
}
