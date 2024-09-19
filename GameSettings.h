#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>


class GameSettings{
public:
    bool isActive;
    bool menu;
    sf::Font font;

    bool isSetting;
    bool showLeaders;
    bool LShift;
    bool Tab;
    bool startGame;
    bool afterGame;
    sf::Clock generalClock;
    sf::Clock intervalClock;
    float generalPausedSeconds = 0.f;
    std::string curUser;
    int ButtonFontSize = 30;
    int TextFontSize = ButtonFontSize / 2;
    float maxVolume = 6.f;
    float volume = maxVolume / 2;
    double maxSpeed = 3;
    double minSpeed = 0.2;
    int fontStep = 1;
    double speedStep = 0.1;
    double moveSpeed = 0.3;
    int maxSize = 30;
    int minSize = 10;
    float interval = 0.1f / (float)moveSpeed;
    int WordsFont = TextFontSize;
    sf::Music music;
    bool gamePaused;
    bool savedGame;
    int const MaxLostWords = 9;
    int const MaxWords = 1021;
    float elapseTime = 0.0f;
    float windowX;
    float windowY;
    sf::RenderWindow window;
    std::string filename = "assets/words.txt";
    std::string defaultFont = "assets/Standard.otf";
    std::string savedGameFile = "assets/savedGame.txt";
    std::vector<std::string> fonts;

    GameSettings();
};



