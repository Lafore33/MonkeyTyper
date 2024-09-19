#pragma once
#include "GameSession.h"
#include "LeaderBoard.h"
#include "AfterGame.h"
#include "GameSettings.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include <fstream>
#include <random>

class Game {
public:
    float seconds = 0;
    GameSettings* gameSettings;
    GameSession* gameSession;
    Game(GameSettings& gSettings, GameSession& gs);
    void outOfBounds(LeaderBoard& ld, AfterGame& ag) const;
    void setTimer();
    void Words() const;
    void handleEvent(sf::Event& event) const;
};


