#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "GameSettings.h"
#include "GameSession.h"
#include "LeaderBoard.h"
#include "Game.h"

class SavedGame {
public:
    sf::Text load;
    Button yes;
    Button no;
    Button backToMenu;
    GameSettings* gameSettings;

    SavedGame(GameSettings& game);
    void draw();
    void setPosition();
    void handleEvent(sf::Event &event, GameSession& gs);
    void loadGame(GameSession& gs) const;
    void setFont(const sf::Font &font);

};


