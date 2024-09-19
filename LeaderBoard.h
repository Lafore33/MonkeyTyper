#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "GameSettings.h"
class LeaderBoard {
public:
    sf::Text leaderBoard;
    sf::Text userName;
    sf::Text ms;
    sf::Text maxResult;
    Button backToMenu;
    std::vector<std::vector<std::string>> leaderBord = std::vector<std::vector<std::string>>();
    std::vector<std::vector<std::string>> bestResult = std::vector<std::vector<std::string>>();
    std::string leaderFile = "assets/leaderBoard.txt";
    bool currentS = true;
    int k = 0;
    Button currentSession;
    Button bestResults;
    GameSettings* gameSettings;

    LeaderBoard(GameSettings& game);
    void draw();
    void setFont(const sf::Font& font);
    void setPosition();
    void handleEvent(sf::Event& event);
};


