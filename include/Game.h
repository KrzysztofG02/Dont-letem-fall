#ifndef GAME_H
#define GAME_H

#include "Bullet.h"
#include "Enemy.h"
#include "Level.h"
#include "Player.h"

#include <chrono>
#include <list>
#include <vector>

#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>


class Game
{
private:
    char const static constexpr *_authorName = "Krzysztof Gasior";
    char const static constexpr *_gameTitle = "Don't let'em fall";

    uint8_t constexpr static _resNum = 12;
    uint16_t constexpr static _resolutions[_resNum][2] = {
        {640, 360},
        {800, 450},
        {1024, 600},
        {1280, 720},
        {1366, 768},
        {1600, 900},
        {1920, 1080},
        {2048, 1152},
        {2560, 1440},
        {3072, 1728},
        {3840, 2160},
        {4096, 2304}};

    sf::VideoMode _videoMode;
    sf::RenderWindow *_window;
    sf::Color _backgroundColor;

    std::chrono::microseconds _elapsedIter_us;

    sf::Event _event;

    sf::Font _font;

    sf::Music _backgroundMusic;


    enum class GameStage: char
    {
        intro,
        menu,
        tie,
        null
    };
    GameStage _gameStage;

    enum class StagePhasis: char
    {
        loading,
        ongoing,
        quitting,
        gameover,
        null
    };
    StagePhasis _stagePhasis;

    std::map<GameStage, std::map<StagePhasis, void (Game::*)()>> _stageFunctions;


    enum class GameoverStage: char
    {
        loading,
        ongoing,
        quitting,
        null
    };
    GameoverStage _gameoverStage;


    enum class LevelPhasis: char
    {
        loading,
        ongoing,
        paused,
        quitting,
        null
    };
    LevelPhasis _levelPhasis;

    enum class PausePhasis: char
    {
        loading,
        ongoing,
        quitting,
        null
    };
    PausePhasis _pausePhasis;

    enum class PhasePhasis: char
    {
        loading,
        ongoing,
        quitting,
        null
    };
    PhasePhasis phasePhasis;


    //Menu
    unsigned short static constexpr _numberOfKeys = 2;
    sf::Keyboard::Key static constexpr _keys[_numberOfKeys] = {
        sf::Keyboard::Down,
        sf::Keyboard::Up};

    int _previousHoveredOption;
    int _hoveredOption;
    sf::Keyboard::Key _recentlyPressedKey;

    enum class Mode: char
    {
        singleplayer,
        multiplayer,
        null
    };
    Mode _mode;
    //Menu/

    std::vector<std::chrono::microseconds> _timers_us;
    std::vector<sf::Text> _huds;
    std::vector<sf::Text> _texts;
    std::list<Player> _players;
    std::list<Bullet> _bullets;
    std::list<Enemy> _enemies;
    std::vector<sf::RectangleShape> _overlays;

    std::array<Enemy, 3> _modelEnemyTypesArray;
    std::array<Level, 1> _levels;

    unsigned short _currLevelIdx;
    unsigned short _currPhaseIdx;
    unsigned short _enemiesPasses;



public:
    Game();
    ~Game();

    void run();


private:
    void initRenderWindow();
        bool initFullScreenMode();
        void initWindowMode();
    void initStageFunctions();
    void initFont();
    void initBackgroundMusic();
    void initLevels();
    void initModelEnemyTypesArray();
    void initEnumClassInstances();


    bool const isRunning() const;
    void pollEvents();
    void update();
    void render();

    bool isMusicPlaying();
    void playMusic();
    void pauseMusic();
    void stopMusic();
    bool switchMusic();

    void loadIntro();
    void runIntro();
    void quitIntro();
        void clearIntro();

    void loadMenu();
    void runMenu();
    void quitMenu();
        void clearMenu();

    void loadTie();
    void runTie();
        bool switchPause();

        void loadLevel();
            void loadPlayers();
            void loadHuds();

        void runLevel();
            void loadPhase();
                void prepareObjects();
            void runPhase();
                void updateObjects();
            void quitPhase();
                void clearPhase();

            void setEnemiesPassesHUD();

        void pauseLevel();
            void loadPause();
            void runPause();
            void quitPause();
                void clearPause();

        void quitLevel();
            void clearLevel();
    void gameoverTie();
        void loadGameover();
        void runGameover();
        void quitGameover();
            void clearGameover();
    void quitTie();
        void clearTie();

    void updateEnemies();
        void enemySpawner();
        bool checkEnemyCollisions(std::list<Enemy>::iterator &enemy);
            bool checkEnemyCollisionWithBorder(std::list<Enemy>::iterator &enemy);
            bool checkEnemyCollisionWithPlayers(std::list<Enemy>::iterator &enemy);
                bool checkEnemyCollisionWithPlayer(std::list<Enemy>::iterator &enemy, Player const &player);
            bool checkEnemyCollisionWithBullets(std::list<Enemy>::iterator &enemy);
                bool checkEnemyCollisionWithBullet(std::list<Enemy>::iterator &enemy, Bullet const &bullet);
        void killEnemyByBorder(std::list<Enemy>::iterator &enemy);
        void killEnemyByBullet(std::list<Enemy>::iterator &enemy, Bullet const &bullet);
        void killEnemyByPlayer(std::list<Enemy>::iterator &enemy, Player *player);

    void updateBullets();
        void destroyBullet(std::list<Bullet>::iterator &bullet);

    void updatePlayers();
        void updatePlayerMove(std::list<Player>::iterator &player);



    template <typename T>
    constexpr T calcPercentageOfY(T const &pct)
    {
        return _window->getSize().y * pct / 100;
    }

    template <typename T>
    constexpr T calcPercentageOfX(T const &pct)
    {
        return _window->getSize().x * pct / 100;
    }
};

#endif // GAME_H
