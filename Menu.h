#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameSettings.h"
#include "Button.h"


class Menu{
private:
    sf::Font font;
    Button playButton;
    Button settingsButton;
    Button showLeaderBoard;
    Button exitButton;
    GameSettings* gameSettings;

public:
    Menu(GameSettings& game);
    void handleEvent(sf::Event& event);
    void draw();
    void setFont(const sf::Font& ft);
    void setPosition();
};


