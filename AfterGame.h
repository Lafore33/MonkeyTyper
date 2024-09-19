#pragma once
#include "Button.h"
#include <SFML/Graphics.hpp>
#include "GameSettings.h"
#include "Menu.h"
#include "LeaderBoard.h"
#include "GameSession.h"
#include <memory>

class AfterGame {
public:
    Button restartGame;
    Button backToMenu;
    sf::Text result;
    GameSettings* gameSettings;

    AfterGame(GameSettings& game);
    void draw();
    void setFont();
    void setPosition();
    void handleEvent(sf::Event& event, GameSession& gs);


};


