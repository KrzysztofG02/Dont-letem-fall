#ifndef MENU_H
#define MENU_H

#include <vector>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio/Music.hpp>



/*class Menu final
{
private:
    sf::Font _font;
    sf::Color _backgroundColor;

    std::string _backgroundMusicSource;
    sf::Music *_backgroundMusic;

    float _fontSize;
    sf::Color _optionsColor;
    sf::Color _hoveredOptionColor;
    std::vector<sf::Text> _options;

    int _chosenOption;

public:
    Menu(sf::Font const &font,
         std::string const backgroundMusicSource = "",
         sf::Color const &backgroundColor = sf::Color::Black,
         float const &fontSize = 8.f,
         sf::Color const &optionsColor = sf::Color::Black,
         sf::Color const &hoveredOptionColor = sf::Color::Green);
    ~Menu();

    sf::Color getBackgroundColor() const;
    std::string getBackgroundMusicSource() const;
    sf::Font& getFont() const;
    const std::vector<sf::Text>& getOptions() const;
    float getFontSize() const;
    sf::Color getOptionsColor() const;
    sf::Color getHoveredOptionColor() const;

    int getChosenOption() const;

    void setBackgroundColor(sf::Color const &backgroundColor);
    void setBackgroundMusicSource(std::string const backgroundMusicSource);
    void setFont(sf::Font const &font);
    void setOptions(std::vector<sf::Text> const &options);
    void setFontSize(const float &vhFontSize);
    void setOptionsColor(sf::Color const &optionsColor);
    void setHoveredOptionColor(sf::Color const &hoveredOptionColor);

    // Metoda run
    void run();
    void addOption(std::string const &optionName);
    void removeOption(unsigned const &index);
};*/

#endif // MENU_H
