#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "GameSettings.h"
#include "PreGame.h"
#include "Menu.h"

class GameSession {
public:
    sf::Text input;
    sf::Text score;
    sf::Text points;
    sf::Text missed;
    sf::Text maxMissed;
    sf::Text missedWords;
    sf::Text left;
    sf::Text right;
    sf::Text timerText;
    sf::Text newWord;
    sf::Text showUser;
    sf::Text result;

    Button saving;
    sf::RectangleShape underscore;
    sf::RectangleShape rectangle;
    sf::Clock blinkClock;
    float blinkingInterval = 0.5f;
    std::vector<std::pair<std::string, sf::Text>> currentWords = std::vector<std::pair<std::string, sf::Text>>();
    int count = 0;
    int lostWords = 0;
    int maxLen = 14;
    bool hide=false;
    float lastSpeed = 0;
    std::string inputText = std::string();
    GameSettings *gameSettings;

    GameSession(GameSettings& game);
    void draw();
    void handleEvent(sf::Event& event);
    void setFont(const sf::Font& font);
    void setPosition();
    void moveWords();
    void saveGame();
};
