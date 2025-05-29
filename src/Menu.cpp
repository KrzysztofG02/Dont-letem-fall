/*#include "Menu.h"
#include <iostream>

Menu::Menu(sf::Font const &font,
        std::string const backgroundMusicSource,
        sf::Color const &backgroundColor,
        float const &fontSize,
        sf::Color const &optionsColor,
        sf::Color const &hoveredOptionColor)
{
    _font = font;
    _backgroundColor = backgroundColor;

    _backgroundMusicSource = backgroundMusicSource;
    if(_backgroundMusicSource == "")
    {
        _backgroundMusic = nullptr;
    }
    else
    {
        _backgroundMusic = new sf::Music();
        _backgroundMusic->openFromFile(_backgroundMusicSource);
        _backgroundMusic->setLoop(true);
    }

    _fontSize = fontSize;
    _optionsColor = optionsColor;
    _hoveredOptionColor = hoveredOptionColor;
    _options.push_back(sf::Text("Exit", _font, _fontSize));
    _options[0].setFillColor(sf::Color::White);

    _chosenOption = -1;
}

Menu::~Menu()
{
    if(_backgroundMusic)
    {
        delete _backgroundMusic;
    }
}

void Menu::run()
{
    if(_backgroundMusic)
    {
        _backgroundMusic->play();
    }

    sf::Font font;
    if (!font.loadFromFile("fonts/Minecraft.ttf")) // Podaj œcie¿kê do odpowiedniego pliku czcionki
    {
        // Obs³uga b³êdu wczytywania czcionki
        std::cerr << "Nie uda³o siê za³adowaæ czcionki!" << std::endl;
        return;
    }
}
*/
