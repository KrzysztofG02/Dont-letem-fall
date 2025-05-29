#include "Game.h"

#include <iostream>

using namespace std;



Game::Game(): _window(nullptr)
{
    this->initRenderWindow();
    this->initStageFunctions();
    this->initFont();
    this->initBackgroundMusic();
    this->initLevels();
    this->initModelEnemyTypesArray();
    this->initEnumClassInstances();
}

Game::~Game()
{
    delete _window;
}



void Game::initRenderWindow()
{   ///get current desktop mode of a user
    _videoMode = sf::VideoMode::getDesktopMode();

    //if(this->initFullScreenMode() == false)
    {
        this->initWindowMode();
    }

    _window->setMouseCursorVisible(false);
    _window->setVerticalSyncEnabled(false);
}

bool Game::initFullScreenMode()
{   ///check if any of the predefined resolutions are equal to the user's
    for(unsigned short i = 0; i < _resNum; ++i)
    {
        if(   _resolutions[i][0] == _videoMode.width
           && _resolutions[i][1] == _videoMode.height)
        {
            _videoMode.width = _resolutions[i][0];  ///if so, create a window
            _videoMode.height = _resolutions[i][1]; ///in full-screen mode

            _window = new sf::RenderWindow(_videoMode, _gameTitle,
                                           sf::Style::Fullscreen);

            return true;
        }
    }

    return false;
}

void Game::initWindowMode()
{
    /*for(int i = _resNum - 1; i >= 0; --i)
    {
        if(   _resolutions[i][0] <= _videoMode.width    ///if not, create the largest possible
           && _resolutions[i][1] <= _videoMode.height)  ///window with one of the predefined resolutions
        {
            _videoMode.width = _resolutions[i][0];  ///if so, create a window
            _videoMode.height = _resolutions[i][1]; ///in full-screen mode

            _window = new sf::RenderWindow(_videoMode, _gameTitle,
                                             sf::Style::Titlebar
                                           | sf::Style::Close);

            return;
        }
    }*/

    _window = new sf::RenderWindow(sf::VideoMode(1280, 720), _gameTitle, sf::Style::Titlebar | sf::Style::Close);
}


void Game::initStageFunctions()
{
    _stageFunctions[GameStage::intro][StagePhasis::loading] = &Game::loadIntro;
    _stageFunctions[GameStage::intro][StagePhasis::ongoing] = &Game::runIntro;
    _stageFunctions[GameStage::intro][StagePhasis::quitting] = &Game::quitIntro;

    _stageFunctions[GameStage::menu][StagePhasis::loading] = &Game::loadMenu;
    _stageFunctions[GameStage::menu][StagePhasis::ongoing] = &Game::runMenu;
    _stageFunctions[GameStage::menu][StagePhasis::quitting] = &Game::quitMenu;

    _stageFunctions[GameStage::tie][StagePhasis::loading] = &Game::loadTie;
    _stageFunctions[GameStage::tie][StagePhasis::ongoing] = &Game::runTie;
    _stageFunctions[GameStage::tie][StagePhasis::gameover] = &Game::gameoverTie;
    _stageFunctions[GameStage::tie][StagePhasis::quitting] = &Game::quitTie;
}


void Game::initFont()
{
    _font.loadFromFile("fonts/Minecraft.ttf");
}


void Game::initBackgroundMusic()
{
    _backgroundMusic.openFromFile("music/Spiderman2PizzaTheme.ogg");
    _backgroundMusic.setLoop(true);
}


void Game::initLevels()
{
    //enemyTypesNumber, enemySpawnCooldown_ms, totalEnemyCount, maxAliveEnemies,
    //spawnEnemyCumulativeProb, xSpeedPerSecMultiplier, ySpeedPerSecMultiplier,
    //prizeMultiplier, penaltyMultiplier
    _levels[0] = Level(100, chrono::seconds(5), 8);
    _levels[0].addPhase(Phase(1, chrono::milliseconds(500), 32, 6, {100}, 1.f, 1.f));
    _levels[0].addPhase(Phase(1, chrono::milliseconds(500), 40, 8, {100}, 1.f, 1.f));
    _levels[0].addPhase(Phase(2, chrono::milliseconds(500), 32, 8, {80,20}, 1.f, 1.f));
    _levels[0].addPhase(Phase(2, chrono::milliseconds(400), 40, 10, {70,30}, 1.f, 1.25f));
    _levels[0].addPhase(Phase(2, chrono::milliseconds(400), 50, 10, {60,40}, 1.f, 1.25f));
    _levels[0].addPhase(Phase(3, chrono::milliseconds(350), 50, 10, {50,35,15}, 1.f, 1.5f));
    _levels[0].addPhase(Phase(3, chrono::milliseconds(300), 60, 12, {35,40,25}, 1.f, 1.5f));
}


void Game::initModelEnemyTypesArray()
{
    _modelEnemyTypesArray[0] = Enemy(0,  //id
        sf::Vector2f(0.f, 0.f),     //position
        sf::Vector2f(this->calcPercentageOfY(12), this->calcPercentageOfY(12)), //size
        this->calcPercentageOfY(0.2f), //outline Thickness
        sf::Vector2f(1.f, 1.f),      //scale
        sf::Color::Green,            //fill Colour
        sf::Color::Red,              //outline Colour
        0.f,                         //xSpeedPerSec
        this->calcPercentageOfY(13.f),  //ySpeedPerSec
        0.f,                         //xDefMoveUnit
        this->calcPercentageOfY(1.f), //yDefMoveUnit
        5,   //prize Amount
        10); //penalty Amount

    _modelEnemyTypesArray[1] = Enemy(1,
        sf::Vector2f(0.f, 0.f),
        sf::Vector2f((this->calcPercentageOfY(9)),(this->calcPercentageOfY(9))),
        this->calcPercentageOfY(0.2f),
        sf::Vector2f(1.f, 1.f),
        sf::Color::Blue,
        sf::Color::Cyan,
        0.f,
        this->calcPercentageOfY(16.f),
        0.f,
        this->calcPercentageOfY(1.f),
        8,
        15);

    _modelEnemyTypesArray[2] = Enemy(2,
        sf::Vector2f(0.f, 0.f),
        sf::Vector2f(this->calcPercentageOfY(5), this->calcPercentageOfY(5)),
        this->calcPercentageOfY(0.3f),
        sf::Vector2f(1.f, 1.f),
        sf::Color::Red,
        sf::Color(145, 25, 16, 255),
        0.f,
        this->calcPercentageOfY(20.f),
        0.f,
        this->calcPercentageOfY(1.f),
        1,
        20);
}


void Game::initEnumClassInstances()
{
    _gameStage = GameStage::null;
    _stagePhasis = StagePhasis::null;
    _gameoverStage = GameoverStage::null;
    _levelPhasis = LevelPhasis::null;
    _pausePhasis = PausePhasis::null;
    phasePhasis = PhasePhasis::null;
    _mode = Mode::null;
}
