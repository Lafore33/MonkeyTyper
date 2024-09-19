#pragma once
#include "Button.h"
#include "GameSettings.h"
#include "LeaderBoard.h"
#include <SFML/Graphics.hpp>
#include <string>


class PreGame {
public:
    Button backToMenu;
    sf::Text enterName;
    sf::Text input;
    std::string inputText;
    GameSettings* gameSettings;

    PreGame(GameSettings& game);
    void draw();
    void setPosition();
    void handleEvent(sf::Event& event);
    void setFont(const sf::Font& font);

};


