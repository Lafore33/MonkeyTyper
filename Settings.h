#pragma once
#include <SFML/Graphics.hpp>
#include "GameSettings.h"
#include "Button.h"



class Settings {
public:
    sf::RectangleShape volumeSetter;
    sf::CircleShape volumePointer;
    sf::Text percentage;

    Button enterSpeed;
    Button setFontSize;
    Button changeVolume;
    Button backToMenu;
    Button newSpeed;
    Button newSize;
    Button changeFont;

    Button incSpeed;
    Button decSpeed;
    Button incSize;
    Button decSize;
    std::vector<std::string> fonts;
    std::string prefix;
    bool isDragging;
    bool deleteFontButtons;
    bool changingFont;
    float rest ;
    std::string speed = std::to_string(0.3).substr(0, 4);
    std::vector<Button> curFonts;
    GameSettings* gameSettings;


    Settings(GameSettings& game, std::vector<std::string>& fts);
    void handleEvent(sf::Event& event);
    void setFont(const sf::Font& font);
    void setPosition();
    void draw();
};


