#include "Game.h"

using namespace std;



void Game::loadTie()
{
    _currLevelIdx = 0;

    _stagePhasis = StagePhasis::ongoing;
    _levelPhasis = LevelPhasis::loading;
}

void Game::runTie()
{
    switch(_levelPhasis)
    {
        case LevelPhasis::loading:
            this->loadLevel();
            return;

        case LevelPhasis::ongoing:
            this->runLevel();
            return;

        case LevelPhasis::paused:
            this->pauseLevel();
            return;

        case LevelPhasis::quitting:
            this->quitLevel();
            return;

        default: return;
    }
}

void Game::gameoverTie()
{
    switch(_gameoverStage)
    {
        case GameoverStage::loading:
            this->loadGameover();
            return;

        case GameoverStage::ongoing:
            this->runGameover();
            return;

        case GameoverStage::quitting:
            this->quitGameover();
            return;

        default: return;
    }
}

void Game::quitTie()
{
    this->clearTie();

    _gameStage = GameStage::menu;
    _stagePhasis = StagePhasis::loading;
}

void Game::clearTie()
{
    if(_levelPhasis != LevelPhasis::quitting && _levelPhasis != LevelPhasis::null)
    {
        this->clearLevel();
    }
}
